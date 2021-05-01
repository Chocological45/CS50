#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long cardNumber = get_long("Number: ");

    //Length of cardNumber
    length = log10(cardNumber) + 1;

    if (length == 15)
    {
        printf(cardNumber);

    } else if (length == 16) {
        printf(cardNumber);

    } else if (length == 13) {
        printf(cardNumber);

    }


}