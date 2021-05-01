import csv
import sys
import re

def main():

    # Check the arguments passed for errors
    if len(sys.argv) != 3:
        # Exit if missing arguments
        sys.exit("Usage: python dna.py data.csv sequence.txt")


    # Read the Data file
    fData = open(sys.argv[1])
    data = list(csv.reader(fData))

    # Read the Sequence file
    fDna = open(sys.argv[2])
    dna = fDna.read()

    # Declare arrays for STR counting and finding the longest consecutive count
    strCount = []
    lChain = []

    # For all the values to look for in the database
    for x in range(len(data[0]) - 1):

        # Find all the STR chains
        chains = re.findall(rf'(?:{data[0][x + 1]})+', dna)

        # Find the longest consecutive chain of STR with default check value if there is no chain
        lChain.append(max(chains, default = 0))

        # Check if the chain is empty or not
        if (lChain[0] != 0):

            # Calculate the length of the chain
            strCount.append(int(len(lChain[x])/len(data[0][x + 1])))


    # Declare array for names
    names = []

    # Split data into two lists for ease of comparison
    # Move the names to another list and remove them from the start of each database entry
    for x in range(len(data) - 1):
        names.append(data[x + 1].pop(0))

    # Remove the column titles list from data
    data.pop(0)

    # Convert the STR count to string to easily compare with data from database
    strCount = list(map(str, strCount))

    # Check if data is in strCount
    if strCount in data:
        # Find the index of the STR count in data and output the name using that index
        i = data.index(strCount)
        print(names[i])

    else:
        print("No match")

    sys.exit()



main()