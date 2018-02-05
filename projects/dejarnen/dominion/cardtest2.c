/*
 * CardTest 2
 *
 * village card test
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

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
	int count;

	struct gameState G, testG;

	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, kingdom, seed, &G); // initialize game state
	memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	testG.hand[0][0] = village; // add village card to hand
	asserttrue(testG.hand[0][0], village, "village card added to player 1 hand\n");
	count = testG.handCount[0];

	result = cardEffect(village, 0, 0, 0, &testG, 0, 0);
	asserttrue(result, 0, "village return value\n");
	asserttrue(testG.handCount[0], G.handCount[0], "player 1 handcount\n"); // no net change in hand count
	asserttrue(testG.numActions, G.numActions + 2, "2 actions added for player 1\n"); // +2 actions
	asserttrue(testG.hand[0][0], G.hand[0][count - 1], "village card removed from player 1 hand\n");


	return 0;
}