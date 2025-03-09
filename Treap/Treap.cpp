///implicit treap
///#pragma GCC optimize("O3")
///#pragma GCC target("tune=native") those can be used to optimize the code



mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
auto randis = uniform_int_distribution<int>(numeric_limits<int>::min(), numeric_limits<int>::max());

struct Node {
	int v;
	int w, s;
	Node *l, *r;
	Node(int c) : v(c), w(randis(rng)), s(1), l(NULL), r(NULL) {}
    ///if you want to do the reverse operations
    ///a trick is multiply -1 the size
    ///instead of add the boolean
} *root;

inline int size(Node *t) { return t ? abs(t->s) : 0;}

void mergenodes(Node *& p, Node *l, Node *r){
    ///merge nodes
    p->s = size(p->l) + size(p->r);
    ///operations to merge the nodes
}

void push(Node *t){
    if(!t) return;
    ///operations for lazy
    ///reverse a treap with the trick
    if(t->s < 0){
        swap(t->l, t->r);
        if(t->l) t->l->s = -t->l->s;
        if(t->r) t->r->s = -t->r->s;
        t->s = - t->s;
    }
}

void update(Node *t){
    if(!t) return;
    ///reset value of the node t
    t->s = 1;
    ///whatever operations to reset value
    if(t->l) mergenodes(t, t->l, t);
    if(t->r) mergenodes(t, t, t->r);
}

void split(Node *t, Node *&l, Node *&r, int v) {
	if (!t) {
		l = r = NULL;
		return;
	}
    push(t);
	if (size(t->l) < v) {
		split(t->r, t->r, r, v - size(t->l) - 1);
		l = t;
	} else {
		split(t->l, l, t->l, v);
		r = t;
	}
    update(t);
}

void merge(Node *&t, Node *l, Node *r) {
	push(l), push(r);
	if(!l || !r){
        t = (l) ? l : r;
        return;
	}
	if (l->w < r->w) {
		merge(l->r, l->r, r);
		t = l;
	} else {
		merge(r->l, l, r->l);
		t = r;
	}
	update(t);
}

///treap

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
auto randis = uniform_int_distribution<int>(numeric_limits<int>::min(), numeric_limits<int>::max());


struct Node {
	// the value and priority of the node respectively
	int v, y, s;
	// pointer to left and right child (NULL means no child)
	Node *l, *r;
	Node(int v) : v(v), y(randis(rng)), l(NULL), r(NULL), s(1){};
} *root;

inline int size(Node * t){return t ? abs(t->s) : 0;}

void push(Node * t){
    if(!t) return;
    ///operations for lazy
    ///maybe you could use the reverse sequence idk
    ///so this is the trick for the reverse
    if(t->s < 0){
        swap(t->l, t->r);
        if(t->l) t->l->s = -t->l->s;
        if(t->r) t->r->s = -t->r->s;
        t->s = - t->s;
    }
}

void mergenodes(Node *& p, Node * l, Node * r){
    p->s = size(l) + size(r);
    ///operations to merge nodes
}

void update(Node * t){
    if(!t) return;
    t->s = 1;
    ///reset values of t as if only it doesnt have childs
    if(t->l) mergenodes(t, t->l, t);
    if(t->r) mergenodes(t, t, t->r);

}

void split(Node *t, Node *&l, Node *&r, int x) {
	if (!t) {
		l = r = NULL;
		return;
	}
	push(t);
	if (t->v <= x) {
		split(t->r, t->r, r, x);
		l = t;
	} else {
		split(t->l, l, t->l, x);
		r = t;
	}
	update(t);
}

void merge(Node *&t, Node *l, Node *r) {
    push(l), push(r);
	if (!l || !r) {
		t = l ? l : r;
		return;
	}

	if (l->y > r->y) {
		merge(l->r, l->r, r);
		t = l;
	} else {
		merge(r->l, l, r->l);
		t = r;
	}
	update(t);
}


Node *unite(Node *l, Node *r){
    push(l), push(r);
    if(!l || !r) return l ? l : r;
    if(l->y < r->y) swap(l, r);
    Node * lt, *rt;
    split(r, lt, rt, l->v);
    l->l = unite(l->l, lt);
    l->r = unite(l->r, rt);
    update(l);
    return l;
}


///treap with parent
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
auto randis = uniform_int_distribution<int>(numeric_limits<int>::min(), numeric_limits<int>::max());

struct Node {
	int v;
	int w, s;
	Node *l, *r, *p;
	Node(int c) : v(c), w(randis(rng)), s(1), l(NULL), r(NULL), p(NULL) {}
} *root;

inline int size(Node *t) { return t ? abs(t->s) : 0;}

void push(Node *t){
    if(!t) return;
    ///operation for lazy
    ///trick to reverse the sequence
    if(t->s < 0){
        swap(t->l, t->r);
        if(t->l) t->l->s = - t->l->s;
        if(t->r) t->r->s = - t->r->s;
        t->s = - t->s;
    }
}

void mergenodes(Node *&p, Node *l, Node * r){
    p->s = size(p->l) + size(p->r);
    ///operations to merge nodes l and r to p
}

void update(Node * t){
    if(!t) return;
    t->s = 1;
    ///initialize with only the node of t
    push(t->l), push(t->r);
    if(t->l){
        t->l->p = t;
        ///operation to merge nodes left and parent
        mergenodes(t, t->l, t);
    }
    if(t->r){
        t->r->p = t;
        ///operation to merge nodes parent and right
        mergenodes(t, t, t->r);
    }

}

void split(Node *t, Node *&l, Node *&r, int v) {
	if (!t) {
		l = r = NULL;
		return;
	}
	push(t);
    if(t->l) t->l->p = NULL;
    if(t->r) t->r->p = NULL;
	if (size(t->l) < v) {
		split(t->r, t->r, r, v - size(t->l) - 1);
		l = t;
	} else {
		split(t->l, l, t->l, v);
		r = t;
	}
	update(t);
}

void merge(Node *&t, Node *l, Node *r) {
	push(l), push(r);
	if (!l || !r) {
		t = l ? l : r;
		return;
	}
	if (l->w < r->w) {
		merge(l->r, l->r, r);
		t = l;
	} else {
		merge(r->l, l, r->l);
		t = r;
	}
	update(t);
}

///return the root and the index of the node
pair<Node *, int> find_root(Node * t){
    int izq = size(t->l);
    Node *ant;
    while(t->p){
        ant = t;
        t = t->p;
        if(ant == t->r) izq += size(t->l) + 1;
    }
    return {t, izq};
}
