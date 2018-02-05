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
	int result;
	int count1, count2, count3;

	struct gameState G, testG;

	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, kingdom, seed, &G); // initialize game state
	memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	result = cardEffect(adventurer, 0, 0, 0, &testG, 0, 0);
	asserttrue(result, 0, "return value from adventurer\n");

	return 0;
}