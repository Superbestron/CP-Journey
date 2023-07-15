#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ost;

struct cmp {
    bool operator() (auto& lhs, auto& rhs) const {
        return lhs.second < rhs.second;
    }
};

// pair is [order, identifier]

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, m, r, movie; cin >> t;
    while (t--) {
        ost tree;
        set<pair<int, int>, cmp> s;
        cin >> m >> r;
        for (int i = 1; i <= m; i++) {
            pair<int, int> temp = {1, i};
            tree.insert(temp);
            s.insert(temp);
        }
        for (int i = 0; i < r; i++) {
            cin >> movie;
            auto p = *s.find({0, movie});
            s.erase(p);
            tree.erase(p);
            cout << tree.order_of_key(p) << ' ';
            pair<int, int> temp = make_pair(-i, p.second);
            s.insert(temp);
            tree.insert(temp);
        }
        cout << '\n';
    }
}
