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

ifstream fin("graf.txt");

void solve(){  
    int n;
    fin >> n;

    vector<vector<bool>> adj(n + 5, vector<bool> (n + 5, 0));
    int x, y;
    while(fin >> x >> y){
        adj[x][y] = adj[y][x] = 1;
    }

    cout << "Matrice de adiacenta: \n";
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)
            cout << adj[i][j] << ' ';
        cout << '\n';
    }

    vector<vector<int>> adj_list(n + 5);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(adj[i][j])
                adj_list[i].push_back(j);

    cout << "Lista de adiacenta: \n";
    for(int i = 1; i <= n; i++){
        cout << i << " : ";
        for(auto j : adj_list[i])
            cout << j << ' ';
        cout << '\n';
    }

    vector<pii> edges;
    for(int i = 1; i <= n; i++){
        for(auto j : adj_list[i])
            if(i < j)
                edges.push_back({i, j});
    }

    int sz_edges = (int)edges.size();
    vector<vector<bool>> mat_inci(n + 5, vector<bool>(sz_edges + 5, 0));
    for(int i = 0; i < sz_edges; i++){
        auto [x, y] = edges[i];

        mat_inci[x][i] = mat_inci[y][i] = 1;
    }

    cout << "Matice de incidenta: \n";
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < sz_edges; j++)
            cout << mat_inci[i][j] << ' ';
        cout << '\n';
    }



    vector<vector<int>> adj_list2(n + 5);

    for(int j = 0; j < sz_edges; j++){
        vector<int> edge;
        for(int i = 1; i <= n; i++)
            if(mat_inci[i][j])
                edge.push_back(i);

        adj_list2[edge[0]].push_back(edge[1]);
        adj_list2[edge[1]].push_back(edge[0]);
    }

    cout << "Lista de adiacenta2: \n";
    for(int i = 1; i <= n; i++){
        cout << i << " : ";
        for(auto j : adj_list2[i])
            cout << j << ' ';
        cout << '\n';
    }


    vector<vector<bool>> adj2(n + 5, vector<bool> (n + 5, 0));

    for(int i = 1; i <= n; i++)
        for(auto j : adj_list2[i])
            adj2[i][j] = adj2[j][i] = 1;

    cout << "Matrice de adiacenta2: \n";
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)
            cout << adj2[i][j] << ' ';
        cout << '\n';
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