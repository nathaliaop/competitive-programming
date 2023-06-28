// Description
// THe values are divided in two multisets so that one of them contain all values that are
// smaller than the median and the other one contains all values that are greater or equal to the median.

// Problem:
// https://atcoder.jp/contests/abc306/tasks/abc306_e
// Problem I - Maratona Feminina de Programação da Unicamp 2023
// https://codeforces.com/group/WYIydkiPyE/contest/450037/attachments

// Complexity:
// Add and remove elements - O(log n)
// Return sum of biggest or smallest set or return the median - O(1)

using ll = long long;

struct TwoSets {
  multiset<int> small;
  multiset<int> big;
  ll sums = 0;
  ll sumb = 0;
  int n = 0;

  int size_small() {
    return small.size();
  }

  int size_big() {
    return big.size();
  }

  void balance() {
    while (size_small() > n / 2) {
      int v = *small.rbegin();
      small.erase(prev(small.end()));
      big.insert(v);
      sums -= v;
      sumb += v;
    }
    while (size_big() > n - n / 2) {
      int v = *big.begin();
      big.erase(big.begin());
      small.insert(v);
      sumb -= v;
      sums += v;
    }
  }

  void add(int x) {
    n++;
    small.insert(x);
    sums += x;
    while (!small.empty() && *small.rbegin() > *big.begin()) {
      int v = *small.rbegin();
      small.erase(prev(small.end()));
      big.insert(v);
      sums -= v;
      sumb += v;
    }
    balance();
  }

  bool rem(int x) {
    n--;
    auto it1 = small.find(x);
    auto it2 = big.find(x);
    bool flag = false;
    if (it1 != small.end()) {
      sums -= *it1;
      small.erase(it1);
      flag = true;
    } else if (it2 != big.end()) {
      sumb -= *it2;
      big.erase(it2);
      flag = true;
    }
    balance();
    return flag;
  }

  ll sum_small() {
    return sums;
  }

  ll sum_big() {
    return sumb;
  }
  
  int median() {
    return *big.begin();
  }
};
