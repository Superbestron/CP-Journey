#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, t, sum = 0; cin >> n >> t;
    int arr[n];
    if (t == 1) {
        cout << 7;
    } else if (t == 2) {
        cin >> arr[0] >> arr[1];
        if (arr[0] > arr[1]) cout << "Bigger";
        else if (arr[0] == arr[1]) cout << "Equal";
        else cout << "Smaller";
    } else if (t == 3) {
        cin >> arr[0] >> arr[1] >> arr[2];
        sort(arr, arr + 3);
        cout << arr[1];
    } else if (t == 4) {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            sum += arr[i];
        }
        cout << sum;
    } else if (t == 5) {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            if (arr[i] % 2 == 0) sum += arr[i];
        }
        cout << sum;
    } else if (t == 6) {
        string s;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            s += static_cast<char>(arr[i] % 26 + 'a');
        }
        cout << s;
    } else {
        bool visited[n];
        memset(visited, 0, sizeof visited);
        int idx = 0;
        for (int i = 0; i < n; i++) cin >> arr[i];
        while (true) {
            if (idx < 0 || idx >= n) {
                cout << "Out"; break;
            }
            if (visited[idx]) {
                cout << "Cyclic"; break;
            }
            if (idx == n - 1) {
                cout << "Done"; break;
            }
            visited[idx] = true;
            idx = arr[idx];
        }
    }
}