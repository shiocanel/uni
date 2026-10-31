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
#include <string>
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

ifstream fin("labirint_2.txt");

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int n, m;

bool inside(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
}

void solve(){  
    vector<string> grid;
    string s;

    while(getline(fin, s))
        grid.push_back(s);

    n = grid.size();
    m = grid[0].size();

    vector<vector<int>> dist(n, vector<int>(m, -1));
    vector<vector<pii>> parent(n, vector<pii>(m, {-1, -1}));

    int xs = -1, ys = -1, xf = -1, yf = -1;

    for(int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if(grid[i][j] == 'S'){
                xs = i;
                ys = j;
            }
            if(grid[i][j] == 'F'){
                xf = i;
                yf = j;
            }
        }
    }

    if(xs == -1 || xf == -1){
        return;
    }

    queue<pii> q;
    q.push({xs, ys});
    dist[xs][ys] = 0;

    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop();

        for(int k = 0; k < 4; k++){
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(inside(nx, ny) && grid[nx][ny] != '1' && dist[nx][ny] == -1){
                dist[nx][ny] = dist[x][y] + 1;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }

    if(dist[xf][yf] == -1){
        cout << "Nu exista drum!\n";
        return;
    }

    cout << "sistanta minima: " << dist[xf][yf] << "\n";

    int x = xf, y = yf;
    while(!(x == xs && y == ys)){
        if (grid[x][y] != 'F')
            grid[x][y] = '*';

        auto p = parent[x][y];
        x = p.first;
        y = p.second;
    }

    cout << "sol:\n";
    for(int i = 0; i < n; i++){
        cout << grid[i] << '\n';
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