# TODO
import sys
from cs50 import SQL


if len(sys.argv) != 2:
    # Exit if missing arguments
    sys.exit("Usage: python roster.py house")

# Connect to database
db = SQL("sqlite:///students.db")

# Execute SELECT query on database
arr = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first ASC;", sys.argv[1])

# For all the entries taken from database
# Iterate and take the first, middle, last and birth date of each person and print string
for x in range(len(arr)):
    first = arr[x]["first"]
    middle = arr[x]["middle"]
    last = arr[x]["last"]
    birth = arr[x]["birth"]

    if (middle == ""):
        print(first + " " + last + ", born " + str(birth))
    else:
        print(first + " " + middle + " " + last + ", born " + str(birth))
