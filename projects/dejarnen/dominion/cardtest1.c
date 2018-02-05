/*
 * CardTest 1
 *
 * smithy card test
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

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
	int result;
	int card;

	struct gameState G, testG;

	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, kingdom, seed, &G); // initialize game state
	memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	testG.hand[0][0] = smithy; // add smithy to player 1 hand
	asserttrue(testG.hand[0][0], smithy, "smithy card added to player 1 hand\n");
	card = testG.handCount[0];
	//printf("Card: %d\n", G.hand[0][card - 1]);

	result = cardEffect(smithy, 0, 0, 0, &testG, 0, 0);
	asserttrue(result, 0, "smithy return value\n"); // smithy returns
	asserttrue(G.handCount[0] + 2, testG.handCount[0], "3 cards added to player hand\n"); // 3 - 1 = 2 net card gain
	// first card should now be old last card
	asserttrue(testG.hand[0][0], G.hand[0][card - 1], "smithy card removed from player 1\n");
	//printf("Card: %d\n", testG.hand[0][0]);

	return 0;
}