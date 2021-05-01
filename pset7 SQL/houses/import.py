# TODO
import sys
import csv
from cs50 import SQL


if len(sys.argv) != 2:
    # Exit if missing arguments
    sys.exit("Usage: python import.py students.csv")

# Connect to database
db = SQL("sqlite:///students.db")


# Open the CSV file
fs = open(sys.argv[1])
characters = list(csv.reader(fs))

# Remove the header list from the characters list
characters.pop(0)

# For all the items in characters
for x in range(len(characters)):
    # Get the name, house and birth date
    name = characters[x][0]
    house = characters[x][1]
    birth = characters[x][2]

    # Split the name and get the first, middle and last names
    name = name.split(' ')

    if (len(name) == 3):
        first = name[0]
        middle = name[1]
        last = name[2]

    elif (len(name) == 2):
        first = name[0]
        middle = ''
        last = name[1]

    # Insert into the table
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);", (first, middle, last, house, birth))