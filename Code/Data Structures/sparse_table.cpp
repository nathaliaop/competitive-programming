// Description:
// Data structure to query for minimum and maximum

// Problem:
// https://cses.fi/problemset/task/1647/

// Complexity:
// Build O(n log n)
// Query O(1)

#include <bits/stdc++.h>
 
using namespace std;

const int MAX = 2e5+17;
const int INF = 1e9+17;

struct SparseTable {
  int n;
  vector<int> arr;
  vector<vector<int>> st;
  vector<int> log_2;

  SparseTable(vector<int>& arr, int& n) : arr(arr), n(n) {
    build();
  }
  
  void build() {
    log_2.resize(MAX + 1);

    log_2[1] = 0;
    for (int i = 2; i <= MAX; i++) {
      log_2[i] = log_2[i/2] + 1;
    }
    
    int K = log_2[n + 1];

    st.resize(MAX, vector<int>(K + 1));
    
    for (int i = 0; i < MAX; i++) {
      for (int j = 0; j < K + 1; j++) {
        st[i][j] = INF;
      }
    }
    
    for (int i = 0; i < n; i++) {
      st[i][0] = arr[i];
    }
    
    for (int j = 1; j <= K; j++) {
      for (int i = 0; i + (1 << j) < MAX; i++) {
        st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  int query(int l, int r) {
    int j = log_2[r - l + 1];
    return min(st[l][j], st[r - (1 << j) + 1][j]);
  }
};
