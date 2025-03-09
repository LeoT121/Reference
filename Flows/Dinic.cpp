///hackmd https://hackmd.io/@8iUL97mRS2mgfTEJDy5xmA/Bk2Q1K6vj
#define SET(p,n) memset(p, n, sizeof (p))
///MN number of nodes
///ME number of edges

const int INF = INT_MAX;
const int MN = 100010, ME = 500010;

int src, snk, nno, ned;
int q[MN], fin[MN], pro[MN], dist[MN];
int flow[2*ME], cap[2*ME];
int sig[2*ME], to[2*ME];

inline void init (int _src, int _snk, int _n) {
    src = _src, snk = _snk, nno = _n, ned = 0;
    SET(fin, -1);
}

inline void add (int u, int v, int c) {
    to[ned] = v, cap[ned] = c, flow[ned] = 0, sig[ned] = fin[u], fin[u] = ned++;
    to[ned] = u, cap[ned] = 0, flow[ned] = 0, sig[ned] = fin[v], fin[v] = ned++;
}

inline void reset (int _src, int _snk) {
    src = _src, snk = _snk;
    for (int i = 0; i < ned; i++)
        flow[i] = 0;
}

bool bfs () {
    int st, en, u, v;
    SET(dist, -1);

    dist[src] = st = en = 0;
    q[en++] = src;

    while (st < en) {
        u = q[st++];

        for (int e = fin[u]; e >= 0; e = sig[e]) {
            v = to[e];

            if (flow[e] < cap[e] && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q[en++] = v;
            }
        }
    }

    return dist[snk] != -1;
}

int dfs (int u, int mn) {
    if (u == snk)
        return mn;

    int au, v;
    for (int &e = pro[u]; e >= 0; e = sig[e]) {
        v = to[e];

        if (flow[e] < cap[e] && dist[v] == dist[u]+1)
            if (au = dfs(v, min(mn, cap[e] - flow[e]))) {
                flow[e] += au;
                flow[e^1] -= au;
                return au;
            }
    }

    return 0;
}

ll dinitz () {
    ll f = 0;
    int au;

    while (bfs()) {
        for (int i = 0; i <= nno; i++)
            pro[i] = fin[i];

        while (au = dfs(src, INF))
            f += au;
    }

    return f;
}
