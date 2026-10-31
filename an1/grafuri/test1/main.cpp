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
    d.assign(n, inf);
    p.assign(n, -1);

    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, u});
    d[u] = 0;
    while(!q.empty()){
        int di = q.top().first;
        int s = q.top().second;
        q.pop();

        if(d[s] != di) // d[s] < di ?? actual cunoscut < ce vrea asta
            continue;
        
        for(auto i : a[s]){
            int to = i.first;
            int len = i.second;
        
            if(d[s] + len < d[to]){
                d[to] = d[s] + len;
                p[to] = s;
                q.push({d[to], to});
            }
        }
    }
}

void solve(){  
    cin >> n >> m;
    a = vector<vector<pii>> (n, vector<pii>(n));
    d = p = vector<int> (n);

    vector<pii> vf(n);

    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;

        vf[i] = {x, y};
    }

    while(m--){
        int x, y, d;
        cin >> x >> y;

        d = sqrt((vf[x].first - vf[y].first) * (vf[x].first - vf[y].first) + (vf[x].second - vf[y].second) * (vf[x].second - vf[y].second));

        a[x].push_back({y, d});
        a[y].push_back({x, d});
    }

    int u = 0;
    dij(u);

    cout << "d: ";
    for(auto i : d)
        cout << i << ' ';
    cout << '\n';

    cout << "p: ";
    for(auto i : p)
        cout << i << ' ';
    cout << '\n';
}






// O(n * m) cost negati = bellman

struct edge{
    int a, b, cost;
};

int n, m, s; // start
vector<edge> edges;
vector<int> d, p;

bool bellmanFord(){
    d = vector<int> (n, inf);
    p = vector<int> (n, -1);

    d[s] = 0;
    for(int i = 0; i < n - 1; i++)
        for(auto e : edges)
            if(d[e.a] < inf && d[e.b] > d[e.a] + e.cost){
                d[e.b] = d[e.a] + e.cost;
                p[e.b] = e.a;
            }

    for(auto e : edges)
        if(d[e.a] < inf && d[e.b] > d[e.a] + e.cost){
            cout << "AVEM CICLU NEGATIV\n";
            return false;
        }

    return true;
}


void solve(){
    cin >> n >> m;

    while(m--){
        int x, y, cost;
        cin >> x >> y >> cost;

        edges.push_back({x, y, cost});
    }

    cout << "start: " << endl;
    cin >> s;

    bellmanFord();

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