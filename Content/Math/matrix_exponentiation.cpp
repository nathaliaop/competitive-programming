// Description:
// Calculate the nth term of a linear recursion

// Example Fibonacci:
// Given a linear recurrence, for example fibonacci
// F(n) = n, x <= 1
// F(n) = F(n - 1) + F(n - 2), x > 1

// The recurrence has two terms, so we can build a matrix 2 x 1 so that
// n + 1 = transition * n

// (2 x 1) = (2 x 2) * (2 x 1)
// F(n)      = a b * F(n - 1)
// F(n - 1)    c d   F(n - 2)

// Another Example:
// Given a grid 3 x n, you want to color it using 3 distinct colors so that
// no adjacent place has the same color. In how many different ways can you do that?
// There are 6 ways for the first column to be colored using 3 distinct colors
// ans 6 ways using 2 equal colors and 1 distinct one

// Adding another column, there are:
// 3 ways to go from 2 equal to 2 equal
// 2 ways to go from 2 equal to 3 distinct
// 2 ways to go from 3 distinct to 2 equal
// 2 ways to go from 3 distinct to 3 distinct

// So we star with matrix 6 6 and multiply it by the transition 3 2 and get 18 12
//                        6 6                                   2 2         12 12
// the we can exponentiate this matrix to find the nth column

// Problem:
// https://cses.fi/problemset/task/1722/

// Complexity:
// O(log n)

// How to use:
// vector<vector<ll>> v = {{1, 1}, {1, 0}};
// Matriz transition = Matriz(v);
// cout << fexp(transition, n)[0][1] << '\n';

using ll = long long;
 
const int MOD = 1e9+7;
 
struct Matriz{
    vector<vector<ll>> mat;
    int rows, columns;
    
    vector<ll> operator[](int i){
        return mat[i];
    }
 
    Matriz(vector<vector<ll>>& matriz){
        mat = matriz;
        rows = mat.size();
        columns = mat[0].size();
    }
    
    Matriz(int row, int column, bool identity=false){ 
        rows = row;  columns = column;
        mat.assign(rows, vector<ll>(columns, 0));
        if(identity) {
            for(int i = 0; i < min(rows,columns); i++) {
                mat[i][i] = 1;
            }
        }
    }
 
    Matriz operator * (Matriz a) {
        assert(columns == a.rows);
        vector<vector<ll>> resp(rows, vector<ll>(a.columns, 0));
 
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < a.columns; j++){
                for(int k = 0; k < a.rows; k++){
                    resp[i][j] = (resp[i][j] + (mat[i][k] * 1LL * a[k][j]) % MOD) % MOD;
                }
            }
        }
        return Matriz(resp);
    }
 
    Matriz operator + (Matriz a) {
        assert(rows == a.rows && columns == a.columns); 
        vector<vector<ll>> resp(rows, vector<ll>(columns,0));
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                resp[i][j] = (resp[i][j] + mat[i][j] + a[i][j]) % MOD;
            }
        }
        return Matriz(resp);
    }
};
 
Matriz fexp(Matriz base, ll exponent){
    Matriz result = Matriz(base.rows, base.rows, 1);
    while(exponent > 0){
        if(exponent & 1LL) result = result * base;
        base = base * base;
        exponent  = exponent >> 1;
    }
    return result;
}