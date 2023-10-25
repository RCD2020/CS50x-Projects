import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

def checkNum(string):
    if not string:
        return False
    try:
        return int(string)
    except:
        return False


def checkMonth(string):
    num = checkNum(string)
    if num and num >= 1 and num <= 12:
            return num
    return False


def checkDay(string):
    num = checkNum(string)
    if num and num >= 1 and num <= 31:
        return num
    return False



@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get('name')
        month = request.form.get('month')
        day = request.form.get('day')

        month = checkMonth(month)
        day = checkDay(day)
        if month and day:
            db.execute('INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)', name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        rows = db.execute('SELECT name, month, day FROM birthdays;')

        return render_template("index.html", rows=rows)


