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

// void solve(){

// }

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

    int m;
    fin >> m;

    int n = m + 1;
    vector<int> a(m);
    vector<int> cnt(n, 1ll);
    for(int i = 0; i < m; i++){
        fin >> a[i];
        cnt[a[i]]++;
    }

    vector<int> par(n, -1);
    int cur = 0;
    while(cur < n && cnt[cur] != 1)
        cur++;

    int leaf = cur;
    for(int i = 0; i < m; i++){
        int u = a[i];
        
        par[leaf] = u;
        cnt[u]--;

        if(cnt[u] == 1 && u < cur)
            leaf = u;
        else{
            cur++;
            while(cur < n && cnt[cur] != 1)
                cur++;
            leaf = cur;
        }
    }

    fout << n << '\n';
    for(auto i : par)
        fout << i << ' ';

    fin.close();
    fout.close();

    return 0;
}