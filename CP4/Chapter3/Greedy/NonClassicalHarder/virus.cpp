#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string before, after;
    cin >> before >> after;
    int low = min(before.size(), after.size());
    for (int i = 0; i < min(before.size(), after.size()); i++) {
        if (before[i] != after[i]) {
            low = i;
            break;
        }
    }
    before = before.substr(low);
    after = after.substr(low);
    reverse(before.begin(), before.end());
    reverse(after.begin(), after.end());
    low = min(before.size(), after.size());
    for (int i = 0; i < min(before.size(), after.size()); i++) {
        if (before[i] != after[i]) {
            low = i;
            break;
        }
    }
    cout << after.size() - low;
}
