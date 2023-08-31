// Description:
// Suffix array is an array with the indixes of the starting letter of every
// suffix in an array sorted in lexicographical order.

// Problem:
// https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/problem/A

// Complexity:
// O(n log n) with radix sort
// O(n log ^ 2 n) with regular sort

// Notes:
// Relevant Problems
// Substring search: Queries to know whether a given substring is present in a string
// Binary search for the first suffix that is greater or equal 
// O(log n |p|) where |p| is the total size of the substrings queried
//
// Substring size: Queries to know how many times a given substring appears in a string
// Binary search both for first ans last that is greater or equal
//
// Number of different substrings:
// A given suffix gives sz new substrings being sz the size of the suffix
// We can subtract the lcp (longest common prefix) to remove substrings
// that were already counted.
//
// Longest common substring between two strings:
// We can calculate the suffix array and lcp array of the two strings 
// concantened with a character greater than $ and smaller than A (like '&')
// The answer will be the lcp between two consecutive suffixes that belong to different strings
// (index at suffix array <= size of the first array)

void radix_sort(vector<pair<pair<int, int>, int>>& a) {
  int n = a.size();
  vector<pair<pair<int, int>, int>> ans(n);

  vector<int> count(n);

  for (int i = 0; i < n; i++) {
    count[a[i].first.second]++;
  }

  vector<int> p(n);

  p[0] = 0;
  for (int i = 1; i < n; i++) {
    p[i] = p[i - 1] + count[i - 1];
  }

  for (int i = 0; i < n; i++) {
    ans[p[a[i].first.second]++] = a[i];
  }

  a = ans;

  count.assign(n, 0);

  for (int i = 0; i < n; i++) {
    count[a[i].first.first]++;
  }

  p.assign(n, 0);

  p[0] = 0;
  for (int i = 1; i < n; i++) {
    p[i] = p[i - 1] + count[i - 1];
  }

  for (int i = 0; i < n; i++) {
    ans[p[a[i].first.first]++] = a[i];
  }

  a = ans;
}

vector<int> p, c;

vector<int> suffix_array(string s) {
  int n = s.size();
  vector<pair<char, int>> a(n);
  p.assign(n, 0);
  c.assign(n, 0);

  for (int i = 0; i < n; i++) {
    a[i] = mp(s[i], i);
  }

  sort(a.begin(), a.end());

  for (int i = 0; i < n; i++) {
    p[i] = a[i].second;
  }

  c[p[0]] = 0;
  for (int i = 1; i < n; i++) {
    if (a[i].first == a[i - 1].first) c[p[i]] = c[p[i - 1]];
    else c[p[i]] = c[p[i - 1]] + 1;
  }

  int k = 0;
  while ((1 << k) < n) {
    vector<pair<pair<int, int>, int >> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = mp(mp(c[i], c[(i + (1 << k)) % n]), i);
    }

    radix_sort(a);

    for (int i = 0; i < n; i++) {
      p[i] = a[i].second;
    }

    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
      if (a[i].first == a[i - 1].first) c[p[i]] = c[p[i - 1]];
      else c[p[i]] = c[p[i - 1]] + 1;
    }

    k++;
  }

  /* for (int i = 0; i < n; i++) {
    for (int j = p[i]; j < n; j++) {
      cout << s[j];
    }
    cout << '\n';
  } */

  return p;
}

// the first suffix will alway be $ the (n - 1)th character in the string
vector<int> lcp_array(string s) {
  int n = s.size();
  vector<int> ans(n);
  // minimum lcp
  int k = 0;
  for (int i = 0; i < n - 1; i++) {
    // indice in the suffix array p of suffix starting in i
    int pi = c[i];
    // start index of the previous suffix in suffix array
    int j = p[pi - 1];
    while (s[i + k] == s[j + k]) k++;
    ans[pi] = k;
    k = max(k - 1, 0);
  }

  return ans;
}

