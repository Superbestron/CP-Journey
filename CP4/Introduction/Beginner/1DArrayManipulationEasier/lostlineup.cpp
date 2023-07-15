#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, idx; cin >> n; int arr[n];
    arr[0] = 1;
    for (int i = 0; i < n - 1; i++) {
        cin >> idx;
        arr[idx + 1] = i + 2;
    }
    for (int i = 0; i < n; i++) cout << arr[i] << ' ';
}