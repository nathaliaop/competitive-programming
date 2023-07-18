const string digits { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

string representation(int n, int b) {
  string rep;

  do {
    rep.push_back(digits[n % b]);
    n /= b;
  } while (n);

  reverse(rep.begin(), rep.end());

  return rep;
}
