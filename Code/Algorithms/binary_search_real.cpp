int cnt = 100;
ld l = 1e-7, r = 1e6+10;
while (cnt--) {
    ld mid = (l + r) / 2;

    if (f(mid)) {
        l = mid;
    } else {
        r = mid;
    }
}
