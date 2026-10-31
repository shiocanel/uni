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

    vector<vector<int>> a(n + 5, vector<int>(n + 5));
    int x, y;
    while(fin >> x >> y)
        a[x].push_back(y);

    vector<vector<int>> adj(n + 5);

    for(int i = 1; i <= n; i++){
        vector<int> v(n + 5, 0ll);
        
        queue<int> q;
        q.push(i);
        v[i] = 1;
        while(q.size()){
            int s = q.front();
            q.pop();

            for(auto j : a[s])
                if(v[j] == 0){
                    v[j] = 1;
                    q.push(j);
                }
        }

        adj[i] = v;
    }

    cout << "matrice tranzitiva:\n";
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)
            cout << adj[i][j] << ' ';
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