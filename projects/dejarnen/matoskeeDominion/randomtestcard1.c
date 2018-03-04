/*
 * RandomTestCard 1
 *
 * smithy card random test
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"
#define TEST_RANGE 1000

// keep track of test failures
int handCountFails = 0;
int discardCountFails = 0;

// check for cards added to hand and card removed from hand 
// might need to check for deckcount

// refactored for teammate code testing
void smithyTestOracle(struct gameState *state, int prevHandCount, int handPos) {
	//printf("Whose turn in test oracle: %d\n", state->whoseTurn);
	if(state->handCount[state->whoseTurn] != prevHandCount + 2) {
		printf("Test failed: not enough cards added to player %d hand.\n", state->whoseTurn);
		printf("Hand count before: %d\n", prevHandCount);
		printf("Hand count after: %d\n", state->handCount[state->whoseTurn]);
		printf("Expected hand count: %d\n", prevHandCount + 2);
		printf("##################################\n");
		handCountFails++;
	}
	if(state->hand[state->whoseTurn][handPos] == smithy) {
		// printf("Test failed: %s card not removed from hand.\n", TESTCARD);
		discardCountFails++;
	}
}

int main()
{
	srand(time(NULL));

	struct gameState testG;
	int result, oracleResult, count, cardPosition;

	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	int i;
	for(i = 0; i < TEST_RANGE; i++) {
		int numPlayers = rand() % (4+1-1) + 1;
		int seed = rand();
		int card = smithy;
		int currentPlayer = rand() % numPlayers;

		initializeGame(numPlayers, kingdom, seed, &testG); // initialize game state

		testG.whoseTurn = currentPlayer;
		count = testG.handCount[currentPlayer] = rand() % MAX_HAND + 1;
		testG.discardCount[currentPlayer] = rand() % MAX_DECK;
		testG.deckCount[currentPlayer] = rand() % MAX_DECK + 1;
		cardPosition = testG.hand[currentPlayer][rand() % count] = card; // add smithy card to hand

		//card_smithy(currentPlayer, &testG, cardPosition);

		// testing for teammate code
		//printf("Whose turn: %d\n", currentPlayer);
		cardSmithy(&testG, cardPosition);

		smithyTestOracle(&testG, count, cardPosition);
	}
	
	if(handCountFails > 0)
		printf("Testing completed: hand count was not correct %d times out of %d\n", handCountFails, i);
	if(discardCountFails > 0)
		printf("Testing completed: smithy card was not discarded %d time out of %d\n", discardCountFails, i);
	if(handCountFails == 0 && discardCountFails == 0)
		printf("Testing completed: All tests passed\n");

	return 0;
}