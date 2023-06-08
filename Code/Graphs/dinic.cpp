// Description: 
// Obtains the maximum possible flow rate given a network. A network is a graph with a single source vertex and a single sink vertex in which each edge has a capacity

// Problem:
// https://codeforces.com/gym/103708/problem/J

// Complexity:
// O(V^2 * E) where V is the number of vertex and E is the number of edges

// Unit network
// A unit network is a network in which for any vertex except source and sink either incoming or outgoing edge is unique and has unit capacity (matching problem).
// Complexity on unit networks: O(E * sqrt(V))

// Unity capacity networks
// A more generic settings when all edges have unit capacities, but the number of incoming and outgoing edges is unbounded
// Complexity on unity capacity networks: O(E * sqrt(E))

// How to use:
// Dinic dinic = Dinic(num_vertex, source, sink);
// dinic.add_edge(vertex1, vertex2, capacity);
// cout << dinic.max_flow() << '\n';

#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define ff first
#define ss second
#define ll long long

using namespace std;

const ll INF = 1e18+10;

struct Edge {
    int from;
    int to;
    ll capacity;
    ll flow;
    Edge* residual;
    
    Edge() {}
    
    Edge(int from, int to, ll capacity) : from(from), to(to), capacity(capacity) {
        flow = 0;
    }
    
    ll get_capacity() {
        return capacity - flow;
    }
    
    void augment(ll bottleneck) {
        flow += bottleneck;
        residual->flow -= bottleneck;
    }
    
    bool operator<(const Edge& e) const {
        return true;
    }
};

struct Dinic {
    int source;
    int sink;
    int nodes;
    ll flow;
    vector<vector<Edge*>> adj;
    vector<int> level;
    vector<int> next;
    
    Dinic(int source, int sink, int nodes) : source(source), sink(sink), nodes(nodes) {
        adj.resize(nodes + 1);
    } 
    
    void add_edge(int from, int to, ll capacity) {
        Edge* e1 = new Edge(from, to, capacity);
        Edge* e2 = new Edge(to, from, 0);
        e1->residual = e2;
        e2->residual = e1;
        adj[from].pb(e1);
        adj[to].pb(e2);
    }
    
    bool bfs() {
        level.assign(nodes + 1, -1);
        queue<int> q;
        q.push(source);
        level[source] = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (auto e : adj[node]) {
                if (level[e->to] == -1 && e->get_capacity() > 0) {
                    level[e->to] = level[e->from] + 1;
                    q.push(e->to);
                }
            }
        }
        
        return level[sink] != -1;
    }
    
    ll dfs(int v, ll flow) {
        if (v == sink)
            return flow;

        int sz = adj[v].size();
        for (int i = next[v]; i < sz; i++) {
            Edge* e = adj[v][i];
            if (level[e->to] == level[e->from] + 1 && e->get_capacity() > 0) {
                ll bottleneck = dfs(e->to, min(flow, e->get_capacity()));
                if (bottleneck > 0) {
                    e->augment(bottleneck);
                    return bottleneck;
                }
            }
            
            next[v] = i + 1;
        }
        
        return 0;
    }
    
    ll max_flow() {
        flow = 0;
        while(bfs()) {
            next.assign(nodes + 1, 0);
            ll sent = -1;
            while (sent != 0) {
                sent = dfs(source, INF);
                flow += sent;
            }
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    
    Dinic dinic = Dinic(1, n, n);
    
    for (int i = 1; i <= m; i++) {
        int v, u, c; cin >> v >> u >> c;
        dinic.add_edge(v, u, c);
        // dinic.add_edge(u, v, c);
    }
    
    cout << dinic.max_flow() << '\n';
    
    return 0;
}
