#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
using namespace std;
#define ull unsigned long long 
#define ld long double
#define ll long long
#define int long long
#define pii pair<int, int>
#define all(v) v.begin(), v.end()
int mod = 1e9 + 7; 
const ll inf = 1e18;
const int N = 1e5 + 50, K = 22;

// O ((n + m) * log n) - cost pozitiv = dijkstra

int n, m;
vector<vector<pii>> a;
vector<int> d, p;

void dij(int u){
    d = vector<int> (n, inf);
    p = vector<int> (n, -1);

    priority_queue<pii, vector<pii>, greater<pii>> q;
    d[u] = 0;
    q.push({0, u});

    while(q.size()){
        int di = q.top().first;
        int s = q.top().second;
        q.pop();

        if(di != d[s])
            continue;

        for(auto i : a[s]){
            int to = i.first;
            int len = i.second;

            if(d[to] > d[s] + len){
                d[to] = d[s] + len;
                p[to] = s;
                q.push({d[to], to});
            }
        }
    }
}

void solve(){
    cin >> n >> m;
    a = vector<vector<pii>> (n);

    while(m--){
        int x, y, d;
        cin >> x >> y >> d;

        a[x].push_back({y, d});
    }

    dij(0);

    cout << "d: ";
    for(auto i : d)
        cout << i << ' ';
    cout << '\n';

    cout << "p: ";
    for(auto i : p)
        cout << i << ' ';
    cout << '\n';



    /*
5 6
0 1 2
0 2 4
1 2 1
1 3 7
2 4 3
3 4 1
start: 
1
    */
}


/*
    dijkstra -> ponderi pozitive
    bellman-ford -> ponderi negative


*/

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while(t--)
        solve();
        
    return 0;
}