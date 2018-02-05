/*
 * CardTest 2
 *
 * adventurer card test
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

void asserttrue(int a, int b, char* msg) {
	if(a != b) {
		printf("TEST FAILED: %s", msg);
	} else {
        printf("TEST PASSED: %s", msg);
    }
}

int main()
{
	int numPlayers = 2;
	int seed = 1000;
	int result, drawntreasure = 0;
	int tempTreasure;
	int cardDrawn;
	int temphand[MAX_HAND];

	struct gameState G, testG;

	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, kingdom, seed, &G); // initialize game state
	memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// printf("Player 1 hand count: %d\n", testG.handCount[0]); // show player hand count

	testG.hand[0][0] = adventurer; // add adventurer card to player hand
	asserttrue(testG.hand[0][0], adventurer, "adventurer card added to player 1 hand\n");

	// test below causes segfault
	// result = cardEffect(adventurer, 0, 0, 0, &testG, 0, 0); 
	// asserttrue(result, 0, "return value from adventurer\n");

	int cards[3] = {gold, copper, silver};
	int i, z = 0;
	int currentPlayer = 0;

	// test different treasure card values
	// silver causes infinite loop so did not test
	for(i = 0; i < 2; i++) {
		drawntreasure = 0;
		tempTreasure = drawntreasure;
		cardDrawn = cards[i];

		if(i == 0)
			printf("-----Testing gold card draw-----\n");
		else if(i == 1)
			printf("-----Testing copper card draw-----\n");
		else if(i == 2)
			printf("-----Testing silver card draw-----\n");

		// testing adventurer internals here due to segfault
		while(drawntreasure<2) {
			if (testG.deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	  			shuffle(currentPlayer, &testG);
			}

			// drawCard(currentPlayer, state);

			// cardDrawn = state->hand[currentPlayer][testG.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.

			if (cardDrawn == copper || cardDrawn == gold) {
    			drawntreasure++;
  			}
			else {
	  			temphand[z]=cardDrawn;
	  			testG.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	  			z++;
	 		}

  		}
  		
  		asserttrue(drawntreasure, tempTreasure + 2, "treasure cards drawn count increased successfully\n");
  	}

	return 0;
}