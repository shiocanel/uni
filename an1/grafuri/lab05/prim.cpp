/*
int n, m;
vector<int> d, ans;
vector<bool> v;
vector<vector<pii>> a;

void prim(int u){
    priority_queue<pii, vector<pii>, greater<pii>> q;

    d = vector<int> (n, inf);
    ans = vector<int> (n, -1);
    v = vector<bool> (n, 0);

    ans[u] = 0;
    d[u] = 0;

    q.push(make_pair(0, u));
    while(!q.empty()){
        int s = q.top().second;
        q.pop();

        if(v[s])
            continue;

        v[s] = 1;
        for(auto it : a[s]){
            int nv = it.first; // vecin
            int nc = it.second; // cost

            if(!v[nv] && d[nv] > nc){
                d[nv] = nc;
                q.push({d[nv], nv});
                ans[nv] = s;
            }
        }
    }
}

void solve(){  
    cin >> n >> m;

    a = vector<vector<pii>> (n);

    for(int i = 0; i < m; i++){
        int x, y, len;
        cin >> x >> y >> len;

        a[x].push_back({y, len});
        a[y].push_back({x, len});
    }

    prim(0);

    int res = 0;
    for(auto i : ans)
        res += i;

    cout << res << '\n';
    for(auto i : ans)
        cout << i << ' ';
    cout << '\n';
}
*/