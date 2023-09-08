#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b;
    cin >> n >> m;
    unordered_set<int> left, right;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        if (a < b) left.insert(i);
        else (right.insert(i));
    }
    // left or right will never be more than half
    if (left.size() < right.size()) {
        cout << left.size() << '\n';
        for (int i : left) cout << i << '\n';
    } else {
        cout << right.size() << '\n';
        for (int i : right) cout << i << '\n';
    }
}

