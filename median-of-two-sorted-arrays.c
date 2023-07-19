/*
 * This is a leetcode problem. You can find it here:
 * https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 * The solution below is the solution I made for the problem.
*/

/*
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, 
 * return the median of the two sorted arrays.
 * The overall run time complexity should be O(log (m+n)).
*/

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
	int result_size_oddness = (nums1Size+nums2Size) % 2; // 0 = even, 1 = odd
	int result_size = (nums1Size+nums2Size)/2 + 1;
	int* result_array = (int*) malloc(sizeof(int) * result_size);
	int* ptr = result_array;
	double median;

	if (nums1Size == 0) {
		result_array = nums2;
	} else if (nums2Size == 0) {
		result_array = nums1;
	} else {
		// Both arrays are already sorted, so we loop through them while merging in a third array
		for (int i = 0, j = 0, k = 0; i < nums1Size || j < nums2Size;) {
			if (k == result_size) break;

			if (i < nums1Size && (j >= nums2Size || nums1[i] < nums2[j])) {
				result_array[k++] = nums1[i++];
			} else {
				result_array[k++] = nums2[j++];
			}
		}
	}

	median = (result_size_oddness == 1) ? (result_array[result_size-1]) : ((double) (result_array[result_size-1] + result_array[result_size-2])/2);
	free(ptr);
	return median;
}