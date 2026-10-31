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

struct edge{
    int a, b, cost;
};

int n, m;
vector<edge> edges;
vector<int> d, p;

bool bell(int u){
    d = vector<int> (n, inf);
    p = vector<int> (n, -1);

    d[u] = 0;
    for(int i = 0; i < n - 1; i++)
        for(auto e : edges)
            if(d[e.a] < inf && d[e.b] > d[e.a] + e.cost){
                d[e.b] = d[e.a] + e.cost;
                p[e.b] = e.a;
            }

    for(auto e : edges)
        if(d[e.a] < inf && d[e.b] > d[e.a] + e.cost){
            cout << "CICLU INFINIT!!!";
            return false;
        }

    return true;
}

void restore(int u, int v){
    if(d[v] == inf)
        return;

    vector<int> path;

    while(u != v){
        path.push_back(v);
        v = p[v];
    }
    path.push_back(u);

    reverse(all(path));

    for(auto i : path)
        cout << i << ' ';
    cout << '\n';
}

void solve(){
    cin >> n >> m;

    while(m--){
        int x, y, d;
        cin >> x >> y >> d;

        edges.push_back({x, y, d});
    }

    bell(0);

    restore(0, 4);

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