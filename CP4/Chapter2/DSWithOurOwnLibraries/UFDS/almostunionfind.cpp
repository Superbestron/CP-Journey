#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

// Key idea here is to use a temp parent array to reduce the number of changes
// made to the original set A when moving i from set A to set B

class UnionFind {                                // OOP style
private:
    vi p, temp_p, rank, setSize;                           // vi p is the key part
    vector<long long> sum;
    int numSets;
public:
    explicit UnionFind(int N) {
        p.assign(N, 0);
        temp_p.assign(N, 0);
        sum.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            p[i] = i;
            temp_p[i] = i;
            sum[i] = i;
        }
        rank.assign(N, 0);                           // optional speedup
        setSize.assign(N, 1);                        // optional feature
        numSets = N;                                 // optional feature
    }

    int findSet(int i) {
        int parent = temp_p[i];
        while (parent != p[parent]) parent = p[parent];
        temp_p[i] = parent;
        return parent;
    }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    [[nodiscard]] int numDisjointSets() const { return numSets; }      // optional
    int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;                 // i and j are in same set
        int x = findSet(i), y = findSet(j);          // find both rep items
        if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
        p[x] = y;
        temp_p[i] = y;
        if (rank[x] == rank[y]) ++rank[y];           // optional speedup
        setSize[y] += setSize[x];                    // combine set sizes at y
        sum[y] += sum[x];
        --numSets;                                   // a union reduces numSets
    }

    void move(int i, int j) {
        int old_parent = findSet(i);
        int new_parent = findSet(j);
        if (old_parent == new_parent) return;
        setSize[new_parent]++;
        setSize[old_parent]--;
        sum[new_parent] += i;
        sum[old_parent] -= i;
        temp_p[i] = new_parent;
    }

    void answer(int i) {
        cout << sizeOfSet(i) << ' ' << sum[findSet(i)] << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, op, p, q;
    while (cin >> n >> m) {
        UnionFind ufds(n + 1);
        while (m--) {
            cin >> op;
            if (op == 1) {
                cin >> p >> q;
                ufds.unionSet(p, q);
            } else if (op == 2) {
                cin >> p >> q;
                ufds.move(p, q);
            } else {
                cin >> p;
                ufds.answer(p);
            }
        }
    }
}
