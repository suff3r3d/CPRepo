struct bin_trie {
    struct node {
		int nxt[2];
        int cnt;
        node() {
            cnt = 0;
			nxt[0] = nxt[1] = -1;
        }
    };
	int maxbit = 40; // change this if ai <= 10^18
    int sz;
    vector<node> b;
    bin_trie() {
        b.assign(1, node());
        sz = 0;
    }
    void add(long long s) {
		int u = 0;
		for (int k = maxbit; k >= 0; k--) {
			bool id = (1ll << k) & s;
			if (b[u].nxt[id] == -1) {
				b[u].nxt[id] = ++sz;
				b.push_back(node());
			}
			u = b[u].nxt[id];
			b[u].cnt++;
		}
    }
};