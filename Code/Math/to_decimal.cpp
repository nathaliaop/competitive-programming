long long to_decimal(const string& rep, long long base) {
  long long n = 0;

  for (auto c : rep) {
    // if the number can't be represented in this base
    if (c > digits[base - 1]) return -1;
    n *= base;
    n += digits.find(c);
  }

  return n;
}
