// gera todas as possíveis sequências usando as letras em set (de comprimento n) e que tenham tamanho k
// sequence = ""
vector<string> generate_sequences(char set[], string sequence, int n, int k) {
   if (k == 0){
       return { sequence };
   }

   vector<string> ans;
   for (int i = 0; i < n; i++) {
        auto aux = generate_sequences(set, sequence + set[i], n, k - 1);
        ans.insert(ans.end(), aux.begin(), aux.end());
        // for (auto e : aux) ans.push_back(e);
   }

   return ans;
}