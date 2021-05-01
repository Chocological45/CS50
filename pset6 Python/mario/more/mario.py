#Import get_int function from cs50 lib
from cs50 import get_int

#Set a while loop condition
condition = True

#Continue to loop until condition met
while condition:
    #Get height input
    n = get_int("Height: ")
    
    #Do a check on input height
    if 1 <= n < 9:
        #Loop through the height value and produce the graphic
        for i in range(n):
            #Calculate the spaces and hashes required for graphic
            spaces = n - (i + 1)
            hashes = n - spaces
    
            #Output the graphics using calculated values
            for j in range(spaces):
                print(" ", end = "")
    
            for j in range(hashes):
                print("#", end = "")
    
            print("  ", end = "")
    
            for j in range(hashes):
                print("#", end = "")
    
            print("\n", end = "")
            
            #Set condition to false and end loop
            condition = False
    
    else:
        #If height check fails output message
        print("Pick a number in the range of 1 and 8")