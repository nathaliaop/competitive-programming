// Description:
// Queries the sum of a rectangle that goes from grid[from_row][from_col] to grid[to_row][to_col]

// Problem:
// https://cses.fi/problemset/task/1652/

// Complexity:
// O(n) build
// O(1) query

for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= n; j++) {
		psum[i][j] = grid[i][j] + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
	}
}
 
while (q--) {
	int from_row, to_row, from_col, to_col;
	cin >> from_row >> from_col >> to_row >> to_col;
	cout << psum[to_row][to_col] - psum[from_row - 1][to_col] -
	psum[to_row][from_col - 1] + psum[from_row - 1][from_col - 1] << '\n';
}
