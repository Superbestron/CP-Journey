#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 0; i <= 3; i++) {
        for (int a = 1; a <= 20; a++) {
            for (int j = 0; j <= 3; j++) {
                for (int b = 1; b <= 20; b++) {
                    for (int k = 0; k <= 3; k++) {
                        for (int c = 1; c <= 20; c++) {
                            if (a * i + b * j + c * k == n) {
                                if (i == 1) cout << "single " << a << '\n';
                                else if (i == 2) cout << "double " << a << '\n';
                                else if (i == 3) cout << "triple " << a << '\n';
                                if (j == 1) cout << "single " << b << '\n';
                                else if (j == 2) cout << "double " << b << '\n';
                                else if (j == 3) cout << "triple " << b << '\n';
                                if (k == 1) cout << "single " << c << '\n';
                                else if (k == 2) cout << "double " << c << '\n';
                                else if (k == 3) cout << "triple " << c << '\n';
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "impossible";
}
