// msb de 0 é undefined
#define msb(n) (32 - __builtin_clz(n))
// #define msb(n) (64 - __builtin_clzll(n) )
// popcount
#define popcount(x) __builtin_popcountll((unsigned ll)x)
// turn bit off

bool bit_on(int n, int bit) {
    if(1 & (n >> bit)) return true;
    else return false;
}
