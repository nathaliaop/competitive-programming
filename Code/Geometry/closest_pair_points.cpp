// Description
// Find the squared distance between the closest two points among n points
// Also finds which pair of points is closest (could be more than one)

// Problem
// https://cses.fi/problemset/task/2194/

// Complexity
// O(n log n)

ll closest_pair_points(vp &vet){
    pair<point, point> ans;
    int n = vet.size();
    sort(vet.begin(), vet.end());
    set<point> s;

    ll best_dist = LLONG_MAX;
    int j=0;
    for(int i=0;i<n;i++){
        ll d = ceil(sqrt(best_dist));
        while(j<n and vet[i].x-vet[j].x >= d){
            s.erase(point(vet[j].y, vet[j].x));
            j++;
        }

        auto it1 = s.lower_bound({vet[i].y - d, vet[i].x});
        auto it2 = s.upper_bound({vet[i].y + d, vet[i].x});

        for(auto it=it1; it!=it2; it++){
            ll dx = vet[i].x - it->y;
            ll dy = vet[i].y - it->x;

            if(best_dist > dx*dx + dy*dy){
                best_dist = dx*dx + dy*dy;
                // closest pair points
                ans = mp(vet[i], point(it->y, it->x));
            }
        }

        s.insert(point(vet[i].y, vet[i].x));
    }

    // best distance squared
    return best_dist;
}
