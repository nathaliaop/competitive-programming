// Description
// Minimum queries in a 2D grid

// Problem:
// https://codeforces.com/group/YgJmumGtHD/contest/103794/problem/D

// Complexity:
// Build O(N * M * log(N) * log(M))
// Query O(1)
// Memory COmplexity: O(N * M * log(N) * log(M))

const int MAX = 410;

struct SparseTable2D {
  vector<vector<int>> matrix;
  vector<vector<vector<vector<int>>>> table;
  int n, m;

  SparseTable2D(vector<vector<int>>& matrix, int n, int m) : matrix(matrix), n(n), m(m) {
    table.resize(MAX, vector<vector<vector<int>>>(MAX, vector<vector<int>>(log2(MAX) + 1, vector<int>(log2(MAX) + 1))));
    build();
  }

  int f(int a, int b) {
    return max(a, b);
  }

  void build() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        table[i][j][0][0] = matrix[i][j];
      }
    }
 
    for (int k = 1; k <= (int)(log2(n)); k++) {
      for (int i = 0; i + (1 << k) - 1 < n; i++) {
        for (int j = 0; j + (1 << k) - 1 < m; j++) {
          table[i][j][k][0] = f(
          table[i][j][k - 1][0],
          table[i + (1 << (k - 1))][j][k - 1][0]);
        }
      }
    }
 
    for (int k = 1; k <= (int)(log2(m)); k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j + (1 << k) - 1 < m; j++) {
          table[i][j][0][k] = f(
          table[i][j][0][k - 1],
          table[i][j + (1 << (k - 1))][0][k - 1]);
        }
      }
    }
 
    for (int k = 1; k <= (int)(log2(n)); k++) {
      for (int l = 1; l <= (int)(log2(m)); l++) {
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
          for (int j = 0; j + (1 << l) - 1 < m; j++) {
            table[i][j][k][l] = f(
              f(
                table[i][j][k - 1][l - 1],
                table[i + (1 << (k - 1))][j][k - 1][l - 1]
              ),
              f(
                table[i][j + (1 << (l - 1))][k - 1][l - 1],
                table[i + (1 << (k - 1))][j + (1 << (l - 1))][k - 1][l - 1])
              );
          }
        }
      }
    }
  }
  
  int query(int x1, int y1, int x2, int y2) {
    int k = log2(x2 - x1 + 1);
    int l = log2(y2 - y1 + 1);
     
    return f(
      f(
        table[x1][y1][k][l],
        table[x2 - (1 << k) + 1][y1][k][l]
      ),
      f(
        table[x1][y2 - (1 << l) + 1][k][l],
        table[x2 - (1 << k) + 1][y2 - (1 << l) + 1][k][l]
      )
    );
  }
};
