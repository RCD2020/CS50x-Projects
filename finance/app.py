import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import time

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get held stocks and add prices to each stock as well as add it to the total
    balance = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0][
        "cash"
    ]
    total = balance
    stocks = db.execute(
        "SELECT userid, symbol, amount FROM held WHERE userid=?", session["user_id"]
    )
    for x in range(len(stocks)):
        price = lookup(stocks[x]["symbol"])["price"]
        stocks[x]["price"] = price
        total += price * stocks[x]["amount"]

    return render_template(
        "portfolio.html", total=total, balance=balance, stocks=stocks
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get the form data
        data = lookup(request.form.get("symbol"))
        amount = request.form.get("shares")

        # Validate Form Data
        if not data:
            return apology("Symbol not Found", 400)

        try:
            amount = int(amount)
            if amount < 1:
                return apology("Must buy more than 0 shares")
        except:
            return apology("Must buy a number of shares")

        # Check if possible
        userid = session["user_id"]
        rows = db.execute("SELECT cash FROM users WHERE id=?;", userid)

        if rows[0]["cash"] < data["price"] * amount:
            return apology("Too Broke!!")

        # Add purchase to held and history and subtract cash
        timestamp = int(time.time())

        rows = db.execute(
            "SELECT * FROM held WHERE userid=? AND symbol=?", userid, data["symbol"]
        )
        if not rows:
            db.execute(
                "INSERT INTO held (userid, symbol, amount) VALUES (?, ?, ?)",
                userid,
                data["symbol"],
                amount,
            )
        else:
            db.execute(
                "UPDATE held SET amount=amount + ? WHERE userid=? AND symbol=?",
                amount,
                userid,
                data["symbol"],
            )

        db.execute(
            'INSERT INTO history (userid, added_on, amount, price, type, symbol) VALUES (?, ?, ?, ?, "buy", ?)',
            userid,
            timestamp,
            amount,
            data["price"],
            data["symbol"],
        )
        db.execute(
            "UPDATE users SET cash=cash - ? WHERE id=?", amount * data["price"], userid
        )

        # Redirect to homepage
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get held stocks and add prices to each stock as well as add it to the total
    stocks = db.execute(
        "SELECT DATETIME(added_on, 'unixepoch') AS added_on, amount, price, type, symbol FROM history WHERE userid=?",
        session["user_id"],
    )

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        data = lookup(request.form.get("symbol"))
        if not data:
            return apology("Symbol not found!", 400)

        return render_template("quoted.html", data=data)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        name = request.form.get("username")
        if not name:
            return apology("Where's your username!?", 400)
        if db.execute("SELECT username FROM users WHERE username=?", name):
            return apology("ERM maybe try being a little more creative?", 400)

        password = request.form.get("password")
        confirm = request.form.get("confirmation")
        if not password:
            return apology("Where's your password!?", 400)
        if password != confirm:
            return apology("You didn't match the passwords!", 400)

        passhash = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, passhash)

        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        # Get the form data
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol not found")
        data = lookup(symbol)
        amount = request.form.get("shares")

        # Validate Form Data
        stock = db.execute(
            "SELECT symbol, amount FROM held WHERE userid=? AND symbol=?",
            session["user_id"],
            data["symbol"],
        )
        if not data:
            return apology("Symbol not Found", 404)
        if not stock:
            return apology("Pick something you own!")

        try:
            amount = int(amount)
            if amount < 1:
                return apology("Must sell more than 0 shares")
            if amount > stock[0]["amount"]:
                return apology("You can only sell what you have!")
        except:
            return apology("Must sell a number of shares")

        # Check if possible
        userid = session["user_id"]

        # Add sale to held and history and add cash
        timestamp = int(time.time())

        db.execute(
            "UPDATE held SET amount=amount - ? WHERE userid=? AND symbol=?",
            amount,
            userid,
            data["symbol"],
        )
        db.execute(
            'INSERT INTO history (userid, added_on, amount, price, type, symbol) VALUES (?, ?, ?, ?, "sell", ?)',
            userid,
            timestamp,
            amount,
            data["price"],
            data["symbol"],
        )
        db.execute(
            "UPDATE users SET cash=cash + ? WHERE id=?", amount * data["price"], userid
        )
        db.execute("DELETE FROM held WHERE amount=0")

        # Redirect to homepage
        return redirect("/")

    # Get held stocks
    stocks = db.execute("SELECT symbol FROM held WHERE userid=?", session["user_id"])

    return render_template("sell.html", stocks=stocks)


@app.route("/settings", methods=["GET", "POST"])
@login_required
def webSettings():
    if request.method == "POST":
        oldpass = request.form.get("oldpass")
        if not oldpass:
            return apology("You didn't put in your password!")

        newpass = request.form.get("newpass")
        confirm = request.form.get("confirmation")
        if not newpass or not confirm:
            return apology("You have to fill out the boxes!")
        if newpass != confirm:
            return apology("Passwords do not match!")

        passhash = db.execute("SELECT hash FROM users WHERE id=?", session["user_id"])[
            0
        ]["hash"]
        if not check_password_hash(passhash, oldpass):
            return apology("That's not your old password!")

        db.execute(
            "UPDATE users SET hash=? WHERE id=?",
            generate_password_hash(newpass),
            session["user_id"],
        )

    return render_template("settings.html")
