const ld EPS1 = 1e-9; // iteration precision error
const ld EPS2 = 1e-4; // output precision error

ld f(ld x) {
  // exp(-x) == e^(-x)
  return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

ld root(ld a, ld b) {
  while (b - a >= EPS1) {
    ld c = (a + b) / 2.0;
    ld y = f(c);

    if (y < 0) b = c;
    else a = c;
  }

  return (a + b) / 2;
}

int main() {
  ld ans = root(0, 1);
  if (abs(f(ans)) <= EPS2) cout << fixed << setprecision(4) << ans << '\n';
  else  cout << "No solution\n";

  return 0;
}
