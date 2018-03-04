/* ----------------------------------------------
 * Unit Test 2 
 * isGameOver function
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
    int i, result;
    struct gameState G;

    // initializeGame(numPlayer, k, seed, &G);

    // initialize some supply card counts
    for(i = 0; i < 27; i++) {
        G.supplyCount[i] = 3;
    }

    // empty province deck test
    G.supplyCount[province] = 0; 
    result = isGameOver(&G);
    asserttrue(result, 1, "empty province card deck.\n");

    // resupply
    for(i = 0; i < 27; i++) {
        G.supplyCount[i] = 3;
    }

    // test 3 empty supply piles
    for(i = 0; i < 3; i++) {
        G.supplyCount[i] = 0;
    }
    result = isGameOver(&G);
    asserttrue(result, 1, "3 empty supply piles.\n");

    // resupply
    for(i = 0; i < 27; i++) {
        G.supplyCount[i] = 3;
    }
    // full supply piles
    result = isGameOver(&G);
    asserttrue(result, 0, "full supply piles.\n");


	return 0;
}