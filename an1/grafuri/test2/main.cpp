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
const ll inf = 1e9;
const int N = 1e5 + 50, K = 22;

int n, m;
vector<int> d, p;
vector<bool> v;
vector<vector<pii>> a;

/*
algoritmul lui Prim este unul greedy care se bazeaza pe urmatorul concept
1) avand o lista de muchii ponderate o scoatem din lista si
    daca nodul in care ajungem este deja vizitat NU FACEM NIMIC (nu ajuta la mst)
    in caz contrar parcurgem muchia

2) actualizam lista de muchii cu muchii noi descoperite din nodul anterior 

3) repetam 1) si 2) pana nu mai avem muchii noi

astfel obtine un mst dintr-un nod u la celalte noduri posibil accesibile


EXEMPLU REAL:
Boc vrea sa repare unele strazi dar totusi cu cost cat mai mic posibil dart sa fie posibil 
sa ajungi din orice localitate in toate localitatile prin strazile reparate

aplicam Prim si gasim un mst cu cost minim iar celalte strazi raman generatiilor viitoare
*/
void prim(int u){
    priority_queue<pii, vector<pii>, greater<pii>> q;

    d = vector<int> (n, inf);
    p = vector<int> (n, -1);
    v = vector<bool> (n, 0);

    d[u] = 0;

    q.push(make_pair(0, u));
    while(!q.empty()){
        int s = q.top().second;
        q.pop();

        if(v[s])
            continue;

        v[s] = 1;
        for(auto it : a[s]){
            int nv = it.first;
            int nc = it.second;

            if(!v[nv] && d[nv] > nc){
                d[nv] = nc;
                q.push({d[nv], nv});
                p[nv] = s;
            }
        }
    }
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

    fin >> n >> m;

    a = vector<vector<pii>> (n);

    for(int i = 0; i < m; i++){
        int x, y, len;
        fin >> x >> y >> len;

        a[x].push_back({y, len});
        a[y].push_back({x, len});
    }

    prim(0);

    int res = 0;
    for(auto i : d)
        res += i;

    fout << res << '\n';
    fout << "d: ";
    for(auto i : d)
        fout << i << ' ';
    fout << '\n';

    fout << "p: ";
    for(auto i : p)
        fout << i << ' ';
    fout << '\n';

    fin.close();
    fout.close();

    return 0;
}