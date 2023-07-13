// Description:
// Evaluates y = f(x)

// Problem:
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=439

// Complexity:
// O(n)

using polynomial = std::vector<int>;

polynomial p {6, -5, 2}; // p(x) = x^2 - 5x + 6;

int degree(const polynomial& p) {
  return p.size() - 1;
}

int evaluate(const polynomial& p, int x) {
  int y = 0, N = degree(p);

  for (int i = N; i >= 0; --i) {
    y *= x;
    y += p[i];
  }

  return y;
}
