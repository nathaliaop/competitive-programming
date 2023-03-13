// Description:
// Indexed at zero
// Find a centroid, that is a node such that when it is appointed the root of the tree,
// each subtree has at most ⌊n/2⌋ nodes.

// Problem:
// https://cses.fi/problemset/task/2079/

// Complexity:
// O(n)

// How to use:
// get_subtree_size(0);
// cout << get_centroid(0) + 1 << endl;

int n;
vector<int> adj[MAX];
int subtree_size[MAX];

int get_subtree_size(int node, int par = -1) {
	int &res = subtree_size[node];
	res = 1;
	for (int i : adj[node]) {
		if (i == par) continue;
		res += get_subtree_size(i, node);
	}
	return res;
}

int get_centroid(int node, int par = -1) {
	for (int i : adj[node]) {
		if (i == par) continue;

		if (subtree_size[i] * 2 > n) { return get_centroid(i, node); }
	}
	return node;
}

int main() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	get_subtree_size(0);
	cout << get_centroid(0) + 1 << endl;
}
