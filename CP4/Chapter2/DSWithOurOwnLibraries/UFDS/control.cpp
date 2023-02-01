#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UnionFind {                                // OOP style
private:
    vi p, rank, setSize;                           // vi p is the key part
    int numSets;
public:
    explicit UnionFind(int N) {
        p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);                           // optional speedup
        setSize.assign(N, 1);                        // optional feature
        numSets = N;                                 // optional feature
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    [[nodiscard]] int numDisjointSets() const { return numSets; }      // optional
    int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;                 // i and j are in same set
        int x = findSet(i), y = findSet(j);          // find both rep items
        if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
        p[x] = y;                                    // set x under y
        if (rank[x] == rank[y]) ++rank[y];           // optional speedup
        setSize[y] += setSize[x];                    // combine set sizes at y
        --numSets;                                   // a union reduces numSets
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, ans = 0; cin >> N;
    UnionFind ufds(500001);
    while (N--) {
        cin >> M;
        int total_size = 0;
        vector<int> ids(M);
        unordered_set<int> s;
        for (int i = 0; i < M; i++) {
            cin >> ids[i];
            int parent = ufds.findSet(ids[i]);
            s.insert(parent);
        }
        for (int i : s) total_size += ufds.sizeOfSet(i);
        if (total_size == M) {
            ans++;
            for (int i = 1; i < M; i++) ufds.unionSet(ids[0], ids[i]);
        }
    }
    cout << ans;
}
