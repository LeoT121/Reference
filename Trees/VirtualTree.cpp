const int MX = 2e5;

vector<vi> ST;
vi logs;
int K, N;

int h[MX + 2], node[MX + 2], sum[MX + 2][2], dist[MX + 2][2];
vi arr, tree[MX + 2], vtree[MX + 2];
pii euler[MX + 2];
bool used[MX + 2];
int k, root, sz;
int a[MX + 2];

bool sorteuler(int u, int v){
    return euler[u].fi < euler[v].fi;
}

void SparseTable(){
    N = arr.size();
    K = log2(N) + 2;
    ST.assign(K + 1, vector<int>(N));
    logs.assign(N + 1, 0);
    for(int i = 2; i <= N; ++i)
        logs[i] = logs[i >> 1] + 1;
    for(int i = 0; i < N; ++i)
        ST[0][i] = arr[i];
    for(int j = 1; j <= K; ++j)
        for(int i = 0; i + (1 << j) <= N; ++i)
            ST[j][i] = (h[ST[j - 1][i]] <= h[ST[j - 1][i + (1 << (j - 1))]]) ? ST[j - 1][i] : ST[j - 1][i + (1 << (j - 1))];
}

int LCA(int l, int r){
    int j = logs[r - l + 1];
    return (h[ST[j][l]] <= h[ST[j][r - (1 << j) + 1]]) ? ST[j][l] : ST[j][r - (1 << j) + 1];
}

void dfs(int u, int p){
    h[u] = h[p] + 1;
    euler[u] = {SZ(arr), SZ(arr)};
    arr.pb(u);
    foru(v, tree[u]){
        if(v == p) continue;
        dfs(v, u);
        euler[u].se = SZ(arr);
        arr.pb(u);
    }
}

void buildvirtualtree(){
    sz = k;
    forn(i, 1, k - 1){
        int aux = LCA(euler[node[i - 1]].fi, euler[node[i]].fi);
        if(!used[aux]){
            used[aux] = 1;
            node[sz ++] = aux;
        }
    }
    sort(ord0(node, sz), sorteuler);
    stack<int> s;
    root = -1;
    for0(i, sz){
        int add = node[i];
        if(root == -1) root = add;
        if(!s.empty()){
            while(euler[s.top()].se < euler[add].fi) s.pop();
            vtree[s.top()].pb(add);
            vtree[add].pb(s.top());
        }
        s.push(add);
    }
}

void clean(){
    for0(i, sz){
        vtree[node[i]].clear();
        used[node[i]] = 0;
    }
}

void solve(){
    int n;
    cin >> n;
    int u, v;
    for0(i, n - 1){
        cin >> u >> v;
        tree[u].pb(v);
        tree[v].pb(u);
    }
    arr.reserve(2 * n);
    dfs(1, 1);
    SparseTable();
    ///read the nodes or whatever you want in the virtual tree or maybe divisors
    ///those ways are the most common problems that can be solved using virtual tree
    ///to be honest I haven't solved a problem that involves divisors xd
    int q;
    cin >> q;
    while(q --){
        cin >> k;
        ///be sure to avoid repetitions of nodes
        ///because the algorithm only uses non duplicate nodes
        ///if there are duplicates nodes, just consider one and modify k
        ///for only non-duplicated nodes
        int w;
        for0(i, k){
            cin >> w;
            node[i] = w;
            used[w] = 1;
        }
        sort(ord0(node, k), sorteuler);
        buildvirtualtree();

        ///whatever you need to do in the virtual tree
        ///for example a dfs
        ///just be careful about the nodes that don't belong to the given set
        ///according to the problem those can be useful or not
        clean();
    }
}
