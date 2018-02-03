/* ----------------------------------------------
 * Unit Test 4 
 * numHandCards function
 * ----------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void asserttrue(int a, int b, char* msg) {
	if(a != b) {
		printf("TEST FAILED: %s", msg);
	} else {
        printf("TEST PASSED: %s", msg);
    }
}

int main() 
{
	int i, count;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    initializeGame(numPlayer, k, seed, &G);

    // player 0 tests
    G.whoseTurn = 0;
    printf("Testing player 0 hand count...\n");
    for(i = 0; i <= 5; i++) {
    	G.handCount[0] = i;
    	printf("Test %d: ", i);
    	asserttrue(numHandCards(&G), i, "player 0 hand count\n");
    }

    // player 1 tests
    G.whoseTurn = 1;
    printf("Testing player 1 hand count...\n");
    for(i = 0; i <= 5; i++) {
    	G.handCount[1] = i;
    	printf("Test %d: ", i);
    	asserttrue(numHandCards(&G), i, "player 1 hand count\n");
    }
    
    return 0;
}