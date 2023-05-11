int last_true(int lo, int hi, function<bool(int)> f) {
	lo--;
	while (lo < hi) {
		int mid = lo + (hi - lo + 1) / 2;
		if (f(mid)) {
			lo = mid;
		} else {
			hi = mid - 1;
		}
	}
	return lo;
}