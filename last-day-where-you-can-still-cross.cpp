/*
 * This is a leetcode problem. You can find it here:
 * https://leetcode.com/problems/last-day-where-you-can-still-cross/description/
 * The solution below is the solution I made for the problem.
 */

/*
 * There is a 1-based binary matrix where 0 represents land and 1 represents water. 
 * You are given integers row and col representing the number of rows and columns 
 * in the matrix, respectively.
 * 
 * Initially on day 0, the entire matrix is land. However, each day a new cell becomes 
 * flooded with water. You are given a 1-based 2D array cells, where cells[i] = [ri, ci] 
 * represents that on the ith day, the cell on the rith row and cith column (1-based coordinates) 
 * will be covered with water (i.e., changed to 1).
 * 
 * You want to find the last day that it is possible to walk from the top to the bottom 
 * by only walking on land cells. You can start from any cell in the top row and end at 
 * any cell in the bottom row. You can only travel in the four cardinal directions 
 * (left, right, up, and down).
 * 
 * Return the last day where it is possible to walk from the top to the bottom by only 
 * walking on land cells.
 */

class Solution {
public:
	int latestDayToCross(int row, int col, vector<vector<int>>& cells)
	{
		int n = row * col;
		vector<int> root(n), lft(n), rgt(n);

		// Initialize the leftmost and rightmost indices for each cell
		for (int i = 0; i < col; ++i) {
			for (int j = 0; j < row; ++j) {
				int index = i * row + j;
				lft[index] = i;
				rgt[index] = i;
				root[index] = index;
			}
		}

		// Define the findRoot function to find the root of a component
		function<int(int)> findRoot = [&](int x) {
			// Find the root of the component containing x (with path compression)
			if (x != root[x]) {
				root[x] = findRoot(root[x]);
			}
			return root[x];
		};

		// Define the unionFind function to merge components
		function<void(int, int)> unionFind = [&](int x, int y) {
			// Merge the components of x and y
			int a = findRoot(x);
			int b = findRoot(y);
			if (a != b) {
				root[a] = b;
				lft[b] = min(lft[b], lft[a]); // Update leftmost and rightmost indices of the new component.
				rgt[b] = max(rgt[b], rgt[a]);
			}
		};

		unordered_set<int> seen;
		vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

		for (int i = 0; i < cells.size(); ++i) {
			int cx = cells[i][0] - 1;
			int cy = cells[i][1] - 1;

			for (const auto& dir : dirs) {
				int dx = dir.first;
				int dy = dir.second;
				int x = cx + dx;
				int y = cy + dy;

				if (x >= 0 && x < row && y >= 0 && y < col && seen.count(y * row + x)) {
					unionFind(cy * row + cx, y * row + x);
					int newRoot = findRoot(y * row + x);
					if (lft[newRoot] == 0 && rgt[newRoot] == col - 1) {
						return i;
					}
				}
			}

			seen.insert(cy * row + cx);
		}

		return -1; // Not possible to cross
	}
};
