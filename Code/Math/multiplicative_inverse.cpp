ll extend_euclid(ll a, ll b, ll &x, ll &y) {
    if (a == 0)
    {
        x = 0; y = 1;
        return b;
    }
    ll x1, y1;
    ll d = extend_euclid(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

// gcd(a, m) = 1 para existir solucao
// ax + my = 1, ou a*x = 1 (mod m)
ll inv_gcd(ll a, ll m) { // com gcd
	ll x, y;
	extend_euclid(a, m, x, y);
	return (((x % m) +m) %m);
}

ll inv(ll a, ll phim) { // com phi(m), se m for primo entao phi(m) = p-1
	ll e = phim-1;
	return fexp(a, e, MOD);
}