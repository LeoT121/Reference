vector<vi> tree;
vector<int> subtree_size;
vector<bool> is_removed;
///En ancestors tenemos los ancestros del
///centroid tree
vector<vii> ancestors;

int get_subtree_size(int u, int p = -1) {
	subtree_size[u] = 1;
	for (int & v : tree[u]) {
		if (v == p || is_removed[v]) continue;
		subtree_size[u] += get_subtree_size(v, u);
	}
	return subtree_size[u];
}

int get_centroid(int u, int tree_size, int p = -1) {
	for (int & v : tree[u]) {
		if (v == p || is_removed[v]) continue;
		if (subtree_size[v] * 2 > tree_size)
			return get_centroid(v, tree_size, u);
	}
	return u;
}

/**
 * Calculate the distance between current `node` and the `centroid` it belongs
 * to. The distances between a node and all its centroid ancestors are stored
 * in the vector `ancestors`.
 * @param cur_dist the distance between `node` and `centroid`
 */
void get_dists(int u, int centroid, int p = -1, int dist = 1) {
	for (int & v : tree[u]) {
		if (v == p || is_removed[v]) continue;
		get_dists(v, centroid, u, dist + 1);
	}
	ancestors[u].push_back({centroid, dist});
}

void build_centroid_decomp(int u = 0) {
	int centroid = get_centroid(u, get_subtree_size(u));

	/*
	 * For all nodes in the subtree rooted at `centroid`, calculate their
	 * distances to the centroid
	 */
	for (int & v : tree[centroid]) {
		if (is_removed[v]) continue;
		get_dists(v, centroid, centroid);
	}

	is_removed[centroid] = 1;
	for (int & v : tree[centroid]) {
		if (is_removed[v]) continue;
		// build the centroid decomposition for all child components
		build_centroid_decomp(v);
	}
}
