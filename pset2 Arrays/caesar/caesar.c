#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//For the check secondary function
bool check(string s);


int main( int argc, char * argv[] )
{
    //Check if the arguments provided are valid for the function
    if (argc != 2 || check(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;

    }

    //Convert key input into integer to be used
    int key = atoi(argv[1]);

    //Check that key is not 0
    if (key > 0)
    {
        //Get plaintext input
        string pt = get_string("plaintext:  ");



        printf("ciphertext: ");

        //For all characters in input
        for (int i = 0; i < strlen(pt); i++)
        {

            //If character is alphabetic
            if (isalpha(pt[i]))
            {
                //and is upper case
                if (isupper (pt[i]))
                {
                    //Convert to ciphered text
                    printf ("%c", (((pt[i] - 64) + key) % 26) + 64);

                }
                else
                {
                    //Convert to ciphered
                    printf ("%c", (((pt[i] - 96) + key) % 26) + 96);

                }
            }
            else
            {
                //Output non-alphabetic character
                printf ("%c", pt[i]);

            }
        }

        //Newline
        printf("\n");
        return 0;


    }
}



bool check(string s)
{
    //Check that argument is not a negative integer
    if (s[0] == '-')
    {
        return true;

    }

    //Compare number of numeric characters to total number of characters in string argument
    int count = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[i]))
        {
            count++;

        }

    }

    //If the number of numeric characters is equal to the total number of characters
    if (count == strlen(s))
    {
        //Ready to go!
        return false;

    }

    return true;
}