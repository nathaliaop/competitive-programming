// Description:
// Find the lowest common ancestor between two nodes in a tree

// Problem:
// https://cses.fi/problemset/task/1135

// Complexity:
// O(log n)

// How to use:
// preprocess();
// lca(a, b);

// Notes
// To calculate the distance between two nodes use the following formula
// level_peso[a] + level_peso[b] - 2*level_peso[lca(a, b)]

const int MAX = 2e5+10;
const int BITS = 30;
 
vector<pii> adj[MAX];
vector<bool> visited(MAX);

int up[MAX][BITS + 1];
int level[MAX];
int level_peso[MAX];

void find_level() {
  queue<pii> q;
 
  q.push(mp(1, 0));
  visited[1] = true;
 
  while (!q.empty()) {
    auto [v, depth] = q.front();
    q.pop();
    level[v] = depth;
 
    for (auto [u,d] : adj[v]) {
      if (!visited[u]) {
        visited[u] = true;
        up[u][0] = v;
        q.push(mp(u, depth + 1));
      }
    }
  }
}

void find_level_peso() {
  queue<pii> q;
 
  q.push(mp(1, 0));
  visited[1] = true;
 
  while (!q.empty()) {
    auto [v, depth] = q.front();
    q.pop();
    level_peso[v] = depth;
 
    for (auto [u,d] : adj[v]) {
      if (!visited[u]) {
        visited[u] = true;
        up[u][0] = v;
        q.push(mp(u, depth + d));
      }
    }
  }
}
 
int lca(int a, int b) {
   // get the nodes to the same level
    int mn = min(level[a], level[b]);
 
    for (int j = 0; j <= BITS; j++) {
      if (a != -1 && ((level[a] - mn) & (1 << j))) a = up[a][j];
      if (b != -1 && ((level[b] - mn) & (1 << j))) b = up[b][j];
    }
 
    // special case
    if (a == b) return a;
 
    // binary search
    for (int j = BITS; j >= 0; j--) {
      if (up[a][j] != up[b][j]) {
        a = up[a][j];
        b = up[b][j];
      }
    }
    return up[a][0];
}

void preprocess() {
  visited = vector<bool>(MAX, false);
  find_level();
  visited = vector<bool>(MAX, false);
  find_level_peso();
 
  for (int j = 1; j <= BITS; j++) {
    for (int i = 1; i <= n; i++) {
      if (up[i][j - 1] != -1) up[i][j] = up[up[i][j - 1]][j - 1];
    }
  }
}
