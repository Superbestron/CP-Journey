#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, idx = 0, val, start, end; cin >> n;
    bool arr[1000];
    memset(arr, false, sizeof arr);
    while (n--) {
        cin >> val;
        arr[val - 1] = true;
    }

    while (idx < 1000) {
        if (arr[idx]) {
            start = idx + 1;
            while (idx + 1 < 1000 && arr[idx + 1]) idx++;
            end = idx + 1;
            if (start != end) {
                if (start == end - 1) cout << start << ' ' << end << ' ';
                else cout << start << '-' << end << ' ';
            }
            else cout << start << ' ';
        }
        idx++;
    }
    if (end < start) cout << start << '-' << 1000;
}