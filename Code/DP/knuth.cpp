// Description
// Optimization of range dp

// Problem
// https://www.spoj.com/problems/BRKSTRNG/

// Recurrence
// dp(i, j) = min(dp(i, k) + d[(k + 1, j) + C(i, j)]) for (int k = i; k < j; k++)

int dp[MAX][MAX], opt[MAX][MAX];
vector<int> v;
int n, m;

int solve(int l, int r) {
  if (abs(l - r) <= 1) return 0;

  int& memo = dp[l][r];
  if (memo != -1) return memo;

  memo = INF;
  for (int i = l + 1; i < r; i++) {
    memo = min(memo, solve(l, i) + solve(i, r) + v[r] - v[l]);
  }

  return memo;
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> n >> m) {   
    v.resize(m + 2, 0);
    v[m + 1] = n;
    for (int i = 1; i <= m; i++) {
      cin >> v[i];
    }

    for (int i = 0; i <= m + 1; i++) {
      for (int j = 0; j <= m + 1; j++) {
        opt[i][i] = i;
        dp[i][i] = 0;
        dp[i][j] = INF;
        if (abs(i - j) <= 1) dp[i][j] = 0;
        if (abs(i - j) <= 1) opt[i][j] = i;
      }
    }

    // memset(dp, -1, sizeof(dp));
    // cout << solve(0, m + 1) << '\n';

    for (int l = m; l >= 0; l--) {
      for (int r = l + 1; r <= m + 1; r++) {
        if (abs(l - r) <= 1) continue;
        /* for (int i = l + 1; i < r; i++) {
          dp[l][r] = min(dp[l][r], dp[l][i] + dp[i][r] + v[r] - v[l]);
        } */

        ll ans = INF;
          for (int k=opt[l][r-1]; k<=min(r-1, opt[l+1][r]); k++) {
            ll best = dp[l][k] + dp[k][r];
            if (ans > best) {
                ans = best;
                opt[l][r] = k;
            }
          }
          dp[l][r] = ans + v[r] - v[l];
      }
    }

    cout << dp[0][m + 1] << '\n';
  }

  return 0;
}
