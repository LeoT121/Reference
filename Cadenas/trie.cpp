const int NMAX = 5e3;
const int WMAX = 1e6;
const int MOD = 1e9 + 7;

int trie[WMAX][26];
int node_count;
bool stop[WMAX];

/** Adds a new word into the trie. */
void insert(string word) {
	// Node 0 has 26 children - a through z.
	int node = 0;
	for (char c : word) {
		// If a node with the current char doesn't exist create one.
		if (trie[node][c - 'a'] == 0) { trie[node][c - 'a'] = ++node_count; }
		// Move down the path in the trie.
		node = trie[node][c - 'a'];
	}
	// Mark the ending node so we know it's a dictionary word
	stop[node] = true;
}

int main() {
	string s;
	int n;
	cin >> s >> n;

	for (int i = 0; i < n; i++) {
		string word;
		cin >> word;
		insert(word);
	}

	// dp[i] = how many ways can s[i..s.size()] be formed?
	vector<int> dp(s.size() + 1);
	dp[s.size()] = 1;
	for (int i = s.size() - 1; i >= 0; i--) {
		int node = 0;

		// Check if the s[i..j] is a word in the dictionary.
		for (int j = i; j < s.size(); j++) {
			// If the char doesn't exist in the trie break.
			if (trie[node][s[j] - 'a'] == 0) { break; }
			// Move to the next node.
			node = trie[node][s[j] - 'a'];

			/*
			 * If stop[node] true then it's the end of a word.
			 * Let's add to dp[i] the number of ways s[j+1...s.size()] can be
			 * formed.
			 */
			if (stop[node]) { dp[i] = (dp[i] + dp[j + 1]) % MOD; }
		}
	}

	cout << dp[0] << endl;
}