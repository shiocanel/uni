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
#include <numeric>
#include <functional>

using namespace std;

#define ull unsigned long long
#define ld long double
#define ll long long
#define int long long
#define pii pair<int, int>
#define all(v) v.begin(), v.end()

int32_t main(int32_t argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    if (argc != 3) {
        cout << "Insuficiente argumente!!!\n";
        return 0;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m;
    fin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> vis(n, 0), globalColor(n, -1);
    int answer = 0;

    for (int s = 0; s < n; s++) {
        if (vis[s]) 
            continue;

        queue<int> q;
        q.push(s);
        vis[s] = 1;

        vector<int> comp;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            comp.push_back(v);

            for (int u : adj[v]) {
                if (!vis[u]) {
                    vis[u] = 1;
                    q.push(u);
                }
            }
        }

        int comp_size = comp.size();
        vector<int> id(n, -1);
        for (int i = 0; i < comp_size; i++) 
            id[comp[i]] = i;

        vector<vector<int>> localAdj(comp_size);
        for (int i = 0; i < comp_size; i++) {
            int v = comp[i];
            for (int u : adj[v]) {
                if (id[u] != -1) 
                    localAdj[i].push_back(id[u]);
            }
        }

        vector<int> order(comp_size);
        iota(all(order), 0);
        sort(all(order), [&](int a, int b) {
            return localAdj[a].size() > localAdj[b].size();
        });

        int best_c = 0;
        vector<int> best_color_map(comp_size, -1);
        
        for (int v : order) {
            vector<bool> used(comp_size, false);
            for (int u : localAdj[v]) {
                if (best_color_map[u] != -1) {
                    used[best_color_map[u]] = true;
                }
            }
            int c = 0;
            while (used[c]) 
                c++;
            best_color_map[v] = c;
            best_c = max(best_c, c + 1);
        }

        vector<int> current_color(comp_size, -1);
        
        auto can_color = [&](int node, int c) {
            for (int u : localAdj[node]) {
                if (current_color[u] == c) 
                    return false;
            }
            return true;
        };

        function<void(int, int)> bkt = [&](int step, int colors_used) {
            if (colors_used >= best_c)
                return;

            if (step == comp_size) {
                best_c = colors_used;
                best_color_map = current_color;
                return;
            }

            int v = order[step];
            for (int c = 0; c <= colors_used; c++) {
                if (can_color(v, c)) {
                    current_color[v] = c;
                    bkt(step + 1, max(colors_used, c + 1));
                    current_color[v] = -1;
                }
            }
        };

        bkt(0, 0);

        answer = max(answer, best_c);
        for (int i = 0; i < comp_size; i++) {
            globalColor[comp[i]] = best_color_map[i];
        }
    }

    fout << answer << '\n';
    for (int i = 0; i < n; i++) {
        fout << globalColor[i] << (i + 1 == n ? "" : " ");
    }
    fout << '\n';

    fin.close();
    fout.close();
    return 0;
}