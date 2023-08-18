// Description:
// Hierholzer's Algorithm
// An Eulerian path is a path that passes through every edge exactly once.
// An Eulerian circuit is an Eulerian path that starts and ends on the same node.

// An Eulerian path exists in an directed graph if the indegree and outdegree is equal
// for every node (not counting self-edges)
// except for possibly exactly one node that have outdegree - indegree = 1
// and one node that has indegree - outdegreee = 1 (start and end nodes).
// An Eulerian circuit exists in an directed graph if the indegree and outdegree is equal for every node.

// The graph has to be conected (except for isolated nodes which are allowed because there
// are no edges connected to them).

// Problem:
// https://cses.fi/problemset/task/1693

// Complexity:
// O(E) where E is the number of edges

// How to use
// Check whether the path exists before trying to find it
// Find the root - any node that has at least 1 outgoing edge
// (if the problem requires that you start from a node v, the root will be the node v)
// Count the degree;
//
// for (int i = 0; i < m; i++) {
//  int a, b; cin >> a >> b;
//  adj[a].pb(b);
//  root = a;
//  outdegree[a]++; indegree[b]++;
// }

// Notes
// It works when there are self loops, but not when there are multiple edges

vector<bool> visited;
vector<int> outdegree, indegree;
vector<vector<int>> adj, undir;

void dfs(int v) {
  visited[v] = true;
  for (auto u : undir[v]) {
    if (!visited[u]) dfs(u);
  }
}

int is_eulerian(int n, int root, int &start, int& end) {
  start = -1, end = -1;
  if (n == 1) return 2; // only one node
  visited.assign(n + 1, false);
  dfs(root);

  for (int i = 1; i <= n; i++) {
    if (!visited[i] && (i == n || i == 1 || outdegree[i] + indegree[i] > 0)) return 0;
  }

  // start => node with indegree - outdegree = 1
  // end => node with outdegree - indegree = 1
  for (int i = 1; i <= n; i++) {
    if (start == -1 && indegree[i] - outdegree[i] == 1) start = i;
    else if (end == -1 && outdegree[i] - indegree[i] == 1) end = i;
    else if (indegree[i] != outdegree[i]) return 0;
  }

  if (start == -1 && end == -1) {start = root; end = root; return 2;} // has eulerian circuit and path
  if (start != -1 && end != -1) {swap(start, end); return 1;} // has eulerian path
  return 0; // no eulerian path nor circuit
}

vector<int> path;

void dfs_path(int v) {
  visited[v] = true;

  while (outdegree[v] != 0) {
    int u = adj[v][--outdegree[v]];
    int next_edge = adj[v][outdegree[v]];
    dfs_path(next_edge);
  }
  path.pb(v);
}

void find_path(int n, int start) {
  path.clear();
  visited.assign(n + 1, false);
  dfs_path(start);
  reverse(path.begin(), path.end());
}
