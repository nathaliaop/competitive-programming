// Description:
// Calculates a binomial n chooses k based on the value of a previous binomial.

// Complexity:
// O(n * k)

vector<vector<int>> comb(MAX + 1, vector<int>(MAX + 1, 0));

for (int n = 0; n <= MAX; n++) {
  comb[n][0] = 1;
}

for (int n = 1; n <= MAX; n++) {
  for (int k = 1; k <= n; k++) {
    comb[n][k] = comb[n - 1][k - 1] + comb[n - 1][k];
  }
}
