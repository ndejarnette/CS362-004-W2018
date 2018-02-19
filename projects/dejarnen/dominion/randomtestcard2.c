/*
 * RandomTestCard 2
 *
 * village card random test
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"
#define TEST_RANGE 1000

int handCountFails = 0;
int deckCountFails = 0;
int actionCountFails = 0;
int discardFail = 0;

// check for cards added to hand and card removed from hand 
void villageTestOracle(struct gameState *state, int player, int prevHandCount, int prevActions, int prevDeck, int handPos) {
	if(state->deckCount[player] != (prevDeck - 1)) {
		// printf("Test failed: not enough cards added to player %d hand.\n", player);
		// printf("Hand count before: %d\n", prevHandCount);
		// printf("Hand count after: %d\n", state->handCount[player]);
		deckCountFails++;
	}
	if(state->handCount[player] != prevHandCount) {
		handCountFails++;
	}
	if(state->hand[player][handPos] == village) {
		//printf("Test failed: %s card not removed from hand.\n", TESTCARD);
		discardFail++;
	}
	if(state->numActions != prevActions + 2) {
		//printf("FAIL: incorrect action\n");
		actionCountFails++;
	}
}

int main()
{
	srand(time(NULL));

	struct gameState testG, G;
	int failures = 0;
	int hCount, cardPosition, dCount, dkCount, actions, result;

	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	int i;
	for(i = 0; i < TEST_RANGE; i++) {

		int numPlayers = rand() % (4+1-1) + 1; // at most 4 players
		int seed = rand();
		int card = village;
		int currentPlayer = rand() % numPlayers;

		initializeGame(numPlayers, kingdom, seed, &G); // initialize game state
		memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

		hCount = testG.handCount[currentPlayer] = rand() % MAX_HAND + 1; // need at least 1 card in hand
		dCount = testG.discardCount[currentPlayer] = rand() % MAX_DECK;
		dkCount = testG.deckCount[currentPlayer] = rand() % MAX_DECK + 1; // need at least 1 card in deck
		cardPosition = testG.hand[currentPlayer][rand() % hCount] = card; // add village card to hand
		actions = testG.numActions = rand();
		testG.whoseTurn = currentPlayer;
		//printf("Before card effect: %d\n", i);
		result = cardEffect(card, -1, -1, -1, &testG, cardPosition, 0);
		//printf("After card effect\n");
		if(result != 0)
			printf("error!\n");

		villageTestOracle(&testG, currentPlayer, hCount, actions, dkCount, cardPosition);
	}

	if(handCountFails > 0)
		printf("Testing completed: hand count was not correct %d times out of %d\n", handCountFails, i);
	if(discardFail > 0)
		printf("Testing completed: village card was not discarded %d times out of %d\n", discardFail, i);
	if(actionCountFails > 0)
		printf("Testing completed: action count failed %d times out of %d\n", actionCountFails, i);
	if(deckCountFails > 0)
		printf("Testing completed: deck count failed %d times out of %d\n", deckCountFails, i);
	if(handCountFails == 0 && discardFail == 0 && actionCountFails == 0 && deckCountFails == 0)
		printf("Testing completed: %d tests failed out of %d\n", 0, i);
	

	return 0;
}