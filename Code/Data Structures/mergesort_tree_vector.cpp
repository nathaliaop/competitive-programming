// Description:
// In each node, the tree keeps a sorted list of elements in that range.
// It can be used to find how many elements are greater than x in a given range.
// It can also be used to find the position of an element if the list was sorted.
// query(i, j, k) - how many elements greater than k are in the range (i, j)

// Problem:
// https://www.spoj.com/problems/KQUERY

// Complexity:
// O(n log n) for build
// O(log ^ 2 n) for query

struct MergeSortTree {
  vector<vector<int>> tree;
  int n;

  MergeSortTree(int n, vector<int> v) : n(n), v(v) {
    int sz = 1;
    while (sz < n) sz *= 2;

    tree.assign(2 * sz, vector<int>());
    build(0, 0, n - 1, v)
  }

  vector<int> merge(vector<int>& a, vector<int>& b) {
    vector<int> res((int)a.size() + (int)b.size());
    int it = 0, jt = 0, curr = 0;

    while (it < (int)a.size() && jt < (int)b.size()) {
      if (a[it] <= b[jt]) {
        res[curr++] = a[it++];
      } else {
        res[curr++] = b[jt++];
      }
    }

    while (it < (int)a.size()) {
      res[curr++] = a[it++];
    }

    while (jt < (int)b.size()) {
      res[curr++] = b[jt++];
    }

    return res;
  }

  void build(int pos, int ini, int fim, vector<int>& v) {
    if (ini == fim) {
      if (ini < (int)v.size()) {
        tree[pos].pb(v[ini]);
      }
      return;
    }

    int mid = ini + (fim - ini) / 2;

    build(2 * pos + 1, ini, mid, v);
    build(2 * pos + 2, mid + 1, fim, v);

    tree[pos] = merge(tree[2 * pos + 1], tree[2 * pos + 2]);
  }

  // how many elements greater than val in vector v
  int search(vector<int>& v, int val) {
    auto it = upper_bound(v.begin(), v.end(), val);
    if (it == v.end()) return 0;
    return (int)v.size() - (it - v.begin());
  }

  // how many elements greater than val in the range (p, q)
  int query(int pos, int ini, int fim, int p, int q, int val) {
    if (fim < p || ini > q) {
      return 0;
    }

    if (ini >= p && fim <= q) {
      return search(tree[pos], val);
    }

    int mid = ini + (fim - ini) / 2;
    return query(2 * pos + 1, ini, mid, p, q, val) + query(2 * pos + 2, mid + 1, fim, p, q, val); 
  }

  int query(int p, int q, int val) {
    return query(0, 0, n - 1, p, q, val);
  }
};
