#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;

    //Gets input until valid input is given
    do {
        change = get_float("Change owed: ");

    } while (change < 0);

    //Instantiates variable for output coins
    int coins = 0;

    //Converts change from dollars to cents
    change = round(change * 100);


    //Checks for 25 cents
    while (change >= 25)
    {
        change -= 25;
        coins ++;
    }

    //Checks for 10 cents
    while (change >= 10)
    {
        change -= 10;
        coins ++;
    }

    //Checks for 5 cents
    while (change >= 5)
    {
        change -= 5;
        coins ++;
    }

    //Checks for 1 cent
    while (change >= 1)
    {
        change -= 1;
        coins ++;
    }

    //Outputs coins value
    printf("%d\n", coins);

}