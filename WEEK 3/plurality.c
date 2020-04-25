#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9    //max candidates

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];  //create array of struct candidate
int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [candidate ...]\n", argv[0]);  //print uasage of ./file
        return 1;
    }

    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);  // print error for candidates overflow
        return 2;
    }

    int voters;
    string v;
    for(int i=0; i < candidate_count; i++) //put command line value in candidates global array
    {
    	candidates[i].name = argv[i+1];
    	candidates[i].votes = 0;
    }

  voters = get_int("Number of voters: ");
	for(int i=0; i < voters; i++)
	{
	    do
	    {
	    	v = get_string("vote: "); //get vote if not match ask again untill not true
	    }
	    while(vote(v));
    }
    print_winner();
}

//VOTE function for count vote put by voters
bool vote(string name)
{
    for(int i=0; i < candidate_count; i++)
    {
    	if ( (strcmp(name,candidates[i].name)) == 0)
    	{
    		candidates[i].votes++;
    		return 1;
	    }
    }

    printf("invalid candidate\n");
    return 0;
}

//Function which print winnwe candidate as per votes 
void print_winner()
{
	int vote=0;
    for(int i=0; i < candidate_count; i++)
    {
        if (candidates[i].votes > vote)
          vote = candidates[i].votes;
    }
    for(int i=0; i < candidate_count; i++)
    {
        if (candidates[i].votes == vote)
            printf("%s\n",candidates[i].name);
    }
}
