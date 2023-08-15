// Description:
// Make queries and updates between two vertexes on a tree
// Query path - query path (a, b) inclusive
// Update path - update path (a, b) inclusive
// Query subtree - query subtree of a
// Update subtree - update subtree of a
// Update - update vertex or edge
// Lca - get lowest common ancestor of a and b
// Search - perform a binary search to find the last node with a certain property
// on the path from a to the root 

// Problem:
// https://codeforces.com/gym/101908/problem/L

// Complexity:
// O(log ^2 n) for both query and update

// How to use:
// HLD hld = HLD(n + 1, adj)

// Notes
// Change the root of the tree on the constructor if it's different from 1
// Use together with Segtree

typedef long long ftype;

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
  vector<vector<int>> up;

  HLD() {}
 
  HLD(int n, vector<vector<int>>& adj, int root = 1) : adj(adj), n(n), root(root) {
    seg = Segtree(n);
    cpos = 0;
    at.resize(n);
    parent.resize(n); 
    pos.resize(n); 
    head.resize(n); 
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

  ftype query_path(int a, int b) {
    if(pos[a] < pos[b]) swap(a, b);

    if(head[a] == head[b]) return seg.query(pos[b], pos[a]);
    return seg.f(seg.query(pos[head[a]], pos[a]), query_path(parent[head[a]], b));
  }

  // iterative
  /*ftype query_path(int a, int b) {
    ftype ans = 0;
 
    while (head[a] != head[b]) {
      if (level[head[a]] > level[head[b]]) swap(a, b);
      ans = seg.merge(ans, seg.query(pos[head[b]], pos[b]));
      b = parent[head[b]];
    }
 
    if (level[a] > level[b]) swap(a, b);
    ans = seg.merge(ans, seg.query(pos[a], pos[b]));
    return ans;
  }*/

  ftype query_subtree(int a) {
    return seg.query(pos[a], pos[a] + subtree_size[a] - 1);
  }

  void update_path(int a, int b, int x) {
    if(pos[a] < pos[b]) swap(a, b);

    if(head[a] == head[b]) return (void)seg.update(pos[b], pos[a], x);
    seg.update(pos[head[a]], pos[a], x); update_path(parent[head[a]], b, x);
  }

  void update_subtree(int a, int val) {
    seg.update(pos[a], pos[a] + subtree_size[a] - 1, val);
  }
 
  void update(int a, int val) {
    seg.update(pos[a], pos[a], val);
  }

  //edge
  void update(int a, int b, int val) {
    if (level[a] > level[b]) swap(a, b);
    update(b, val);
  }

  int lca(int a, int b) {
    if(pos[a] < pos[b]) swap(a, b);
    return head[a] == head[b] ? b : lca(parent[head[a]], b);
  }

  void search(int a) {
    a = parent[a];
    if (a == -1) return;
    if (seg.query(pos[head[a]], pos[head[a]]+subtree_size[head[a]]-1) + pos[a]-pos[head[a]]+1 == subtree_size[head[a]]) {
      seg.update(pos[head[a]], pos[a], 1);
      return search(parent[head[a]]);
    }
    int l = pos[head[a]], r = pos[a]+1;
    while (l < r) {
      int m = (l+r)/2;
      if (seg.query(m, m+subtree_size[at[m]]-1) + pos[a]-m+1 == subtree_size[at[m]]) {
        r = m;
      }
      else l = m+1;
    }
    seg.update(l, pos[a], 1);
  }

  /* k-th ancestor of x
  int x, k; cin >> x >> k;

  for (int b = 0; b <= BITS; b++) {
    if (x != -1 && (k & (1 << b))) {
      x = up[x][b];
    }
  }

  cout << x << '\n';
  */
  void preprocess() {
    up.assign(n + 1, vector<int>(31, -1));  
 
    for (int i = 1; i < n; i++) {
      up[i][0] = parent[i];
    }
 
    for (int i = 1; i < n; i++) {
      for (int j = 1; j <= 30; j++) {
        if (up[i][j - 1] != -1) up[i][j] = up[up[i][j - 1]][j - 1];
      }
    }
  }

  int getKth(int p , int q , int k){
    int a = lca(p,q) , d ;

    if( a == p ){
        d = level[q] - level[p] + 1 ;
        swap(p,q);
        k = d - k + 1 ;
    }
    else if( a == q ) ;
    else {
        if( k > level[p] - level[a] + 1 ) {
            d = level[p] + level[q] - 2 * level[a] + 1 ;
            k = d - k + 1 ;
            swap(p,q);
        }
        else ;
    }
    int lg ; for( lg = 1 ; (1 << lg) <= level[p] ; ++lg ); lg--;
    k--;
    for( int i = lg ; i >= 0 ; i-- ){
        if( (1 << i) <= k ){
            p = up[p][i];
            k -= ( 1 << i );
        }
    }
    return p;
}
};
