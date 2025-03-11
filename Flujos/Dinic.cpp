#include<bits/stdc++.h>
#define SET(p,n) memset(p, n, sizeof (p))

using namespace std;

const int INF = INT_MAX;
/// INF, valor mayor a las capacidades de las aristas
const int MN = 100010, ME = 500010;
/// MN, cantidad maxima de nodos
/// ME, cantidad maxima de aristas
typedef long long ll;

int src, snk, nno, ned;
int q[MN], fin[MN], pro[MN], dist[MN];
int flow[2*ME], cap[2*ME];
int sig[2*ME], to[2*ME];

/// S, T, nodos
inline void init (int _src, int _snk, int _n) {
	src = _src, snk = _snk, nno = _n, ned = 0;
	for(int i = 0; i <= _n; ++i) fin[i] = -1;
	///SET(fin, -1);
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

/// Como recorrer la lista de adyacencia de un nodo U
/*
    int u;
    for (int e = fin[u]; e >= 0; e = sig[e]) {
        int v = to[e];
        int capacidad = cap[e];
        int flujoEnviado = flow[e];
	SI EL FLUJO ES NEGATIVO ES ARISTA RESIDUAL
	CUIDADO CON EL VECINO S y T
    }
*/

int main() {
    int n, e, u, v, c;
    cin >> n >> e;
    init(1, n, n);
    for(int i = 1; i <= e; ++i){
        cin >> u >> v >> c;
        ///arista bidireccional
        if(u != v)  add(u, v, c);
        if(u != v)  add(v, u, c);
    }
    cout << dinitz() << "\n";
    return 0;
}
