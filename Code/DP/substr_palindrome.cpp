// você deve informar se a substring de S formada pelos elementos entre os indices i e j
// é um palindromo ou não.

char s[MAX];
int calculado[MAX][MAX]; // inciado com false, ou 0
int tabela[MAX][MAX];

int is_palin(int i, int j){
	if(calculado[i][j]){
		return tabela[i][j];
	}
	if(i == j) return true;
	if(i + 1 == j) return s[i] == s[j];

	int ans = false;
	if(s[i] == s[j]){
		if(is_palin(i+1, j-1)){
			ans = true;
		}
	}
	calculado[i][j] = true;
	tabela[i][j] = ans;
	return ans;
}