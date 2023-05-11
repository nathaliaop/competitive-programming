// achar uma subsequencia continua no array que a soma seja a maior possivel
// nesse caso vc precisa multiplicar exatamente 1 elemento da subsequencia
// e achar a maior soma com isso

int n, x, arr[MAX], tab[MAX][2]; // tab[maior resposta no intervalo][foi multiplicado ou não]
 
int dp(int i, bool mult) {
    if (i == n-1) {
        if (!mult) return arr[n-1]*x;
        return arr[n-1];
    }
    if (tab[i][mult] != -1) return tab[i][mult];
    
    int res;
    
    if (mult) {
        res = max(arr[i], arr[i] + dp(i+1, 1));
    } 
    else {
        res = max({
            arr[i]*x,
            arr[i]*x + dp(i+1, 1),
            arr[i] + dp(i+1, 0)
        });
    }
    
    return tab[i][mult] = res;
}
 
int main() {
    
    memset(tab, -1, sizeof(tab));
    
    int ans = -oo;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dp(i, 0));
    }    
    
    return 0;
}



int ans = a[0], ans_l = 0, ans_r = 0;
int sum = 0, minus_pos = -1;

for (int r = 0; r < n; ++r) {
    sum += a[r];
    if (sum > ans) {
        ans = sum;
        ans_l = minus_pos + 1;
        ans_r = r;
    }
    if (sum < 0) {
        sum = 0;
        minus_pos = r;
    }
}
