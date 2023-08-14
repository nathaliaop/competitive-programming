// Description:
// Make queries and updates between two vertexes on a tree

// Problem:
// https://www.spoj.com/problems/QTREE/

// Complexity:
// O(log ^2 n) for both query and update

// How to use:
// HLD hld = HLD(n + 1, adj)

// Notes
// Change the root of the tree on the constructor if it's different from 1
// Use together with Segtree

struct HLD {
  vector<int> parent;
  vector<int> pos;
  vector<int> head;
  vector<int> subtree_size;
  vector<int> level;
  vector<int> heavy_child;
  vector<ftype> subtree_weight;
  vector<ftype> path_weight;
  vector<vector<int>> adj;
  vector<int> at;
  Segtree seg = Segtree(0);
  int cpos;
  int n;
  int root;

  HLD() {}
 
  HLD(int n, vector<vector<int>>& adj, int root = 1) : adj(adj), n(n), root(root) {
    seg = Segtree(n);
    cpos = 0;
    at.assign(n, 0);
    parent.assign(n, 0); 
    pos.assign(n, 0); 
    head.assign(n, 0); 
    subtree_size.assign(n, 1);
    level.assign(n, 0);
    heavy_child.assign(n, -1);
    parent[root] = -1;
    dfs(root, -1);
    decompose(root, -1);
  }

  void dfs(int v, int p) {
    parent[v] = p;
    if (p != -1) level[v] = level[p] + 1;
    for (auto u : adj[v]) {
      if (u != p) {
        dfs(u, v);
        subtree_size[v] += subtree_size[u];
        if (heavy_child[v] == -1 || subtree_size[u] > subtree_size[heavy_child[v]]) heavy_child[v] = u;
      }
    }
  }

  void decompose(int v, int chead) {
    // start a new path
    if (chead == -1) chead = v;
 
    // consecutive ids in the hld path
    at[cpos] = v;
    pos[v] = cpos++;
    head[v] = chead;
 
    // if not a leaf
    if (heavy_child[v] != -1) decompose(heavy_child[v], chead);
 
    // light child
    for (auto u : adj[v]){
      // start new path
      if (u != parent[v] && u != heavy_child[v]) decompose(u, -1); 
    }
  }

  ll query_path(int a, int b) {
    if (a == b) return 0;
    if(pos[a] < pos[b]) swap(a, b);

    if(head[a] == head[b]) return seg.query(pos[b] + 1, pos[a]);
    return seg.f(seg.query(pos[head[a]], pos[a]), query_path(parent[head[a]], b));
  }

  ftype query_subtree(int a) {
    if (subtree_size[a] == 1) return 0;
    return seg.query(pos[a] + 1, pos[a] + subtree_size[a] - 1);
  }

  void update_path(int a, int b, int x) {
    if (a == b) return;
    if(pos[a] < pos[b]) swap(a, b);

    if(head[a] == head[b]) return (void)seg.update(pos[b] + 1, pos[a], x);
    seg.update(pos[head[a]], pos[a], x); update_path(parent[head[a]], b, x);
  }

  void update_subtree(int a, int val) {
    if (subtree_size[a] == 1) return;
    seg.update(pos[a] + 1, pos[a] + subtree_size[a] - 1, val);
  }

  // vertex
  void update(int a, int val) {
    seg.update(pos[a], pos[a], val);
  }

  //edge
  void update(int a, int b, int val) {
    if (parent[a] == b) swap(a, b);
    update(b, val);
  }

  int lca(int a, int b) {
    if(pos[a] < pos[b]) swap(a, b);
    return head[a] == head[b] ? b : lca(parent[head[a]], b);
  }
};
