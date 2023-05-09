#include <stdlib.h>
#include <stdio.h>

// snail is a function that takes a two-dimensional array and returns
// an array containing the elements of the input array in a "snail"
// pattern, starting from the top left corner and spiraling inwards.
int* snail(size_t* outsz, int** mx, size_t rows, size_t cols) 
{
	// Declare variables for the current row and column in the snail traversal.
	size_t vertical, horizontal;

	// Allocate memory for the output array, which will have the same number
	// of elements as the input array.
	int* output = (int*) malloc((*outsz = rows*rows) * sizeof(int));
	if (output == NULL) {
		printf("Error allocating memory for output array\n");
		return NULL;
	}

	// Initialize the current row and column to the top left corner of the input array.
	vertical = horizontal = rows = 0;

	// Decrement the number of columns, since we will be using this variable as an
	// upper bound for the column index in the traversal loops below.
	cols--;

	// Perform the snail traversal. The traversal will continue until the current
	// row reaches the last column of the input array.
	while (rows < cols) {
		// Traverse the current row from left to right, adding each element to the output array.
		while (horizontal < cols) *output++ = mx[vertical][horizontal++];
		// Traverse the current column from top to bottom, adding each element to the output array.
		while (vertical < cols) *output++ = mx[vertical++][horizontal];
		// Traverse the current row from right to left, adding each element to the output array.
		while (horizontal > rows) *output++ = mx[vertical][horizontal--];
		// Traverse the current column from bottom to top, adding each element to the output array.
		while (vertical > rows) *output++ = mx[vertical--][horizontal];

		// Move to the next outer layer of the input array by incrementing the current row and column,
		// and decrementing the number of rows and columns.
		vertical++, horizontal++, rows++, cols--;
	}

	// If the number of rows and columns is the same, we have reached the middle of the input array.
	// In this case, add the element at the current row and column to the output array.
	if (rows == cols) *output++ = mx[vertical][horizontal];

	return output - *outsz;
}

// Adaptation for leetcode's version of this problem
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
    size_t rows = matrixSize;
    size_t cols = *matrixColSize;

    // Declare variables for the current row and column in the snail traversal.
    size_t vertical, horizontal;

    // Allocate memory for the output array, which will have the same number
    // of elements as the input array.
    int* output = (int*) malloc((*returnSize = rows*cols) * sizeof(int));
    if (output == NULL) {
        printf("Error allocating memory for output array\n");
        return NULL;
    }

    // Declare variables for the current row and column in the snail traversal.
    int row = 0, col = 0;
    // Traverse the matrix in a spiral pattern
    int idx = 0;
    // Start the transversal
    while (row < rows && col < cols) {
        // Traverse the top row from left to right
        for (int i = col; i < cols; i++) output[idx++] = matrix[row][i];
        row++;

        // Traverse the right column from top to bottom
        for (int i = row; i < rows; i++) output[idx++] = matrix[i][cols - 1];
        cols--;

        // Traverse the bottom row from right to left
        if (row < rows) {
            for (int i = cols - 1; i >= col; i--) output[idx++] = matrix[rows - 1][i];
            rows--;
        }

        // Traverse the left column from bottom to top
        if (col < cols) {
            for (int i = rows - 1; i >= row; i--) output[idx++] = matrix[i][col];
            col++;
        }
    }

    return output;
}

int main(int argc, char* argv[])
{
	size_t size;

	// Declare a variable for the number of rows and columns in the input array.
	int n = 4;

	int** test_array = (int**) malloc(sizeof(int*) * n);
	if (test_array == NULL) {
		printf("Error allocating memory for test_array\n");
		return -1;
	}

	for (int i = 0; i < n; ++i) {
		test_array[i] = (int*) malloc(sizeof(int) * n);
		if (test_array[i] == NULL) {
			printf("Error allocating memory for test_array[%d]\n", i);
			return -1;
		}
	}

	// Initialize the elements of the input array.
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			test_array[i][j] = (i*n) + j + 1;
		}
	}

	// Call the snail function to get the snail traversal of the input array.
	int* output = snail(&size, test_array, n, n);

	for (int i = 0; i < n*n; ++i) {
		printf("%d ", output[i]);
	}

	// Free the memory allocated for the output array.
	free(output);

	// Free the memory allocated for each row of the input array.
	for (int i = 0; i < n; i++) {
		free(test_array[i]);
	}

	// Free the memory allocated for the input array.
	free(test_array);

	return 0;
}
