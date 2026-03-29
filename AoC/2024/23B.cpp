#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int, int> iiii;

// Abridged problem statement: Find the largest clique in a graph. This is a well-known NP-hard problem, so don't bother
// finding a polynomial time solution to this. Just as you have realised for AoC style inputs, they are usually small
// enough such that a brute-force exponential solution is accepted. The challenge is to design the brute-force
// algorithm. One way is try to consider each node as part of the clique, and build the largest clique from there. Take
// the maximum clique size over all possible nodes.

void backtrack() {

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ans = 0;
    string s;
    unordered_map<string, unordered_set<string>> AL;
    unordered_set < string > nodes;
    while (cin >> s) {
        vector<string> vec = split(s, '-');
        const string &u = vec[0];
        const string &v = vec[1];
        AL[u].insert(v);
        AL[v].insert(u);
        nodes.insert(u);
        nodes.insert(v);
    }
    for (auto &u : nodes) {
        // try each node to be in the clique
        unordered_set < string > &others = AL[u];
        unordered_set < string > clique = others;
        for (auto &first : others) {
            for (auto &second : others) {
                if (first == second) continue;
                if (!AL[first].contains(second)) {
                    clique.erase(first);
                    clique.erase(second);
                }
            }
        }
        cout << clique.size() << endl;
        ans = max(ans, static_cast<int>(clique.size()) + 1);
    }
    cout << ans << '\n';
}
