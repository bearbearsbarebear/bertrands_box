/*
 * This is a leetcode problem. You can find it here:
 * https://leetcode.com/problems/longest-palindromic-substring/description/
 * The solution below is the solution I made for the problem.
 */

/*
 * Given a string s, return the longest palindromic substring in s.
 */

char* longestPalindrome(char* s)
{
	int string_size = strlen(s);
	int maxLen = 0, start = 0;
	char* result = NULL;

	// Check each character as a potential center of a palindrome
	for (int i = 0; i < string_size; ++i) {
		// Check odd-length palindromes with center at i
		int left = i, right = i;
		while (left >= 0 && right < string_size && s[left] == s[right]) {
			if (right - left + 1 > maxLen) {
				maxLen = right - left + 1;
				start = left;
			}

			--left;
			++right;
		}

		// Check even-length palindromes with center at i and i+1
		left = i, right = i + 1;
		while (left >= 0 && right < string_size && s[left] == s[right]) {
			if (right - left + 1 > maxLen) {
				maxLen = right - left + 1;
				start = left;
			}

			--left;
			++right;
		}
	}

	// Allocate memory for the result substring
	result = (char*) malloc(maxLen + 1);
	strncpy(result, s + start, maxLen);
	result[maxLen] = '\0';

	return result;
}