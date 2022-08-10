#include <stdio.h>
#include <stdint.h>

/* 
* https://en.wikipedia.org/wiki/Cycle_detection
* Floyd's cycle-finding algorithm is a pointer algorithm
* that uses only two pointers, which move through the sequence
* at different speeds.
*
* This always assumes the given array has a length of n+1
* and n numbers, following the pigeonhole principle.
*/
int findDuplicateInArr(const int16_t arr[])
{
	int16_t tortoise = 0;
	int16_t hare = 0;

	for (;;) {
		tortoise = arr[tortoise];
		hare = arr[arr[hare]];

		if (tortoise == hare) break;
	}

	tortoise = 0;
	while (tortoise != hare) {
		tortoise = arr[tortoise];
		hare = arr[hare];
	}

	return tortoise;
}

int main(int argc, char* argv[])
{
	const int16_t arr[] = {7, 1, 4, 2, 5, 8, 3, 9, 6, 8};

	printf("%d", findDuplicateInArr(arr));

	return 0;
}
