-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Show all crimes that take place on the day to find our case
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28;
-- id: 295
-- description: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--              Interviews were conducted today with three witnesses who were present at the time
--              – each of their interview transcripts mentions the bakery.

-- I then looked for the interviews mentioned in the report
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28;
-- I found the three interviews that were previously mentioned
--
-- Ruth:    Sometime within ten minutes of the theft,
--          I saw the thief get into a car in the bakery parking lot and drive away.
--          If you have security footage from the bakery parking lot,
--          you might want to look for cars that left the parking lot in that time frame.
-- Conclusion: The theif left shortly after the crime by car within ten minutes of the theft.
--
-- Eugene:  I don't know the thief's name,
--          but it was someone I recognized.
--          Earlier this morning,
--          before I arrived at Emma's bakery,
--          I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- Conclusion: Eugene recognizes the culprit,
--             and they withdrew from the ATM on Leggett Street before Eugene arrived at the bakery.
--
-- Raymond: As the thief was leaving the bakery,
--          they called someone who talked to them for less than a minute.
--          In the call,
--          I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--          The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- Conclusion: Theif made a call shortly after the crime,
--             less than a minute,
--             that they're planning on taking a flight tomorrow.
--             The theif was not the one who purchased the ticket.

-- Let's explore Ruth's interview
-- We should add everybody who left shortly after the crime to a suspects table.
CREATE TABLE suspects AS
SELECT id FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 30
    AND activity = 'exit'
);
-- Our suspects are Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey, Bruce

-- Next let's explore Eugene's lead
-- We should check for everybody that withdrew from the ATM on Leggett Street before the crime
SELECT atm_transactions.*, people.name
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number=bank_accounts.account_number
JOIN people ON bank_accounts.person_id=people.id
WHERE month=7
AND day=28
AND atm_location='Leggett Street'
AND transaction_type='withdraw';
-- And now let's update our suspects list to only include those who used the atm and left the bakery 15 minutes after the crime.
DELETE FROM suspects
WHERE id NOT IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
);
-- We're left with Iman, Luca, Diana, Bruce

-- Now time for Raymond's interview:
-- Let's find all the calls made on the day of the crime that lasted less than a minute
SELECT people.name FROM phone_calls
JOIN people ON phone_calls.caller=people.phone_number
WHERE month = 7
AND day = 28
AND duration <= 60;
-- Now let's check them against our suspects
SELECT people.name FROM suspects
JOIN people ON suspects.id=people.id
WHERE people.phone_number IN (
    SELECT caller FROM phone_calls
    WHERE month = 7
    AND day = 28
    AND duration <= 60
);
-- Looks like our suspects are either Diana or Bruce, let's update our suspects list
DELETE FROM suspects
WHERE id NOT IN (
    SELECT suspects.id FROM suspects
    JOIN people ON suspects.id=people.id
    WHERE people.phone_number IN (
        SELECT caller FROM phone_calls
        WHERE month = 7
        AND day = 28
        AND duration <= 60
    )
);
-- While we're here let's check who our suspects called and save it into a new table
CREATE TABLE accomplice AS
SELECT id FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE month = 7
    AND day = 28
    AND duration <= 60
    AND caller IN (
        SELECT phone_number FROM people
        WHERE id IN (
            SELECT id FROM suspects
        )
    )
);
-- Our potential accomplices are Philip and Robin

-- Now let's check for flights out of Fiftyville that our suspects are taking
SELECT origin.city, dest.full_name, dest.city, hour, minute, people.name
FROM flights
JOIN airports AS origin ON origin_airport_id=origin.id
JOIN airports AS dest ON destination_airport_id=dest.id
JOIN passengers ON flights.id=passengers.flight_id
JOIN people ON passengers.passport_number=people.passport_number
WHERE month = 7
AND day = 29
AND people.id IN (
    SELECT id FROM suspects
);
-- Now we see that both Diana and Bruce took a flight that day, however Bruce took the earliest one so he must be our suspect
-- Now we know that Bruce was the theif and he escaped to New York City
-- Let's remove Diana from the suspects
DELETE FROM suspects
WHERE id IN (
    SELECT id FROM people
    WHERE name = 'Diana'
);
-- And let's see who our accomplice is
DELETE FROM accomplice
WHERE id IN (
    SELECT id FROM people
    WHERE phone_number NOT IN (
        SELECT receiver FROM phone_calls
        WHERE month = 7
        AND day = 28
        AND duration <= 60
        AND caller IN (
            SELECT phone_number FROM people
            WHERE id IN (
                SELECT id FROM suspects
            )
        )
    )
);
-- Our accomplice is Robin