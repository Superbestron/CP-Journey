#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

class Score {
public:
    int team;
    int solved = 0;
    int penalty = 0;
};

bool operator< (const Score& lhs, const Score& rhs) {
    if (lhs.solved == rhs.solved) {
        if (lhs.penalty == rhs.penalty) {
            return lhs.team < rhs.team;
        }
        return lhs.penalty < rhs.penalty;
    }
    return lhs.solved > rhs.solved;
}

typedef tree<Score, null_type, less<Score>, rb_tree_tag, tree_order_statistics_node_update> ost;
unordered_map<int, Score> tmp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string symbol;
    int n, m, t, p; cin >> n >> m;
    ost tree;
    for (int i = 1; i <= n; i++) {
        Score score;
        score.team = i;
        tmp[i] = score;
        tree.insert(score);
    }
    while (m--) {
        cin >> t >> p;
        Score& score = tmp[t];
        tree.erase(score);
        score.solved++; score.penalty += p;
        tree.insert(score);
        cout << tree.order_of_key(tmp[1]) + 1 << '\n';
    }
}
