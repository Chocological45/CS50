#include <stdio.h>
#include <cs50.h>

////////////////////////////////////////////////////////////////////////////////
//
//  Function name: main()
//  Purpose: Handles the user input of the program
//
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    bool check = false;
    do
    {
        int val = get_int("Height: ");
        if (val > 0 && val < 9)
        {
            check = true;




////////////////////////////////////////////////////////////////////////////////
//
//  Pyramid output process based on user's input of 'val'
//
////////////////////////////////////////////////////////////////////////////////
            //Counts down each row
            for (int i = 1; i <= val; i++)
            {

                // Row number: i
                //Spaces required for row
                int spaces = val - i;

                //Hashes required for each row
                int hashes = val - spaces;

                //Counts through spaces and prints them
                for (int j = 1; j <= spaces; j++)
                {
                    printf(" ");

                }

                //Counts through the hashes and prints them
                for (int j = 1; j <= hashes; j++)
                {
                    printf("#");

                }

                //Outputs two space gap
                printf("  ");

                //Outputs the second side of the pyramid
                for (int j = 1; j <= hashes; j++)
                {
                    printf("#");

                }

                //Goes to next line for next row output
                printf("\n");

            }
////////////////////////////////////////////////////////////////////////////////





        }
    }
    while (check == false);
}