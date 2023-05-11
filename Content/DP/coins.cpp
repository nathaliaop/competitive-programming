int tb[1005];
int n;
vector<int> moedas;

int dp(int i){
	if(i >= n)
		return 0;
	if(tb[i] != -1)
		return tb[i];

	tb[i] = max(dp(i+1), dp(i+2) + moedas[i]);
	return tb[i];
}

int main(){
	memset(tb,-1,sizeof(tb));
}