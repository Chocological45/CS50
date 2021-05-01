from cs50 import get_string
import string
import re

#Get the text input and set the initial count values
text = get_string("Text: ")
ltrs = 0
wrds = 1
snts = 0


#Count letters
#For characters in text if alphabetic then increment count
for letter in text:
    if letter.isalpha() == True:
        ltrs += 1


#Count words
#Remove all selected punctuation
textFiltered = text + ' '
regex = re.compile("[,\.!?']")
textFiltered = regex.sub('', textFiltered)

#For all characters in text if text is a space increment count
for i in range(len(textFiltered)):
    if (text[i].isspace()):
        wrds += 1



#Count sentences
#For all characters in text if character is end of sentence punctuation then increment count
for letter in text:
    if letter == '.' or letter == '?' or letter == '!':
        snts += 1



#Calculate values of L and S
L = 100 * ltrs/wrds
S = 100 * snts/wrds

#Calcuate the index
index = 0.0588 * L - 0.296 * S - 15.8

#Calculate the grade
grade = round(index)


#Check and output the grade with bounds edited
if grade <= 0:
    print("Before Grade 1\n")
elif grade >= 16:
    print("Grade 16+\n")
elif grade > 0:
    print("Grade", grade,"\n")