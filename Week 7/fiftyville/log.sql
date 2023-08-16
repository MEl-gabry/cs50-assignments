-- Keep a log of any SQL queries you execute as you solve the mystery.

-- This command was used to discover in greater detail what happened at the crime scene.
SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2020 AND street = "Chamberlin Street";

-- This command was used to retrive the transcripts of the interviews of the witnesses of the crime scene that day.
SELECT transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2020;

-- This command was to see the license plates of all cars that departed the courthouse during the morning of the 28th, since one of the interviews mentioned the theif driving away from the courthouse.
SELECT license_plate FROM courthouse_security_logs WHERE activity = "exit" AND hour = 10 AND minute > 15 AND minute <= 25 AND day = 28 AND month = 7 AND year = 2020;

-- This command was to find all the passport numbers of all the people who left on the earliest flight from the Fiftyville airport on the 29th of July, 2020.
SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour LIMIT 1);

-- This command was to discover the airport the thief escaped to.
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = (SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour LIMIT 1));

-- This command was to find out the potential phone number of the thief.
SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60;

-- This command was to find the person ids of all the people who withdrew money on that day at the ATM on Fifer Street.
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020);

-- This command was to discover the name of the theif.
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour LIMIT 1)) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE activity = "exit" AND hour = 10 AND minute > 15 AND minute <= 25 AND day = 28 AND month = 7 AND year = 2020) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020));

-- This command was to discover the accomplice of the theif.
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = "Ernest"));