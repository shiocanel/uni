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

struct Edge {
    int to;
    int cap;
    int flow;
    int rev;
};

vector<vector<Edge>> adj;

void add_edge(int u, int v, int cap) {
    adj[u].push_back({v, cap, 0, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
}

int bfs(int s, int t, vector<int>& parent, vector<int>& parent_edge){
    fill(all(parent), -1);
    parent[s] = -2;
    
    queue<pair<int, int>> q;
    q.push({s, 2e9});

    while(!q.empty()){
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for(int i = 0; i < adj[cur].size(); i++){
            Edge& e = adj[cur][i];
            
            if(parent[e.to] == -1 && e.cap - e.flow > 0){
                parent[e.to] = cur;
                parent_edge[e.to] = i;
                
                int new_flow = min(flow, e.cap - e.flow);
                
                if(e.to == t){
                    return new_flow;
                }

                q.push({e.to, new_flow});
            }
        }
    }
    return 0;
}

int edmonds_karp(int s, int t, int n){
    int flow = 0;
    vector<int> parent(n);
    vector<int> parent_edge(n);
    int new_flow;

    while(true){
        new_flow = bfs(s, t, parent, parent_edge);
        if(new_flow == 0){
            break;
        }
        
        flow += new_flow;
        int cur = t;
        
        while(cur != s){
            int p = parent[cur];
            int idx = parent_edge[cur];
            
            adj[p][idx].flow += new_flow;
            adj[cur][adj[p][idx].rev].flow -= new_flow;
            
            cur = p;
        }
    }
    return flow;
}

int32_t main(int32_t argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    if(argc != 3){
        cout << "Insuficiente argumente!!!\n";
        return 0;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m;
    if(!(fin >> n >> m)) 
        return 0;

    adj.assign(n, vector<Edge>());

    for(int i = 0; i < m; i++){
        int x, y, c;
        fin >> x >> y >> c;
        add_edge(x, y, c);
    }

    int max_flow = edmonds_karp(0, n - 1, n);

    fout << max_flow << '\n';

    fin.close();
    fout.close();

    return 0;
}