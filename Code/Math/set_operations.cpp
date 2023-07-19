// Complexity;
// O(n * m) being n and m the sizes of the two sets
// 2*(count1+count2)-1 (where countX is the distance between firstX and lastX):

vector<int> res;
set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(res, res.begin()));
set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(res, res.begin()));
// present in the first set, but not in the second
set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(res, res.begin()));
// present in one of the sets, but not in the other
set_symmetric_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(res, res.begin()));
