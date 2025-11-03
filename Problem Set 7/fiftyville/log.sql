-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Step 1: Look up the crime scene report for July 28, 2021, on Humphrey Street.
-- Goal: Find details about the crime (what happened, when, where).
SELECT description
FROM crime_scene_reports
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND street = 'Humphrey Street';


-- Step 2: Review all interviews from July 28, 2021.
-- Goal: Gather witness clues about what happened and potential suspects.
SELECT name, transcript
FROM interviews
WHERE year = 2021
  AND month = 7
  AND day = 28;


-- Step 3: Identify people who left the bakery parking lot between 10:15 and 10:25 a.m.
SELECT people.name, people.license_plate
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute BETWEEN 15 AND 25
  AND bakery_security_logs.activity = 'exit';



-- Step 4: Identify people who withdrew money from the Leggett Street ATM earlier that morning.
-- From Eugene’s interview: the thief withdrew money at the Leggett Street ATM.
SELECT people.name, atm_transactions.amount
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.year = 2021
  AND atm_transactions.month = 7
  AND atm_transactions.day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw';


-- Step 5: Cross-reference people from the parking lot exit and ATM withdrawal.
-- Goal: Find who appears in both lists (likely the thief).
-- (Run the two queries separately and compare names manually in your results.)


-- Step 6: Identify the earliest flight departing Fiftyville the next day (July 29, 2021).
-- From Raymond’s interview: the thief took the earliest flight out of Fiftyville.
SELECT flights.id, airports.city AS destination_city, flights.hour, flights.minute
FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.year = 2021
  AND flights.month = 7
  AND flights.day = 29
ORDER BY flights.hour, flights.minute
LIMIT 1;


-- Step 7: List all passengers on that earliest flight.
-- Goal: Check if any suspect from earlier queries is on this flight (that person is the thief).
SELECT people.name
FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = (
  SELECT id
  FROM flights
  WHERE year = 2021
    AND month = 7
    AND day = 29
  ORDER BY hour, minute
  LIMIT 1
);


-- Step 8: Once you’ve identified the thief, check their phone calls on July 28.
-- From Raymond’s interview: the thief made a short call (< 1 minute) to their accomplice.
SELECT p2.name AS accomplice_name
FROM phone_calls
JOIN people p1 ON phone_calls.caller = p1.phone_number
JOIN people p2 ON phone_calls.receiver = p2.phone_number
WHERE phone_calls.year = 2021
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND p1.name = '[THIEF_NAME]'  -- Replace with thief’s name after Step 7
  AND phone_calls.duration < 60;


-- Step 9: Determine where the thief escaped to (the destination city).
-- We already found this in Step 6, but you can also verify:
SELECT airports.city
FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.id = (
  SELECT flight_id
  FROM passengers
  JOIN people ON passengers.passport_number = people.passport_number
  WHERE people.name = '[THIEF_NAME]'
);