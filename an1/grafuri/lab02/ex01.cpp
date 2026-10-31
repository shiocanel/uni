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

    vector<vector<int>> a(n + 5);
    int x, y;
    while(fin >> x >> y)
        a[x].push_back(y);

    // moore sau bfs cu parinti si dist
    vector<int> d(n + 5, inf);
    vector<int> p(n + 5, 0);

    int s = 0;
    cout << "Start: " << endl;
    cin >> s;
    
    queue<int> q;
    q.push(s);
    d[s] = p[s] = 0;
    while(q.size()){
        int x = q.front();
        q.pop();

        for(auto i : a[x])
            if(d[i] == inf){
                d[i] = d[x] + 1;
                p[i] = x;
                q.push(i);
            }
    }

    cout << "d: ";
    for(int i = 1; i <= n; i++)
        cout << d[i] << ' ';
    cout << '\n';

    cout << "p: ";
    for(int i = 1; i <= n; i++) 
        cout << p[i] << ' ';
    cout << '\n';


    
    cout << "End: " << endl;
    int v = 0;
    cin >> v;

    vector<int> ans(d[v] + 5);

    int k = d[v];
    ans[k] = v;
    while(k != 0){
        ans[k - 1] = p[ans[k]];
        k--;
    }

    cout << "ans: ";
    for(int i = 0; i <= d[v]; i++)
        cout << ans[i] << ' ';
    cout << '\n';
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