// Description:
// In each node, the tree keeps a sorted list of elements in that range.
// It can be used to find how many elements are greater than x in a given range.
// It can also be used to find the position of an element if the list was sorted.
// query(i, j, k) - how many elements greater than k are in the range (i, j)
// update(i, val) - changes the value of the element on index i to val 

// Problem:
// https://www.beecrowd.com.br/judge/pt/problems/view/3097

// Complexity:
// O(n log ^ 2 ^ 2 n) for build
// O(log ^ 2 n) for query

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

struct MergeSortTree {
  vector<ordered_set<int>> tree;
  vector<int> v;
  int n;

  MergeSortTree(int n, vector<int>& v) : n(n), v(v) {
    int sz = 1;
    while (sz < n) sz *= 2;

    tree.resize(2 * sz);

    build(0, 0, n - 1, v);
  }
  
  void Erase(ordered_set<int>& a, int x){
    int r = a.order_of_key(x);
    auto it = a.find_by_order(r);
    a.erase(it);
  }
  
  ordered_set<int> merge(ordered_set<int>& a, ordered_set<int>& b) {
    ordered_set<int> res;
    
    for (auto e : a) res.insert(e);
    for (auto e : b) res.insert(e);

    return res;
  }

  void build(int pos, int ini, int fim, vector<int>& v) {
    if (ini == fim) {
      if (ini < (int)v.size()) {
        tree[pos].insert(v[ini]);
      }
      return;
    }

    int mid = ini + (fim - ini) / 2;

    build(2 * pos + 1, ini, mid, v);
    build(2 * pos + 2, mid + 1, fim, v);

    tree[pos] = merge(tree[2 * pos + 1], tree[2 * pos + 2]);
  }

  // how many elements greater than val in vector v
  int search(ordered_set<int>& v, int val) {
    return (int)v.size() - v.order_of_key(val + 1);
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

  void update(int pos, int ini, int fim, int id, int val) {
    if (ini == id && fim == id) {
      if (!tree[pos].empty()) Erase(tree[pos], v[id]);
      tree[pos].insert(val);
      return;
    }

    if (fim < id || ini > id) {
      return;
    }

    int mid = ini + (fim - ini) / 2;
    update(2 * pos + 1, ini, mid, id, val);
    update(2 * pos + 2, mid + 1, fim, id, val);

    if (!tree[pos].empty()) Erase(tree[pos], v[id]);
    tree[pos].insert(val);
  }

  int query(int p, int q, int val) {
    return query(0, 0, n - 1, p, q, val);
  }

  void update(int id, int val) {
    update(0, 0, n - 1, id, val);
    v[id] = val;
  }
};
