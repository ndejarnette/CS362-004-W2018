/*
 * CardTest 2
 *
 * council_room card test
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

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
	printf("---- testing with 2 players ----\n");
	testG.hand[0][0] = council_room; // add council_room card to hand
	asserttrue(testG.hand[0][0], council_room, "council_room card added to player 1 hand\n");

	// get hand counts for both players
	count1 = testG.handCount[0];
	count2 = testG.handCount[1];
	
	testG.whoseTurn = 0; // player 1 turn

	result = cardEffect(council_room, -1, -1, -1, &testG, 0, 0);
	asserttrue(result, 0, "return value for council_room through card effect\n");
	asserttrue(G.handCount[0] + 3, testG.handCount[0], "4 cards added to player 1 hand\n");
	asserttrue(testG.numBuys, G.numBuys + 1, "number of player 1 buys increased by 1\n" );
	asserttrue(testG.handCount[1], count2 + 1, "player 2 draws a card\n");

	printf("\n---- testing with 3 players ----\n");

	numPlayers = 3;

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayers, kingdom, seed, &G); // initialize a new game
	memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

	testG.hand[1][0] = council_room; // add council_room card to player 2 hand
	asserttrue(testG.hand[1][0], council_room, "council_room card added to player 2 hand\n");

	// get hand counts for all players
	count1 = testG.handCount[0];
	count2 = testG.handCount[1];
	count3 = testG.handCount[2];
	
	testG.whoseTurn = 1; // player 2 turn

	result = cardEffect(council_room, -1, -1, -1, &testG, 0, 0);
	asserttrue(result, 0, "return value for council_room through card effect\n");
	asserttrue(G.handCount[1] + 3, testG.handCount[1], "4 cards added to player 2 hand\n");
	asserttrue(testG.numBuys, G.numBuys + 1, "number of player 2 buys increased by 1\n" );
	asserttrue(testG.handCount[0], count1 + 1, "player 1 draws a card\n");
	asserttrue(testG.handCount[2], count3 + 1, "player 3 draws a card\n");

	return 0;
}