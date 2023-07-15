#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
int n;
int arr[30];
pair<long double, long double> dimensions[30]; // length, height

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i < n; i++) cin >> arr[i];
    long double length = pow(2, -1.25), height = pow(2, -0.75);
    int need = 2;
    for (int i = 1; i < 30; i++) {
        dimensions[i] = make_pair(length, height);
        long double temp = height;
        height = length;
        length = temp / 2;
    }
    long double ans = dimensions[1].second;
    for (int i = 1; i < n; i++) {
        need -= arr[i];
        // tape needed to make "need" amount of paper
        if (need <= 0) {
            cout << fixed << setprecision(5) << ans;
            return 0;
        } else {
            if (i == n - 1) {
                cout << "impossible";
                return 0;
            } else {
                ans += need * dimensions[i + 1].second; // last paper don't need
            }
        }
        need *= 2;
    }
}