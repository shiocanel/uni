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

struct Edge{
    int to;
    int cap;
    int flow;
    int rev;
};

vector<vector<Edge>> adj;

void add_edge(int u, int v, int cap){
    adj[u].push_back({v, cap, 0, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
}

int push_relabel(int s, int t, int n){
    vector<int> h(n, 0);
    vector<int> e(n, 0);
    vector<bool> active(n, false);
    queue<int> q;

    h[s] = n;
    for(int i = 0; i < adj[s].size(); i++){
        Edge& edge = adj[s][i];
        int push_val = edge.cap;
        if(push_val == 0) 
            continue;
        
        edge.flow += push_val;
        adj[edge.to][edge.rev].flow -= push_val;
        e[s] -= push_val;
        e[edge.to] += push_val;
        
        if(edge.to != s && edge.to != t && !active[edge.to]){
            active[edge.to] = true;
            q.push(edge.to);
        }
    }

    vector<int> ptr(n, 0);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        active[u] = false;

        while(e[u] > 0){
            if(ptr[u] < adj[u].size()){
                Edge& edge = adj[u][ptr[u]];
                int v = edge.to;
                
                if(edge.cap - edge.flow > 0 && h[u] == h[v] + 1){
                    int push_val = min(e[u], edge.cap - edge.flow);
                    edge.flow += push_val;
                    adj[v][edge.rev].flow -= push_val;
                    e[u] -= push_val;
                    e[v] += push_val;

                    if(v != s && v != t && !active[v] && e[v] > 0){
                        active[v] = true;
                        q.push(v);
                    }
                } 
                else{
                    ptr[u]++;
                }
            } 
            else{
                int min_h = 2e9;
                for(auto& edge : adj[u]){
                    if(edge.cap - edge.flow > 0){
                        min_h = min(min_h, h[edge.to]);
                    }
                }
                h[u] = min_h + 1;
                ptr[u] = 0;
            }
        }
    }
    
    return e[t];
}

int32_t main(int argc, char* argv[]){
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

    int max_flow = push_relabel(0, n - 1, n);

    fout << max_flow << '\n';

    fin.close();
    fout.close();

    return 0;
}