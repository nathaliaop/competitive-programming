// Description:
// Write in terms of a line y = ax + b

// Problem:
// https://atcoder.jp/contests/dp/tasks/dp_z/

int n, c;
vector<int> h;
int dp[MAX];

const ll is_query = -INF;
struct Line{
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const{
        if(rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if(!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct Cht : public multiset<Line>{ // maintain max m*x+b
    bool bad(iterator y){
        auto z = next(y);
        if(y == begin()){
            if(z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if(z == end()) return y->m == x->m && y->b <= x->b;
        return (ld)(x->b - y->b)*(z->m - y->m) >= (ld)(y->b - z->b)*(y->m - x->m);
    }
    void insert_line(ll m, ll b){ // min -> insert (-m,-b) -> -eval()
        m *= -1; b *= -1;
        auto y = insert({ m, b });
        y->succ = [=]{ return next(y) == end() ? 0 : &*next(y); };
        if(bad(y)){ erase(y); return; }
        while(next(y) != end() && bad(next(y))) erase(next(y));
        while(y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll eval(ll x){
        auto l = *lower_bound((Line) { x, is_query });
        return -(l.m * x + l.b);
    }
};

int cost(int a, int b) {
  return (h[b] - h[a]) * (h[b] - h[a]) + c;
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> c;
  h.resize(n);

  for (int i = 0; i < n; i++) {
    cin >> h[i];
    dp[i] = INF;
  }

  dp[0] = 0;
  Cht cht = Cht();
  cht.insert_line(-2 * h[0], h[0] * h[0] + dp[0]);

  for (int i = 1; i < n; i++) {
    dp[i] = h[i] * h[i] + c + cht.eval(h[i]);

    cht.insert_line(-2 * h[i], h[i] * h[i] + dp[i]);

    // for (int j = 0; j < idx; j++) {
    //   dp[idx] = min(dp[idx], dp[j] + cost(j, idx));
    // }
  }

  cout << dp[n - 1] << '\n';

  return 0;
}
