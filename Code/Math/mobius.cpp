vector<int> m(MAXN, 0), lp(MAXN, 0);
m[1] = 1;
for (int i = 2; i < MAXN; ++i) {
    if (!lp[i]) for (int j = i; j < MAXN; j += i)
        if (!lp[j]) lp[j] = i;
    m[i] = [&](int x) {
        int cnt = 0;
        while (x > 1) {
            int k = 0, d = lp[x];
            while (x % d == 0) {
                x /= d;
                ++k;
                if (k > 1) return 0;
            }
            ++cnt;
        }
        if (cnt & 1) return -1;
        return 1;
    }(i);
}
