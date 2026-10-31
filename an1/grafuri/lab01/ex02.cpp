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

vector<vector<bool>> a;

void solve(){  
    int n;
    fin >> n;

    a = vector<vector<bool>> (n + 5, vector<bool> (n + 5));
    int x, y;
    while(fin >> x >> y)
        a[x][y] = a[y][x] = 1;

    vector<int> deg(n + 5, 0ll);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            deg[i] += a[i][j];

    vector<int> nod_izol;
    for(int i = 1; i <= n; i++)
        if(deg[i] == 0)
            nod_izol.push_back(i);

    cout << "Nodurile izolate: " << (nod_izol.size() == 0 ? "vid" : "");
    for(auto i : nod_izol)
        cout << i << ' ';
    cout << '\n';

    bool regular = 1;
    for(int i = 2; i <= n; i++)
        regular &= (deg[i] == deg[i - 1]);

    cout << "Graful: " << (regular ? "" : "nu este") << " regular\n";

    vector<vector<int>> fw(n + 5, vector<int>(n + 5, 0));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(a[i][j] == 1)
                fw[i][j] = 1;
            else if(i == j)
                fw[i][j] = 0;
            else
                fw[i][j] = inf;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            for(int k = 1; k <= n; k++)
                fw[i][k] = min(fw[i][k], fw[i][j] + fw[j][k]);

    cout << "Matricea distantelor: \n";
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)
            cout << fw[i][j] << ' ';
        cout << '\n';
    }

    vector<bool> v(n + 5, 0);
    queue<int> q;
    q.push(1);
    while(q.size()){
        int s = q.front();
        q.pop();

        v[s] = 1;
        for(int i = 1; i <= n; i++)
            if(a[i][s] && !v[i])
                q.push(i), v[i] = 1;
    }

    bool conex = 1;
    for(int i = 1; i <= n; i++)
        conex &= v[i];

    cout << "Graful: " << (conex ? "" : "nu") << " este conex";
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