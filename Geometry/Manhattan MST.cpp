///this returns the edges that potentially can be mst edges
///at most there are 8*n edges that need to be considered

struct pnt{
    int x, y, id;
    const bool operator < (const pnt & a) const {
        return ii(y, x) < ii(a.y, a.x);
    }
};

ii st[4 * MX];

void build(int node, int l, int r){
    st[node] = ii(1e9, -1);
    if(l == r) return;
    int m = (l + r) / 2;
    build(node * 2 + 1, l, m);
    build(node * 2 + 2, m + 1, r);
}

ii query(int node, int l, int r, int a, int b){
    if(l > b || r < a) return ii(1e9, -1);
    if(a <= l && r <= b) return st[node];
    int m = (l + r) / 2;
    return min(query(node * 2 + 1, l, m, a, b), query(node * 2 + 2, m + 1, r, a, b));
}

void update(int node, int l, int r, int p, ii v){
    if(l > p || r < p) return;
    if(l == r){
        st[node] = min(st[node], v);
        return;
    }
    int m = (l + r) / 2;
    update(node * 2 + 1, l, m, p, v);
    update(node * 2 + 2, m + 1, r, p, v);
    st[node] = min(st[node * 2 + 1], st[node * 2 + 2]);
}

vector<pnt> points, aux;
int n;

struct edge{
    int u, v, x;
    const bool operator < (const edge & a) const {
        return x < a.x;
    }
};

vector<edge> e;


void sweep(){
    vi v(n);
    for0(i, n) v[i] = points[i].x - points[i].y;
    sort(all(v));
    v.resize(unique(bg(v), v.end()) - bg(v));
    build(0, 0, n - 1);
    far0(i, n){
        int l = lb(bg(v), v.end(), points[i].x - points[i].y) - bg(v);
        ii p = query(0, 0, n - 1, l, n - 1);
        if(p.se != -1)
            e.pb({points[i].id, p.se, p.fi - points[i].x - points[i].y});
        update(0, 0, n - 1, l, ii(points[i].x + points[i].y, points[i].id));
    }

}

void solve(){
    cin >> n;
    points.resize(n);
    aux.resize(n);
    for0(i, n){
        cin >> points[i].x >> points[i].y;
        points[i].id = i;
    }
    for0(j, 8){
        for0(i, n) aux[i] = points[i];
        for0(i, n){
            if(j & 1) points[i].x *= -1;
            if(j & 2) points[i].y *= -1;
            if(j & 4) swap(points[i].x, points[i].y);
        }
        sort(all(points));
        sweep();
        for0(i, n) points[i] = aux[i];
    }
}
