const int maxn = 1e4 + 5;
int n;

/// L: profundidad de cada nodo visitado
/// E: secuencia de nodos visitados
/// H: indice de la primera aparicion del nodo i en E
int L[2 * maxn], E[2 * maxn], H[maxn], idx = 0;
vector<int> children[maxn];
///
/// L es techo logaritmo base 2 de n
const int LOG = 14;

/// dp en 0 es la profundidad minima, en 1 es el nodo de profundidad minima
int dp[LOG + 2][maxn * 2][2];
int pot[maxn * 2];

int op(int x, int y){
    /// operacion deseada
    return min(x, y);
}

void init(){
    ll potAct = 0, valAct = 1;
    for(ll i = 1; i <= idx; ++i){
        if(valAct * 2ll <= i){
            valAct*= 2;
            potAct++;
        }
        pot[i] = potAct;
    }
    /// j = 0
    for(int i = 0; i < idx; ++i){
        dp[0][i][0] = L[i];
        dp[0][i][1] = E[i];
    }
    for(int j = 1; j <= LOG; ++j){
        for(int i = 0; i < idx; ++i){
            if(i + (1 << j) - 1 > idx - 1) break;
            dp[j][i][0] = op(dp[j - 1][i][0], dp[j - 1][i + (1 << (j - 1))][0]);
            if(dp[j][i][0] == dp[j - 1][i][0]){
                dp[j][i][1] = dp[j - 1][i][1];
            }else{
                dp[j][i][1] = dp[j - 1][i + (1 << (j - 1))][1];
            }
        }
    }
}

int RMQ(int L_query, int R_query){
    /// se puede usar con MAX, MIN, GCD, LCM, AND, OR
    int tam = R_query - L_query + 1;
    int k = pot[tam];
    int valMin = op(dp[k][L_query][0], dp[k][R_query - (1 << k ) + 1][0]);
    if(valMin == dp[k][L_query][0]){
        return dp[k][L_query][1];
    }else{
        return dp[k][R_query - (1 << k ) + 1][1];
    }
}
///
void dfs(int cur, int depth){
    H[cur] = idx;
    E[idx] = cur;
    L[idx++] = depth;
    for(auto &nxt: children[cur]){
        dfs(nxt, depth + 1);
        E[idx] = cur;
        L[idx++] = depth;
    }
}

void buildRMQ(){
    idx = 0;
    int raiz = 0;
    dfs(raiz, 0);
}

int LCA(int u, int v){
    if(H[u] > H[v]) swap(u, v);
    return RMQ(H[u], H[v]);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; ++i){
        int m; cin >> m;
        for(int j = 1; j <= m; ++j){
            int v; cin >> v;
            children[i].push_back(v);
        }
    }
    /// llamadas a las funciones
    buildRMQ();
    init();

    int q; cin >> q;
    while(q--){
        int u, v; cin >> u >> v;
        cout << LCA(u, v) << "\n";
    }
    return 0;
}
