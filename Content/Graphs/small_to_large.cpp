// Problem:
// https://codeforces.com/contest/600/problem/E

void process_colors(int curr, int parent) {
 
	for (int n : adj[curr]) {
		if (n != parent) {
			process_colors(n, curr);
			
            if (colors[curr].size() < colors[n].size()) {
                sum_num[curr] = sum_num[n];
                vmax[curr] = vmax[n];
				swap(colors[curr], colors[n]);
			}
 
			for (auto [item,vzs] : colors[n]) {
                if(colors[curr][item]+vzs > vmax[curr]){
                    vmax[curr] = colors[curr][item] + vzs;
                    sum_num[curr] = item;
                }
                else if(colors[curr][item]+vzs == vmax[curr]){
                    sum_num[curr] += item;
                }
 
                colors[curr][item] += vzs;
			}
		}
	}
 
}
 
 
int32_t main() {
 
	int n; cin >> n;
 
	for (int i = 1; i <= n; i++) {
		int a; cin >> a;
		colors[i][a] = 1;
        vmax[i] = 1;
        sum_num[i] = a;
	}
 
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
 
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
 
	process_colors(1, 0);
 
	for (int i = 1; i <= n; i++) {
		cout << sum_num[i] << (i < n ? " " : "\n");
	}
 
    return 0;
 
}
	