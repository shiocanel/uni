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

vector<edge> edges;
int n, m;
vector<vector<pii>> a;
vector<int> d, p;

void dij(int u){
    d = vector<int> (n, inf);
    p = vector<int> (n, -1);

    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, u});
    d[u] = 0;

    while(q.size()){
        int di = q.top().first;
        int s = q.top().second;
        q.pop();

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
        if(d[e.a] < inf && d[e.b] > d[e.a] + e.cost)
            return false;
        
    return true;
}

void solve(){
    string inFile, outFile;
    cin >> inFile >> outFile;

    ifstream fin(inFile);
    ofstream fout(outFile);

    fin >> n >> m;

    edges.clear();
    a.assign(n, {});

    for(int i = 0; i < m; i++){
        int x, y, w;
        fin >> x >> y >> w;
        edges.push_back({x, y, w});
    }

    vector<edge> all_edges = edges;

    for(int i = 0; i < n; i++){
        all_edges.push_back({n, i, 0});
    }

    vector<int> h(n + 1, inf);
    h[n] = 0;

    for(int i = 0; i < n; i++)
        for(auto e : all_edges)
            if(h[e.a] < inf && h[e.b] > h[e.a] + e.cost)
                h[e.b] = h[e.a] + e.cost;

    for(auto e : all_edges)
        if(h[e.a] < inf && h[e.b] > h[e.a] + e.cost){
            fout << -1;
            return;
        }

    a.assign(n, {});

    for(auto &e : edges){
        int nou_cost = e.cost + h[e.a] - h[e.b];
        a[e.a].push_back({e.b, nou_cost});
        e.cost = nou_cost;
    }

    sort(all(edges), [](edge a, edge b){
        if(a.a != b.a) 
            return a.a < b.a;
        return a.b < b.b;
    });

    for(auto e : edges)
        fout << e.a << " " << e.b << " " << e.cost << "\n";

    vector<vector<int>> dist(n, vector<int>(n, inf));

    for(int i = 0; i < n; i++){
        dij(i);

        for(int j = 0; j < n; j++)
            if(d[j] < inf)
                dist[i][j] = d[j] - h[i] + h[j];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(dist[i][j] == inf) 
                fout << "INF ";
            else 
                fout << dist[i][j] << " ";
        }
        fout << "\n";
    }
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