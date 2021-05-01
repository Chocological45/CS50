#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int i = 0;
    float ltrs = 0, wrds = 0, snts = 0;



    //Count Letters
    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            ltrs++;

        }
    }
    //printf("Letters: %f\n", ltrs);



    //Count Words
    for (i = 0; text[i] != '\0'; i++)
    {
        if (isspace(text[i]))
        {
            if (!(isspace(text[i+1])))
            {
                wrds++;

            }
        }

    }
    wrds++;
    //printf("Words: %f\n", wrds);



    //Count Sentences
    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            snts++;

        }

    }
    //printf("Sentences: %f\n", snts);



    float L = 100 * ltrs/wrds, S = 100 * snts/wrds;
    //printf("%f\n", L);
    //printf("%f\n", S);

    double index = 0.0588 * L - 0.296 * S - 15.8;

    int grade = round(index);
    //printf("%f\n", index);
    //printf("%d\n", grade);

    if (grade <= 0)
    {
        printf("Before Grade 1\n");

    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");

    }
    else if (grade > 0)
    {
        printf("Grade ""%d\n", grade);

    }


}