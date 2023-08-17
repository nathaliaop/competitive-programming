// Description
// Detects any cycle in which the sum of edge weights is negative.
// Alternatively, we can detect whether there is a negative cycle
// starting from a specific vertex.

// Problem:
// https://cses.fi/problemset/task/1197

// Complexity:
// O(n * m)

// Notes
// In order to consider only the negative cycles located on the path from a to b,
// Reverse the graph, run a dfs from node b and mark the visited nodes
// Consider only the edges that connect to visited nodes when running bellman-ford 
// on the normal graph

struct Edge {
  int a, b, cost;
  Edge(int a, int b, int cost) : a(a), b(b), cost(cost) {}
};

int n, m;
vector<Edge> edges;
const int INF = 1e9+10;

void negative_cycle() {
  // uncomment to find negative cycle starting from a vertex v
  // vector<int> d(n + 1, INF);
  // d[v] = 0;
  vector<int> d(n + 1, 0);
  vector<int> p(n + 1, -1);
  int x;
  // uncomment to find all negative cycles
  // // set<int> s;
  for (int i = 1; i <= n; ++i) {
    x = -1;
    for (Edge e : edges) {
      // if (d[e.a] >= INF) continue;
      if (d[e.b] > d[e.a] + e.cost) {
        // d[e.b] = max(-INF, d[e.a] + e.cost);
        d[e.b] = d[e.a] + e.cost;
        p[e.b] = e.a;
        x = e.b;
        // // s.insert(e.b);
      }
    }
  }

  if (x == -1)
    cout << "NO\n";
  else {
    // // int y = all nodes in set s
    int y = x;
    for (int i = 1; i <= n; ++i) {
      y = p[y];
    }

    vector<int> path;
    for (int cur = y;; cur = p[cur]) {
      path.push_back(cur);
      if (cur == y && path.size() > 1) break;
    }
    reverse(path.begin(), path.end());

    cout << "YES\n";
    for (int u : path)
        cout << u << ' ';
    cout << '\n';
  }
}
