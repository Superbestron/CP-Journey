#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UnionFind {                                // OOP style
private:
    vi p, rank, setSize, used;                           // vi p is the key part
    int numSets;
public:
    explicit UnionFind(int N) {
        p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);                           // optional speedup
        setSize.assign(N, 1);                        // optional feature
        numSets = N;                                 // optional feature
        used.assign(N, 0);
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
        used[y] += used[x];
        --numSets;                                   // a union reduces numSets
    }

    void increment(int i) {
        int parent = findSet(i);
        if (used[parent] < sizeOfSet(i)) {
            cout << "LADICA\n";
            used[parent]++;
        }
        else cout << "SMECE\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, L, A, B; cin >> N >> L;
    UnionFind ufds(300001);
    while (N--) {
        cin >> A >> B;
        ufds.unionSet(A, B);
        ufds.increment(A);
    }
}
