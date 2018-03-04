/* ----------------------------------------------
 * Unit Test 1 
 * getCost function
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
    // hardcode card costs with enum position (dominion.h)
    int cardCosts[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,
    	3,4,3,5,3,5,3,4,2,5,4,4,4};

    int i;
    // loop through all cards
    for(i = 0; i < 27; i++) {
    	int x = getCost(i);
    	asserttrue(x, cardCosts[i], "card cost match\n");
    }

    // test for invalid card number 
    int invalid = getCost(53);
    asserttrue(invalid, -1, "invalid card number\n");


	return 0;
}