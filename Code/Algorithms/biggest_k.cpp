// Description: Gets sum of k biggest or k smallest elements in an array

// Problem: https://atcoder.jp/contests/abc306/tasks/abc306_e

// Complexity: O(log n)

struct SetSum {
    ll s = 0;
    multiset<ll> mt;
    void add(ll x){
        mt.insert(x);
        s += x;
    }
    int pop(ll x){
        auto f = mt.find(x);
        if(f == mt.end()) return 0;
        mt.erase(f);
        s -= x;
        return 1;
    }
};

struct BigK {
    int k;
    SetSum gt, mt;
    BigK(int _k){
        k = _k;
    }
    void balancear(){
        while((int)gt.mt.size() < k && (int)mt.mt.size()){
            auto p = (prev(mt.mt.end()));
            gt.add(*p);
            mt.pop(*p);
        }
        while((int)mt.mt.size() && (int)gt.mt.size() && 
        *(gt.mt.begin()) < *(prev(mt.mt.end())) ){
            ll u = *(gt.mt.begin());
            ll v = *(prev(mt.mt.end()));
            gt.pop(u); mt.pop(v);
            gt.add(v); mt.add(u);
        }
    }
    void add(ll x){
        mt.add(x);
        balancear();
    }
    void rem(ll x){
        //x = -x;
        if(mt.pop(x) == 0)
            gt.pop(x);
        balancear();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, q; cin >> n >> k >> q;
    
    BigK big = BigK(k);
    
    int arr[n] = {};
    
    while (q--) {
        int pos, num; cin >> pos >> num;
        pos--;
        big.rem(arr[pos]);
        arr[pos] = num;
        big.add(arr[pos]);
        
        cout << big.gt.s << '\n';
    }

    return 0;
}