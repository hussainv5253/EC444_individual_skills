#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S0 0 //start game
#define S1 1 //take out a random mole between 1 and 10
#define S2 2 //Wait for 3 secs, if hit, increase score, else drop down mole. go back to S1
#define S3 3 // time finsihed, display score andmove back to start

#define START 5
#define HIT 6
#define HIT_TIMEOUT 7
#define GAME_TIMEOUT 8
#define

static int score;

int main()
{

    int state = S0;
    int response; //entered by user

    while (1)
    {
        switch (state)
        {
        case S0:
            if (response == START)
            {
                state = S1; // start game
            }
            break;

        case S1:
            raise_one_mole();
            state = S2;
            break;

        case S2:
            if (response == HIT)
            {
                score++;
                state = S1;
            }
            if (response == HIT_TIMEOUT)
            {
                state = S1;
            }
            if (response == GAME_TIMEOUT)
            {
                state - S3;
            }
            break;

        case S3:
            display_score();
            state = S1;
            break;
        }
    }

    return 1;
}
