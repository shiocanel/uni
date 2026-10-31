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
#define pii pair<int, int>
#define all(v) v.begin(), v.end()

int mod = 1e9 + 7; 
const ll inf = 1e18;
const int N = 101005; 

/*
dijstrka si bellman(slabe sanse) 
prim,kruskal si edmond-karp
si ceva codedare decodare huffman idk n am invatat
*/

vector<vector<pii>> adj;
vector<int> head;
vector<bool> used;

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

    adj.assign(n, vector<pii>());
    head.assign(n, 0);
    used.assign(m, false);

    for(int i = 0; i < m; i++){
        int x, y;
        fin >> x >> y;
        adj[x].push_back({y, i});
        adj[y].push_back({x, i});
    }

    int start = 0;
    for(int i = 0; i < n; i++){
        if(!adj[i].empty()){
            start = i;
            break;
        }
    }

    vector<int> ans;
    stack<int> st;
    st.push(start);

    while(!st.empty()){
        int u = st.top();
        
        if(head[u] < adj[u].size()){
            pii edge = adj[u][head[u]];
            head[u]++;
            
            int v = edge.first;
            int id = edge.second;
            
            if(!used[id]){
                used[id] = true;
                st.push(v);
            }
        } 
        else{
            ans.push_back(u);
            st.pop();
        }
    }

    if(!ans.empty()){
        ans.pop_back();
    }

    for(int i = 0; i < ans.size(); i++)
        fout << ans[i] << ' ';
    fout << '\n';

    fin.close();
    fout.close();

    return 0;
}