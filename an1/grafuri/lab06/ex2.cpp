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

const ll INF = (1LL << 60);

struct Dinic {
    struct Edge {
        int to, rev;
        ll cap;
    };

    int n;
    vector<vector<Edge>> g;
    vector<int> level, ptr;

    Dinic(int n = 0) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
        level.assign(n, 0);
        ptr.assign(n, 0);
    }

    int addEdge(int v, int to, ll cap) {
        Edge a{to, (int)g[to].size(), cap};
        Edge b{v, (int)g[v].size(), 0};
        g[v].push_back(a);
        g[to].push_back(b);
        return (int)g[v].size() - 1;
    }

    bool bfs(int s, int t) {
        fill(all(level), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : g[v]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int v, int t, ll pushed) {
        if (v == t || pushed == 0) 
            return pushed;

        for (int &cid = ptr[v]; cid < (int)g[v].size(); cid++) {
            Edge &e = g[v][cid];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                ll tr = dfs(e.to, t, min(pushed, e.cap));
                if (tr == 0) 
                    continue;
                e.cap -= tr;
                g[e.to][e.rev].cap += tr;
                return tr;
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(all(ptr), 0);
            while (ll pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

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

    int N, C, D;
    fin >> N >> C >> D;

    int S = N, T = N - 1;
    Dinic din(N + 1);

    vector<pair<int,int>> srcEdge(C);

    for (int i = 0; i < D; i++) {
        int x, y, m;
        fin >> x >> y >> m;
        din.addEdge(x, y, m);
    }

    for (int i = 0; i < C; i++) {
        int idx = din.addEdge(S, i, INF);
        srcEdge[i] = {S, idx};
    }

    ll ans = din.maxflow(S, T);

    fout << ans << '\n';
    for (int i = 0; i < C; i++) {
        int v = srcEdge[i].first;
        int idx = srcEdge[i].second;
        ll used = INF - din.g[v][idx].cap;
        fout << used << (i + 1 == C ? '\n' : ' ');
    }

    fin.close();
    fout.close();
    return 0;
}