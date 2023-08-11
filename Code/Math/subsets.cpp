void subsets(vector<int>& nums){
  int n = nums.size();
  int powSize = 1 << n;

  for(int counter = 0; counter < powSize; counter++) {
    for(int j = 0; j < n; j++) {
      if((counter & (1LL << j)) != 0) {
        cout << nums[j] << ' ';  
      }
      cout << '\n';
    }
  }
}
