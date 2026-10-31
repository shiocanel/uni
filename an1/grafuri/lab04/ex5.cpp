#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <array>
using namespace std;
#define ull unsigned long long 
#define ld long double
#define ll long long
// #define int long long
#define pii pair<int, int>
#define all(v) v.begin(), v.end()
int mod = 1e9 + 7; 
const ll inf = 1e18;
const int N = 1e5 + 50, K = 22;

struct dsu{
    vector<int> p, sz;
    dsu(int n){
        p.resize(n);
        sz.resize(n);
        for(int i = 0; i<n; i++)
            p[i] = i, sz[i] = 1;
    }

    int find(int u){
        return p[u] == u ? u : p[u] = find(p[u]);
    }

    bool merge(int a, int b){
        a = find(a);
        b = find(b);

        if(a == b)
            return false;

        if(sz[a] < sz[b])
            swap(a, b);
        sz[a] += sz[b];
        p[b] = a;
        return true;
    }
};  

int32_t main(int32_t argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    //int t = 1;
    // cin >> t;
    // while(t--)
    //     solve();

    if(argc != 3){
        cout << "Insuficiente argumente!!!\n";
        return 0;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m;
    fin >> n >> m;

    vector<array<int, 3>> edges;
    for(int i = 0; i < m; i++){
        int x, y, w;
        fin >> x >> y >> w;
        
        edges.push_back({w, x, y});
    }

    dsu ds(n);

    vector<pii> ans;
    int res = 0;
    sort(all(edges));
    for(auto edge : edges){
        int w = edge[0];
        int x = edge[1];
        int y = edge[2];

        if(ds.merge(x, y)){
            res += w;
            ans.push_back({x, y});
        }
    }

    fout << res << '\n';
    fout << ans.size() << '\n';
    for(auto i : ans)
        fout << i.first << ' ' << i.second << '\n';

    // cout << "ok";
    
    fin.close();
    fout.close();

    return 0;
}