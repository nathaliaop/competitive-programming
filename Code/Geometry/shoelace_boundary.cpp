// before dividing by two

int shoelace(vector<point> & points) {
    int n = points.size();
    vector<point> v(n + 2);
    
    for (int i = 1; i <= n; i++) {
        v[i] = points[i - 1];
    }
    v[n + 1] = points[0];
    
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (v[i].x * v[i + 1].y - v[i + 1].x * v[i].y);
    }
    
    sum = abs(sum);
    return sum;
}
 
int boundary_points(vector<point> & points) {
    int n = points.size();
    vector<point> v(n + 2);
    
    for (int i = 1; i <= n; i++) {
        v[i] = points[i - 1];
    }
    v[n + 1] = points[0];
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i].x == v[i + 1].x) ans += abs(v[i].y - v[i + 1].y) - 1;
        else if (v[i].y == v[i + 1].y) ans += abs(v[i].x - v[i + 1].x) - 1;
        else ans += gcd(abs(v[i].x - v[i + 1].x), abs(v[i].y - v[i + 1].y)) - 1;
    }
    return points.size() + ans;
}
