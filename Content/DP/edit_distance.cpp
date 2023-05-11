// Description:
// Minimum number of operations required to transform a string into another
// Operations allowed: add character, remove character, replace character

// Parameters:
// str1 - string to be transformed into str2
// str2 - string that str1 will be transformed into
// m - size of str1
// n - size of str2

// Problem:
// https://cses.fi/problemset/task/1639

// Complexity:
// O(m x n)

// How to use:
// memset(dp, -1, sizeof(dp));
// string a, b;
// edit_distance(a, b, (int)a.size(), (int)b.size());

// Notes:
// Size of dp matriz is m x n

int dp[MAX][MAX];

int edit_distance(string &str1, string &str2, int m, int n) {
    if (m == 0) return n;
    if (n == 0) return m;
    
    if (dp[m][n] != -1) return dp[m][n];

    if (str1[m - 1] == str2[n - 1]) return dp[m][n] = edit_distance(str1, str2, m - 1, n - 1);
    return dp[m][n] = 1 + min({edit_distance(str1, str2, m, n - 1), edit_distance(str1, str2, m - 1, n), edit_distance(str1, str2, m - 1, n - 1)});
}