#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b; cin >> n;
    char c;
    for (int i = 1; i <= n; i++) {
        cin >> a >> a >> c >> b;
        if (a > b) {
            int depth = a / b;
            a %= b;
            b -= a;
            a += b;
            b += a * depth;
        } else if (b == 1) {
            b = a + 1;
            a = 1;
        } else {
            a = b - a;
            swap(a, b);
        }
        cout << i << ' ' <<  a << '/' << b << '\n';
    }
}