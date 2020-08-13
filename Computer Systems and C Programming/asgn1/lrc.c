#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;
faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};

const char * names[] = {"Dude", "Walter", "Maude", "Big Lebowski", "Brandt", "Bunny", "Karl", "Kieffer", "Franz", "Smokey"};

int fatedie(void);
int rollthedice(int a);
uint32_t left (uint32_t pos, uint32_t players);
uint32_t right(uint32_t pos, uint32_t players);

int main(void) {
    //initializes that seed and players are integers and gets user inputs for them
    int seed, players;
    printf("Random seed: ");
    scanf("%d", &seed);
    printf("How many players? ");
    scanf("%d", &players);
    
    //initializes the random number generator using the seed from the user input
    srand(seed);
    
    //calls rollthedice to figure out the winner of the game
    rollthedice(players);
    
    return 0;
}

int rollthedice(int a) {
    
    int p = 0;
    int pleft = 10;
    int center = 0;
    
    
    //bank accounts for the players
    int b[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i=0; i<a; i++) {
        b[i] = 3;
    }
    
    //while 2 or more players are left, the game continues.
    while(pleft >1) {
        int n = b[p];
        
        //if the person's bank balance is greater than 3, the player rolls 3 times.
        if (b[p] >= 3) {
            printf("%s rolls...", names[p]);
            for (int i = 0; i < 3; i++) {
                int ran = fatedie();
                //comparing the die roll with die array it determines what the palyer is going to do. Either gives one dollar to the left or right or puts one in the center or passes their turn
                if (die[ran] == die[0]) {
                    int l = left(p, a);
                    printf(" gives $1 to %s", names[l]);
                    // the amount is taken out of their bank account and given to the player on the left
                    b[p]--;
                    b[l]++;
                }
                else if (die[ran] == die[1]) {
                    int r = right(p, a);
                    printf(" gives $1 to %s", names[r]);
                    // the amount is taken out of their bank account and given to the player on the right
                    b[p]--;
                    b[r]++;
                }
                else if (die[ran] == die[2]) {
                    printf(" puts $1 in the pot");
                    // the amount is taken out of their bank account and put in the center
                    b[p]--;
                    center++;
                }
                else{
                    printf(" gets a pass");
                }
            }
        }
        //if the bank account balance is greater than 0 and less than 2, the players rolls the dice that amount of times
        else if (b[p] <3 && b[p]>0) {
            printf("%s rolls...", names[p]);
            int g = b[p];
            for (int i = 0; i < g; i++) {
                int ran = fatedie();
                //comparing the die roll with die array it determines what the palyer is going to do. Either gives one dollar to the left or right or puts one in the center or passes their turn
                if (die[ran] == die[0]) {
                    int l = left(p, a);
                    printf(" gives $1 to %s", names[l]);
                    // the amount is taken out of their bank account and given to the player on the left
                    b[p]--;
                    b[l]++;
                }
                else if (die[ran] == die[1]) {
                    int r = right(p, a);
                    printf(" gives $1 to %s", names[r]);
                    // the amount is taken out of their bank account and given to the player on the right
                    b[p]--;
                    b[r]++;
                }
                else if (die[ran] == die[2]) {
                    printf(" puts $1 in the pot");
                    // the amount is taken out of their bank account and put in the center
                    b[p]--;
                    center++;
                }
                else{
                    printf(" gets a pass");
                }
            }
        }
        //determines the amount of players left by checking how many players hav more than 0 dollars in the bank account
        pleft = 0;
        for (int i = 0; i<10; i++) {
            if (b[i] != 0) {
                pleft++;
            }
        }
        //if one player is left, that person gets the winning message with the pot amount and their bank balance is printed.
        if (pleft==1) {
            for (int i = 0; i<10; i++) {
                if (b[i] != 0) {
                    printf("\n%s wins the %d$ pot with %d left in the bank!\n", names[i], center, b[i]);
                }
            }
        }
        if (n>0) {
            printf("\n");
        }
   
        //the person to the right goes next
        p = right(p, a);
        
    }
    return 0;
}

//makes sure that the random number is in the range of 0 to 6
int fatedie(void) {
    return rand()%6;
}

//The position of the person left is returned.
uint32_t left(uint32_t pos, uint32_t players) {
    return ((pos + players - 1)% players);
}

//The position of the person right is returned.
uint32_t right(uint32_t pos, uint32_t players) {
    return ((pos+1) % players);
}


