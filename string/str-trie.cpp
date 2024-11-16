struct str_trie {
    struct node {
        vector<int> nxt;
        int end;

        node(int n) {
            end = 0;
            nxt.assign(n, -1);
        }
    };

    int sz;
    vector<node> b;

    str_trie(int maxb = 0) {
        b.assign(maxb + 5, node(26));
        sz = 0;
    }

    void add(string s) {
        int u = 0;
        for (char c : s) {
            if (b[u].nxt[c - 'a'] == -1) b[u].nxt[c - 'a'] = ++sz;
            u = b[u].nxt[c - 'a'];
        }
        b[u].end++;
    }
};