ll fexp(ll b, ll e) {
    ll res = 1;
    b %= MOD;
    while(e){ 
        if(e & 1LL)
            res = (res * b) % MOD;
        e = e >> 1LL;
        b = (b * b) % MOD;
    }
    return res;
}
