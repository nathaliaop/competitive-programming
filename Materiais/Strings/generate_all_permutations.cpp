vector<string> generate_permutations(string s) {
    int n = s.size();
    vector<string> ans;
    
    sort(s.begin(), s.end());
    
    do {
        ans.push_back(s);
    } while (next_permutation(s.begin(), s.end()));
    
    return ans;
}