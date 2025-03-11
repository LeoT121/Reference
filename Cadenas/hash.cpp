const ll base = 131, base2 = 31;
const ll MOD = 1e9 + 7;
const ll MOD2 = 998244353;

int t, n;
char a[maxn];
ll h[maxn], h2[maxn], B[maxn];
ll hR[maxn], hR2[maxn], B2[maxn];

void sacar_Hash(){
    B[0] = 1;
    B2[0] = 1;
    for(int i = 1; i <= n; ++i){
        B[i] = B[i - 1] * base;
        B[i]%= MOD;
        B2[i] = B2[i - 1] * base2;
        B2[i]%= MOD2;
    }
    for(int i = 1; i <= n; ++i){
        ll c = a[i];
        h[i] = (((h[i - 1] * base) % MOD) + c) % MOD;
        h2[i] = (((h2[i - 1] * base2) % MOD2) + c) % MOD2;
        ///hash para la cadena reverse
        c = a[n - i + 1];
        hR[i] = (((hR[i - 1] * base) % MOD) + c) % MOD;
        hR2[i] = (((hR2[i - 1] * base2) % MOD2) + c) % MOD2;
        ///
    }
}

bool queryH(int L, int R){
    /// h y hR son sobre la misma cadena solo con diferente base y modulo
    ll val1 = ((h[R] - ((h[L - 1] * B[R - L + 1]) % MOD) + MOD) % MOD);
    ll val3 = ((h2[R] - ((h2[L - 1] * B2[R - L + 1]) % MOD2) + MOD2) % MOD2);
    /// hash para la cadena reverse (checar si son palindromos)
    int L2 = n - R + 1;
    int R2 = n - L + 1;
    ll val2 = ((hR[R2] - ((hR[L2 - 1] * B[R2 - L2 + 1]) % MOD) + MOD) % MOD);
    ll val4 = ((hR2[R2] - ((hR2[L2 - 1] * B2[R2 - L2 + 1]) % MOD2) + MOD2) % MOD2);
    return ((val1 == val2) && (val3 == val4));
    ///
}