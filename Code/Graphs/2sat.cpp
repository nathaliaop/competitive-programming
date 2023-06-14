// Description:
// Solves expression of the type (a v b) ^ (c v d) ^ (e v f) 

// Problem:
// https://cses.fi/problemset/task/1684

// Complexity:
// O(n + m) where n is the number of variables and m is the number of clauses

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define ff first
#define ss second

using namespace std;

struct SAT {
    int nodes;
    int curr = 0;
    int component = 0;
    vector<vector<int>> adj;
    vector<vector<int>> rev;
    vector<vector<int>> condensed;
    vector<pii> departure;
    vector<bool> visited;
    vector<int> scc;
    vector<int> order;
    
    // 1 to nodes
    // nodes + 1 to 2 * nodes
    SAT(int nodes) : nodes(nodes) {
        adj.resize(2 * nodes + 1);
        rev.resize(2 * nodes + 1);
        visited.resize(2 * nodes + 1);
        scc.resize(2 * nodes + 1);
    }
    
    void add_imp(int a, int b) {
        adj[a].pb(b);
        rev[b].pb(a);
    }
    
    int get_not(int a) {
        if (a > nodes) return a - nodes;
        return a + nodes;
    }
    
    void add_or(int a, int b) {
        add_imp(get_not(a), b);
        add_imp(get_not(b), a);
    }
    
    void add_nor(int a, int b) {
        add_or(get_not(a), get_not(b));
    }
    
    void add_and(int a, int b) {
        add_or(get_not(a), b);
        add_or(a, get_not(b));
        add_or(a, b);
    }
    
    void add_nand(int a, int b) {
        add_or(get_not(a), b);
        add_or(a, get_not(b));
        add_or(get_not(a), get_not(b));
    }
    
    void add_xor(int a, int b) {
        add_or(a, b);
        add_or(get_not(a), get_not(b));
    }

    void add_xnor(int a, int b) {
        add_or(get_not(a), b);
        add_or(a, get_not(b));
    }
    
    void departure_time(int v) {
        visited[v] = true;
        
        for (auto u : adj[v]) {
            if (!visited[u]) departure_time(u);
        }
    
        departure.pb(mp(++curr, v));
    }
    
    void find_component(int v, int component) {
        scc[v] = component;
        visited[v] = true;
        
        for (auto u : rev[v]) {
            if (!visited[u]) find_component(u, component);
        }
    }
    
    void topological_order(int v) {
        visited[v] = true;
        
        for (auto u : condensed[v]) {
            if (!visited[u]) topological_order(u);
        }
        
        order.pb(v);
    }
    
    bool is_possible() {
        component = 0;
        for (int i = 1; i <= 2 * nodes; i++) {
            if (!visited[i]) departure_time(i);
        }
        
        sort(departure.begin(), departure.end(), greater<pii>());
        
        visited.assign(2 * nodes + 1, false);
        
        for (auto [_, node] : departure) {
            if (!visited[node]) find_component(node, ++component);
        }
        
        for (int i = 1; i <= nodes; i++) {
            if (scc[i] == scc[i + nodes]) return false;
        }
        
        return true;
    }
    
    int find_value(int e, vector<int> &ans) {
        if (e > nodes && ans[e - nodes] != 2) return !ans[e - nodes];
        if (e <= nodes && ans[e + nodes] != 2) return !ans[e + nodes];
        return 0;
    }
    
    vector<int> find_ans() {
        condensed.resize(component + 1);
    
        for (int i = 1; i <= 2 * nodes; i++) {
            for (auto u : adj[i]) {
                if (scc[i] != scc[u]) condensed[scc[i]].pb(scc[u]);
            }
        }
        
        visited.assign(component + 1, false);
        
        for (int i = 1; i <= component; i++) {
            if (!visited[i]) topological_order(i);
        }
        
        reverse(order.begin(), order.end());
        
        // 0 - false
        // 1 - true
        // 2 - no value yet
        vector<int> ans(2 * nodes + 1, 2);
        
        vector<vector<int>> belong(component + 1);
        
        for (int i = 1; i <= 2 * nodes; i++) {
            belong[scc[i]].pb(i);
        }
        
        for (auto p : order) {
            for (auto e : belong[p]) {
                ans[e] = find_value(e, ans);
            }
        }
    
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    
    SAT sat = SAT(m);
    
    for (int i = 0; i < n; i++) {
        char op1, op2; int a, b; cin >> op1 >> a >> op2 >> b;
        if (op1 == '+' && op2 == '+') sat.add_or(a, b);
        if (op1 == '-' && op2 == '-') sat.add_or(sat.get_not(a), sat.get_not(b));
        if (op1 == '+' && op2 == '-') sat.add_or(a, sat.get_not(b));
        if (op1 == '-' && op2 == '+') sat.add_or(sat.get_not(a), b);
    }
    
    if (!sat.is_possible()) cout << "IMPOSSIBLE\n";
    else {
        vector<int> ans = sat.find_ans();
        for (int i = 1; i <= m; i++) {
            cout << (ans[i] == 1 ? '+' : '-') << ' ';
        }
        cout << '\n';
    }

    return 0;
}
