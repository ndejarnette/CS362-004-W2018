/*
 * RandomTestCard 3
 *
 * adventurer card random test
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
#define TEST_RANGE 1000

int handCountFails = 0;
int treasureFail = 0;

int main()
{
	srand(time(NULL));

	struct gameState testG;
	int failures = 0;
	int hCount, cardPosition, dCount, dkCount, result;

	int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	int i;
	for(i = 0; i < TEST_RANGE; i++) {

		int numPlayers = rand() % (4+1-1) + 1; // at most 4 players
		int seed = rand();
		int card = adventurer;
		int currentPlayer = rand() % numPlayers;
		int preTreasures = 0, postTreasures = 0, z = 0, drawn = 0, drawnTreasure = 0;
		int tempHand[MAX_DECK];

		initializeGame(numPlayers, kingdom, seed, &testG); // initialize game state

		hCount = testG.handCount[currentPlayer] = rand() % MAX_HAND + 1; // need at least 1 card in hand
		dkCount = testG.deckCount[currentPlayer] = rand() % MAX_DECK + 1; // need at least 1 card in deck
		dCount = testG.discardCount[currentPlayer] = rand() % MAX_DECK;
		cardPosition = testG.hand[currentPlayer][rand() % hCount] = card; // add adventurer card to hand


		
		int j;
		for(j = 0; j < dkCount; j++) {
			if(testG.deck[currentPlayer][j] == gold || testG.deck[currentPlayer][j] == silver || 
				testG.deck[currentPlayer][j] == copper) {
				preTreasures++;
			}
		}

		result = cardEffect(adventurer, 0, 0, 0, &testG, cardPosition, 0);

		if(result != 0)
			printf("failed\n");

		int i;
		for(i = 0; i < testG.deckCount[currentPlayer]; i++) {
			if(testG.deck[currentPlayer][i] == gold || testG.deck[currentPlayer][i] == silver || 
				testG.deck[currentPlayer][i] == copper) {
				postTreasures++;
			}
		}

		if(postTreasures == preTreasures)
			treasureFail++;

		if(hCount + 2 != testG.handCount[currentPlayer])
			handCountFails++;

	}

	if(treasureFail > 0)
		printf("Testing completed: treasure count was not correct %d times out of %d\n", treasureFail, i);
	if(handCountFails > 0)
	 	printf("Testing completed: hand count failed %d times out of %d\n", handCountFails, i);

	return 0;
}