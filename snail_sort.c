#include <stdlib.h>

#define SIZE 3

/*
snail sort:
array = [[1,2,3],
         [4,5,6],
         [7,8,9]]
snail(array) #=> [1,2,3,6,9,8,7,4,5]
*/

// rows=cols
int* snail(size_t* outsz, int** mx, size_t rows, size_t cols)
{
	size_t vertical, horizontal;
	int* output = (int*) calloc((*outsz = rows*rows), sizeof(int));

	// Setting initial value before starting the loop
	vertical = horizontal = rows = 0;
	cols--;

	while (rows < cols) {
		// Walks towards east (stops at column limit)
		while (horizontal < cols) *output++ = mx[vertical][horizontal++];

		// Walks toward south (stops at column limit)
		while (vertical < cols) *output++ = mx[vertical++][horizontal];

		// Walks toward west (stops at row limit)
		while (horizontal > rows) *output++ = mx[vertical][horizontal--];

		// Walks toward north (stops at row limit)
		while (vertical > rows) *output++ = mx[vertical--][horizontal];

		/*
		 *When it's here, it means it finished a loop;
		 *So what it does is it jumps the loop
		 *further inside, which means closing
		 *the outer part of the matrix and
		 *starting at the upper-left part of the
		 *remaining matrix
		 **********************************************
		 *Vertical and Horizontal starts at (0, 0) then
		 *jumps to (1, 1) etc
		 *Rows starting at 0 and cols at SIZE
		 *Since the idea is closing more and more 
		 *Towards the inner side, add rows and subs cols
		 *When both are equal, means it's finished
		*/
		vertical++, horizontal++, rows++, cols--;
	}

	if (rows == cols) *output++ = mx[vertical][horizontal];

	return output - *outsz;
}

int main(int argc, char* argv[])
{
	size_t size;
	int** test_array;

	// Just creating and filling test_array
	test_array = (int**) malloc(sizeof(int*) * SIZE);
	for (int i = 0; i < SIZE; ++i) {
		test_array[i] = (int*) malloc(sizeof(int) * SIZE);
	}

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			test_array[i][j] = (i*SIZE) + j + 1;
		}
	}

	// Resultant snail sorted array
	int* array = snail(&size, test_array, SIZE, SIZE);

	return 0;
}
