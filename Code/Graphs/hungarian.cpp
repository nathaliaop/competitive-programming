// Description:
// A matching algorithm for weighted bipartite graphs that returns
// a perfect match

// Problem:
// https://codeforces.com/gym/103640/problem/H

// Complexity:
// O(V ^ 3) in which V is the number of vertexs

// Notes:
// Indexed at 1

// n is the number of items on the right side and m the number of items
// on the left side of the graph

// Returns minimum assignment cost and which items were matched

pair<int, vector<pii>> hungarian(int n, int m, vector<vector<int>> A) {
  vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
  for (int i=1; i<=n; ++i) {
    p[0] = i;
    int j0 = 0;
    vector<int> minv (m+1, INF);
    vector<char> used (m+1, false);
    do {
      used[j0] = true;
      int i0 = p[j0],  delta = INF,  j1;
      for (int j=1; j<=m; ++j)
        if (!used[j]) {
          int cur = A[i0][j]-u[i0]-v[j];
          if (cur < minv[j])
            minv[j] = cur,  way[j] = j0;
          if (minv[j] < delta)
            delta = minv[j],  j1 = j;
        }
      for (int j=0; j<=m; ++j)
        if (used[j])
          u[p[j]] += delta,  v[j] -= delta;
        else
          minv[j] -= delta;
      j0 = j1;
    } while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);
  }

  vector<pair<int, int>> result;
  for (int i = 1; i <= m; ++i){
    result.push_back(make_pair(p[i], i));
  }

  int C = -v[0];

  return mp(C, result);
}
