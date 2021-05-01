#Import get_int function from cs50 lib
 

#American Express: 15 digits, starts with 34 or 37
#MasterCard: 16 digits, starts with 51, 52, 53, 54, 55
#Visa: 13 or 16 digits, starts with 4


#Get credit card number
number = get_string("Number: ")

#Reverse credit card number so that we can double every second digit
number = number[::-1]
reverseNumber = number


#Convert input into integer list
number = [int(x) for x in number]


#CheckSum
#Double every second digit in the credit card
validateCard = list()
digits = list(enumerate(number, start=1))

#Solution 1
#More mathematical approach to splitting values
#for index, digit in digits:
#    if index % 2 == 0:
#        if (digit * 2) < 10:
#            validateCard.append(digit * 2)
#        else:
#            validateCard.append((digit*2)%10)
#            validateCard.append((digit*2)//10)
#    else:
#        validateCard.append(digit)

#total = sum(validateCard)

#Solution 2
#More concise python method
string = ''.join(map(str,validateCard))
newList = [int(x) for x in string]
total = sum(newList)

if total % 10 == 0:
    if len(number) == 15:
        if int(reverseNumber) % 100 == 43 or int(reverseNumber) % 100 == 73:
            print("AMEX\n")

    elif len(number) == 16:
        if int(reverseNumber) % 10 == 4:
            print("VISA\n")

        elif int(reverseNumber) % 100 == 15 or int(reverseNumber) % 100 == 25 or int(reverseNumber) % 100 == 35 or int(reverseNumber) % 100 == 45 or int(reverseNumber) % 100 == 55:
            print("MASTERCARD\n")

    elif len(number) == 13:
        if int(reverseNumber) % 100 == 15 or int(reverseNumber) % 100 == 25 or int(reverseNumber) % 100 == 35 or int(reverseNumber) % 100 == 45 or int(reverseNumber) % 100 == 55:
            print("MASTERCARD\n")
    else:
        print("INVALID\n")

else:
    print("INVALID\n")