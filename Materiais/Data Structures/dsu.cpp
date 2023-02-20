#include <bits/stdc++.h>
 
using namespace std;
 
const int MAX = 1e6+17;
 
struct DSU {
    int n;
    vector<int> link, sizes;
 
    DSU(int n) {
        this->n = n;
        link.assign(n+1, 0);
        sizes.assign(n+1, 1);
 
        for (int i = 0; i <= n; i++)
            link[i] = i;
    }
 
    int find(int x) {
        while (x != link[x])
            x = link[x];
        
        return x;
    }
 
    bool same(int a, int b) {
        return find(a) == find(b);
    }
 
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        
        if (a == b) return;
        
        if (sizes[a] < sizes[b])
            swap(a, b);
            
        sizes[a] += sizes[b];
        link[b] = a;
    }
    
    int size(int x) {
        return sizes[x];
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int cities, roads; cin >> cities >> roads;
    vector<int> final_roads;
    int ans = 0;
    DSU dsu = DSU(cities);
    for (int i = 0, a, b; i < roads; i++) {
        cin >> a >> b;
        dsu.unite(a, b);
    }
    
    for (int i = 2; i <= cities; i++) {
        if (!dsu.same(1, i)) {
            ans++;
            final_roads.push_back(i);
            dsu.unite(1,i);
        }
    }
    
    cout << ans << '\n';
    for (auto e : final_roads) {
        cout << "1 " << e << '\n';
    }
    
}