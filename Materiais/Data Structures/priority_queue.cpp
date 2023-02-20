// Description:
// Keeps the largest (by default) element at the top of the queue

// Problem:
// https://cses.fi/problemset/task/1164/

// Complexity:
// O(log n) for push and pop
// O (1) for looking at the element at the top

// How to use:
// prioriy_queue<int> pq;
// pq.push(1);
// pq.top();
// pq.pop()

// Notes
// To use the priority queue keeping the smallest element at the top

priority_queue<int, vector<int>, greater<int>> pq;