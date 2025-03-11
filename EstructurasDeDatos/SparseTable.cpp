const int maxn = 1e5 + 5;
/// L es techo logaritmo base 2 de n
const int LOG = 17;
int n = 1e5;

int dp[LOG + 2][maxn];
int a[maxn];
int pot[maxn];

int op(int x, int y){
    /// operacion deseada
    return min(x, y);
}

void init(){
    ll potAct = 0, valAct = 1;
    for(ll i = 1; i <= n; ++i){
        if(valAct * 2ll <= i){
            valAct*= 2;
            potAct++;
        }
        pot[i] = potAct;
    }
    /// LOG = 0
    for(int i = 1; i <= n; ++i){
        dp[0][i] = a[i];
    }
    for(int j = 1; j <= LOG; ++j){
        for(int i = 1; i <= n; ++i){
            if(i + (1 << j) - 1 > n) break;
            dp[j][i] = op(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
        }
    }
}

int RMQ(int L_query, int R_query){
    /// se puede usar con MAX, MIN, GCD, LCM, AND, OR
    int tam = R_query - L_query + 1;
    int k = pot[tam];
    return op(dp[k][L_query], dp[k][R_query - (1 << k ) + 1]);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    return 0;
}
