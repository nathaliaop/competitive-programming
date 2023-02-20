// Description:
// insert(k) - add element k to the ordered set
// erase(k) - remove element k from the ordered set
// erase(it) - remove element it points to from the ordered set
// order_of_key(k) - returns number of elements strictly smaller than k
// find_by_order(n) - return an iterator pointing to the k-th element in the ordered set (counting from zero).

// Problem:
// https://cses.fi/problemset/task/2169/

// Complexity:
// O(log n) for all operations

// How to use:
// ordered_set<int> os;
// cout << os.order_of_key(1) << '\n;
// cout << os.find_by_order(1) << '\n;

// Notes
// The ordered set only contains different elements
// By using less_equal<T> instead of less<T> on using ordered_set declaration
// The ordered_set becomes an ordered_multiset
// So the set can contain elements that are equal

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;