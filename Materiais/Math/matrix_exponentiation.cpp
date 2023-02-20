#include <bits/stdc++.h>
#define debug(x) cout << "[" << #x << " = " << x << "] "
#define ff first
#define ss second

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

using tii = tuple<int,int,int>;

const int oo = (int)1e9;
const ll OO = 0x3f3f3f3f3f3f3f3fLL;

const int MOD = 1e9+7;
 
struct Mat{
    vector<vector<ll>> matriz;
    int l, c;
 
    Mat(vector<vector<ll>>& mat){
        matriz = mat;
        l = mat.size();
        c = mat[0].size();
    }
    
    Mat(int r, int col, bool identidade=false){ 
        l = r;  c = col;
        matriz.assign(l, vector<ll>(col, 0));
        if(identidade){
            for(int i = 0; i < min(l,col); i++)
                matriz[i][i] = 1;
        }
    }
 
    Mat operator * (const Mat& a) const{
        assert(c == a.l);
        vector<vector<ll>> resp(l, vector<ll>(a.c, 0));

        for(int i = 0; i < l; i++){
            for(int j = 0; j < a.c; j++){
                for(int k = 0; k < a.l; k++){
                    resp[i][j] = (resp[i][j] + (matriz[i][k]*a.matriz[k][j]) % MOD) % MOD;
                }
            }
        }
        return Mat(resp);
    }
 
    Mat operator + (const Mat& a) const{
        assert(l == a.l && c == a.c); 
        vector<vector<ll>> resp(l, vector<ll>(c,0));
        for(int i = 0; i < l; i++){
            for(int j = 0; j < c; j++){
                resp[i][j] = (resp[i][j] + matriz[i][j] + a.matriz[i][j]) % MOD;
            }
        }
        return Mat(resp);
    }
};
 
Mat fexp(Mat& base, ll expoente, ll sz){
    Mat result = Mat(sz, sz, 1);
    while(expoente > 0){
        if(expoente & 1) result = result * base;
        base = base * base;
        expoente /= 2;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, a, b;
    cin >> a >> b >> n;

    Mat X(2,2);
    
    X.matriz[0][1] = 1;
    X.matriz[1][0] = -1;
    X.matriz[1][1] = 1;

    Mat y = fexp(X,n-1,2);

    ll ans = y.matriz[0][0] * a + y.matriz[0][1] * b;

    while(ans < 0)
        ans += MOD;

    cout << ans % MOD << endl;
}