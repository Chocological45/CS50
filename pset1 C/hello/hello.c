#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Gets string value for name, from get_string under cs50 lib
    string name = get_string("What is your name?\n");
    //Outputs string as part of text
    printf("hello, %s\n", name);
}