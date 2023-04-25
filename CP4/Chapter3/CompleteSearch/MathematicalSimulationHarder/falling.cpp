#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int D; cin >> D;
    int start = floor(sqrt(D));
    if (start * start == D) {
        cout << 0 << ' ' << start; return 0;
    }
    while (start > 0) {
        if (D % start == 0) {
            int temp = start + D / start;
            if (temp % 2 == 0) {
                int n2 =  temp / 2;
                int n1 = n2 - start;
                cout << n1 << ' ' << n2;
                return 0;
            }
        }
        start--;
    }
    cout << "impossible";
}