// Description:
// Finds the maximum (or minimum) sum of some subarray of a given array

// Problem:
// https://leetcode.com/problems/maximum-subarray/description/

// Complexity:
// O(n)

// Notes
// To solve the minimum subarray problem, start the variable ans with INF and change the max operations to min operations
// To not count the empty subarray as a subrray, start the variable ans with -INF
// To get the biggest possible subarray with that sum, change if (curr > ans) to if (curr >= ans)
// If the empty subarray is the answer, start and end will be equal to -1

int ans = 0, curr = 0;
int startidx = 0, start = -1, end = -1;

for (int i = 0; i < n; i++) {
  // MAXIMUM SUBARRAY PROBLEM
  curr = max(curr + v[i], v[i]);
  ans = max(ans, curr);
  
  /*
  RECOVER INDEXES MAXIMUM SUBARRAY PROBLEM
  if (curr + v[i] < v[i]) {
    startidx = i;
    curr = v[i];
  }
  else curr += v[i];
  
  if (curr > ans) {
    ans = curr;
    start = startidx;
    end = i;
  }
  */

  // MINIMUM SUBARRAY PROBLEM
  // curr = min(curr + v[i], v[i]);
  // ans = min(ans, curr);
  
  /*
  // MINIMUM SUBARRAY PROBLEM
  if (curr + v[i] > v[i]) {
    startidx = i;
    curr = v[i];
  }
  else curr += v[i];
  
  if (curr < ans) {
    ans = curr;
    start = startidx;
    end = i;
  }
  */ 
}
 
// cout << ans << ' ' << start << ' ' << end << '\n';
