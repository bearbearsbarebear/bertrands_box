#include <stdio.h>
#include <stdint.h>

// Returns the index of the starting point of the cycle, or -1 if no cycle was found.
int findDuplicateInArr(const int16_t arr[], uint16_t len)
{
	uint16_t tortoise = 0;
	uint16_t hare = 0;

	// Move the tortoise and hare pointers through the array until they meet
	// at the starting point of the cycle
	for (;;) {
		tortoise = arr[tortoise];
		hare = arr[arr[hare]];

		// Check if the tortoise and hare pointers have reached the end of the array
		if (tortoise >= len || hare >= len) {
			// The array does not contain a cycle
			return -1;
		}

		if (tortoise == hare) break;
	}

	// Move the tortoise pointer back to the beginning and move both pointers
  	// until they meet again at the starting point of the cycle
	tortoise = 0;
	while (tortoise != hare) {
		tortoise = arr[tortoise];
		hare = arr[hare];
	}

	return tortoise;
}

int main(int argc, char* argv[])
{
	printf("%d", findDuplicateInArr((int16_t[]) {7, 1, 4, 2, 5, 10, 11, 12, 3, 9, 6, 8, 12}, 13));

	return 0;
}
