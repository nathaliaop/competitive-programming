// Description:
// Finds the shortest path from a vertex v to any other vertex

// Problem:
// https://cses.fi/problemset/task/1673

// Complexity:
// O(n * m)

struct Edge {
  int a, b, cost;
  Edge(int a, int b, int cost) : a(a), b(b), cost(cost) {}
};

int n, m;
vector<Edge> edges;
const int INF = 1e9+10;

void bellman_ford(int v, int t) {
  vector<int> d(n + 1, INF);
  d[v] = 0;
  vector<int> p(n + 1, -1);

  for (;;) {
    bool any = false;
    for (Edge e : edges) {
      if (d[e.a] >= INF) continue;
      if (d[e.b] > d[e.a] + e.cost) {
        d[e.b] = d[e.a] + e.cost;
        p[e.b] = e.a;
        any = true;
      }
    }
    if (!any) break;
  }

  if (d[t] == INF)
    cout << "No path from " << v << " to " << t << ".";
  else {
    vector<int> path;
    for (int cur = t; cur != -1; cur = p[cur]) {
      path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    cout << "Path from " << v << " to " << t << ": ";
    for (int u : path) {
      cout << u << ' ';
    }
  }
}
