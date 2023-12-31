#include <cs50.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool isStringEqual(string str1, string str2);
bool isLoop(int index, int target);
bool isPointed(int target);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (isStringEqual(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int change;
    pair tempPair;
    int iStrength;
    int pStrength;

    for (int i = 0; i < pair_count; i++)
    {
        change = 0;

        for (int j = 1; j < pair_count - i; j++)
        {
            iStrength = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            pStrength = preferences[pairs[j - 1].winner][pairs[j - 1].loser] - preferences[pairs[j - 1].loser][pairs[j - 1].winner];
            if (iStrength > pStrength)
            {
                tempPair = pairs[j];
                pairs[j] = pairs[j - 1];
                pairs[j - 1] = tempPair;
                change = 1;
            }
        }

        if (!change)
        {
            return;
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!isLoop(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int connect;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!isPointed(i))
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }

    return;
}

bool isStringEqual(string str1, string str2)
{
    int n = 0;
    while (str1[n] != '\0')
    {
        if (str1[n] != str2[n])
        {
            return false;
        }
        n++;
    }
    if (str1[n] == '\0' && str2[n] == '\0')
    {
        return true;
    }
    return false;
}

bool isLoop(int target, int index)
{
    if (locked[index][target])
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[index][i])
        {
            if (isLoop(target, i))
            {
                return true;
            }
        }
    }

    return false;
}

bool isPointed(int target)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][target])
        {
            return true;
        }
    }

    return false;
}