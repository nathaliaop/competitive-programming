// achar a quantidade de numeros menores que R que possuem no maximo 3 digitos nao nulos
// a ideia eh utilizar da ordem lexicografica para checar isso pois se temos por exemplo
// o numero 8500, a gente sabe que se pegarmos o numero 7... qualquer digito depois do 7
// sera necessariamente menor q 8500

string r;
int tab[20][2][5];

// i - digito de R
// menor - ja pegou um numero menor que um digito de R
// qt - quantidade de digitos nao nulos
int dp(int i, bool menor, int qt){
    if(qt > 3) return 0;
    if(i >= r.size()) return 1;
    if(tab[i][menor][qt] != -1) return tab[i][menor][qt];
 
    int dr = r[i]-'0';
    int res = 0;

    for(int d = 0; d <= 9; d++) {
        int dnn = qt + (d > 0);
        if(menor == true) {
            res += dp(i+1, true, dnn);
        }
        else if(d < dr) {
            res += dp(i+1, true, dnn);
        }
        else if(d == dr) {
            res += dp(i+1, false, dnn);
        }
    }

    return tab[i][menor][qt] = res;
}