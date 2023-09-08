#include <bits/stdc++.h>
using namespace std;

int N, OK;
vector<int> masks;

int backtrack(int u, int mask) {
    if (u == N) return mask == OK;
    return backtrack(u + 1, mask) + backtrack(u + 1, mask | masks[u]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    string s;
    OK = (1 << 26) - 1;
    for (int i = 0; i < N; i++) {
        int mask = 0;
        cin >> s;
        for (char c : s) {
            mask |= (1 << (c - 'a'));
        }
        masks.push_back(mask);
    }
    cout << backtrack(0, 0);
}

