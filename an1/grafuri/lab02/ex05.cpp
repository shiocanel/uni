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
vector<bool> v;

void dfs(vector<vector<int>> a, int u){
    cout << u << ' ';
    
    v[u] = 1;
    for(auto i : a[u])
        if(!v[i])
            dfs(a, i);
}

void solve(){  
    int n;
    fin >> n;

    v = vector<bool> (n + 5, 0);
    vector<vector<int>> a(n + 5);
    int x, y;
    while(fin >> x >> y)
        a[x].push_back(y);

    int s;
    cout << "Start: " << endl;
    cin >> s;

    dfs(a, s);
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