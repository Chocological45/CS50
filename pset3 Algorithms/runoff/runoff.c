#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}








// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    //For all candidate options
    for (int i = 0; i < candidate_count; i++)
    {
        //If valid name given
        if (strcmp(name, candidates[i].name) == 0)
        {
            //Add voter's preference to preferences array
            preferences[voter][rank] = i;
            return true;

        }
    }
    return false;
}



// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //For all candidates and voters
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; i++)
        {
            //Check if not eliminated
            if (candidates[preferences[i][j]].eliminated == false)
            {
                //Increment their vote count
                candidates[preferences[i][j]].votes++;
                break;

            }
            //If they are eliminated
            else if (candidates[preferences[i][j]].eliminated == true)
            {
                //Go to the next prefered candidate
                candidates[preferences[i][j+1]].votes++;
                break;

            }
        }
    }
    return;
}



// Print the winner of the election, if there is one
bool print_winner(void)
{
    //For all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //Redundancy check if candidate is not marked as eliminated
        if (candidates[i].eliminated == false)
        {
            //If candidate has more than 50% of votes
            if (candidates[i].votes > voter_count / 2)
            {
                //They win
                printf("%s\n", candidates[i].name);
                return true;

            }
        }
    }
    return false;
}



// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int i, a = INT_MAX, b = INT_MAX;

    //For all candidates not eliminated
    for (i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            //If candidates votes are lower than a
            if (candidates[i].votes < a)
            {
                //swap values and repeat until lowest value is found
                b = a;
                a = candidates[i].votes;

            }
        }
    }

    return a;
}



// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int notEliminatedCount = 0;
    int isMinimumCount = 0;

    //For all candidates that are not eliminated
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            //Increment number not eliminated
            notEliminatedCount++;

            //Check if candidates votes are equal to minimum
            if (candidates[i].votes == min)
            {
                //Increment minimum count
                isMinimumCount++;

            }
        }
    }

    //If number of minimums is equal to number of viable candidates then it is a tie
    if (notEliminatedCount == isMinimumCount)
    {
        return true;

    }
    return false;
}



// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //For all candidates check if eliminated
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            //Check if the candidates vote count is equal to the minimum number of votes
            if (candidates[i].votes == min)
            {
                //If true then eliminate candidate
                candidates[i].eliminated = true;

            }
        }
    }
    return;
}
