/* ----------------------------------------------
 * Unit Test 3 
 * compare function
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
	int result, a, b;

	// test a greater
	a = 5;
	b = 2;
	result = compare(&a, &b);
	asserttrue(result, 1, "a is greater test\n");

	// test a is less
	a = 1;
	b = 3;
	result = compare(&a, &b);
	asserttrue(result, -1, "a is less test\n");

	// test a and b are equal
	a = 4;
	b = 4;
	result = compare(&a, &b);
	asserttrue(result, 0, "a and b are equal\n");

	// test for negative values
	// test a greater
	a = -2;
	b = -7;
	result = compare(&a, &b);
	asserttrue(result, 1, "negative value a is greater test\n");

	// test a is less
	a = -3;
	b = -2;
	result = compare(&a, &b);
	asserttrue(result, -1, "negative value a is less test\n");

	// test a and b are equal
	a = -4;
	b = -4;
	result = compare(&a, &b);
	asserttrue(result, 0, "negative value a and b are equal\n");



	return 0;
}