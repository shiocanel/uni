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

    int s;
    cout << "Start: " << endl;
    cin >> s;

    queue<int> q;
    q.push(s);
    vector<int> d(n + 5, inf);
    d[s] = 0;

    vector<int> ordine;
    ordine.push_back(s);
    while(q.size()){
        int x = q.front();
        q.pop();

        for(auto i : a[x])
            if(d[i] == inf){
                d[i] = d[x] + 1;
                ordine.push_back(i);
                q.push(i);
            }
    }

    cout << "Ordine bfs: ";
    for(auto i : ordine)
        cout << i << ' ';
    cout << '\n';

    cout << "Distanta  : ";
    for(auto i : ordine)
        cout << d[i] << ' ';
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