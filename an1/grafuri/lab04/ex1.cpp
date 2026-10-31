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

    int n;
    fin >> n;

    vector<int> par(n);
    vector<int> cnt(n, 0);
    for(int i = 0; i < n; i++){
        fin >> par[i];

        if(par[i] != -1)
            cnt[par[i]]++;
    }

    vector<int> ans;

    int cur = 0;
    while(cur < n && cnt[cur] != 0)
        cur++;

    int leaf = cur;
    for(int i = 0; i < n - 1; i++){
        ans.push_back(par[leaf]);
        cnt[par[leaf]]--;

        if(cnt[par[leaf]] == 0 && par[leaf] < cur)
            leaf = par[leaf];
        else{
            cur++;
            while(cur < n && cnt[cur] != 0)
                cur++;
            leaf = cur;
        }
    }

    fout << ans.size() << '\n';
    for(auto i : ans)
        fout << i << ' ';

    fin.close();
    fout.close();

    return 0;
}