// Description:
// Divide the array in k intervals

// Problem:
// https://cses.fi/problemset/task/2086/

// Recurrence
// dp(i, j) = min(dp(i - 1, k - 1), C(k, j))

int dp[MAX][MAX];
 
vector<int> v, psum;
int k, n;
 
int C(int start, int end) {
  if (start == 0) return psum[end] * psum[end]; 
 
  return (psum[end] - psum[start - 1]) * (psum[end] - psum[start - 1]);
}
 
void solve(int sz, int l, int r, int optl, int optr) {
  if (l > r) return;
 
  int mid = l + (r - l) / 2;
 
  pii best = {INF, l};
 
  for (int j = optl; j < min(mid, optr + 1); j++) {
    best = min(best, make_pair(C(j + 1, mid) + dp[sz - 1][j], j));
  }
 
  dp[sz][mid] = best.first;
 
  int opt = best.second;
  solve(sz, l, mid - 1, optl, opt);
  solve(sz, mid + 1, r, opt, optr);
}
 
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
 
  cin >> n >> k;
  v.resize(n);
  psum.assign(n, 0);
  
  for (int idx = 0; idx < n; idx++) {
    for (int sz = 0; sz <= n; sz++) {
       dp[sz][idx] = INF;
    }
  }
 
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    psum[i] = v[i];
    if (i != 0) psum[i] += psum[i - 1];
  }
 
  for (int i = 0; i < n; i++) {
    dp[1][i] = C(0, i);
  }
 
  for (int sz = 2; sz <= n; sz++) {
    solve(sz, 1, n, 0, n - 1);
    
    /* for (int idx = 0; idx < n; idx++) {
      for (int i = 0; i < idx; i++) {
        dp[sz][idx] = min(dp[sz][idx], dp[sz - 1][i] + C(i + 1, idx));
      }
    } */
  
  }
 
  cout << dp[k][n - 1] << '\n';
 
  return 0;
}
