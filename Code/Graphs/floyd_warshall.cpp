#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;

const int MAX  = 507;
const long long INF = 0x3f3f3f3f3f3f3f3fLL;

ll dist[MAX][MAX];
int n;

void floyd_warshall() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else if (!dist[i][j]) dist[i][j] = INF;
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // trata o caso no qual o grafo tem arestas com peso negativo
                if (dist[i][k] < INF && dist[k][j] < INF){
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}