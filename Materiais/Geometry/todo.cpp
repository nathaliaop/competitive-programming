// vector angle
// vector norm
// vector length
// cross and dot product

struct point {
double x, y;
  point(double _x, double _y) {
    x = _x, y = _y;
  }
  point operator+(const point &oth){
    return point(x + oth.x, y + oth.y);
  }
  point operator-(const point &oth){
    return point(x - oth.x, y - oth.y);
  }

  double distance(point oth = point(0,0)) const {
    return sqrt(pow(x - oth.x, 2.0) + pow(y - oth.y, 2.0));
  }
};

typedef long long C;
typedef complex P;
#define X real()
#define Y imag()
P v = {3,1};
P u = {2,2};
P length = abs(v);
P s = v+u;

cout << s.X << " " << s.Y << "\n"; // 5 3

#define P(p) const point &p
#define L(p0, p1) P(p0), P(p1)
double dot(P(a), P(b)) {
  return real(a) * real(b) + imag(a) * imag(b);
}
double angle(P(a), P(b), P(c)) {
  return acos(dot(b - a, c - b) / abs(b - a) / abs(c - b));
}
point closest_point(L(a, b), P(c), bool segment = false) {
  if (segment) {
  if (dot(b - a, c - b) > 0) return b;
  if (dot(a - b, c - a) > 0) return a;
  }
  double t = dot(c - a, b - a) / norm(b - a);
  return a + t * (b - a);
}

double cross(P(a), P(b)) {
  return real(a)*imag(b) - imag(a)*real(x);
}
// counter-clockwise
double ccw(P(a), P(b), P(c)) {
  return cross(b - a, c - b);
}
bool collinear(P(a), P(b), P(c)) {
  return abs(ccw(a, b, c)) < EPS;
}