#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    int arr[N];
    long long ans = 0;
    for (int i = 0; i < N; i++) cin >> arr[i];
    for (int i = N - 2; i >= 0; i--) {
        if (arr[i] >= arr[i + 1]) {
            if (arr[i + 1] == 0) {
                cout << 1; return 0;
            }
            ans += arr[i] - arr[i + 1] + 1;
            arr[i] = arr[i + 1] - 1;
        }
    }
    cout << ans;
}