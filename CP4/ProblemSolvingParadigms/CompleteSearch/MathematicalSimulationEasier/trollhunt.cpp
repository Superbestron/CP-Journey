#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int b, k, g; cin >> b >> k >> g;
    cout << ceil((b - 1) * 1.0 / (k / g));
}