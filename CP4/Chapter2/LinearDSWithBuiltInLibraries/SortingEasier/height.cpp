#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int p, c, ans, ctr, insert;
    cin >> p;
    int arr[20];
    while (p-- > 0) {
        fill(arr, arr + 20, 0);
        ans = 0;
        cin >> ctr;
        for (int i = 0; i < 20; i++) {
            cin >> c;
            for (int j = 0; j < i; j++) {
                if (arr[j] > c) {
                    // shift back
                    for (int k = i - 1; k >= j; k--) {
                        arr[k + 1] = arr[k];
                        ans++;
                    }
                    insert = j;
                    break;
                }
            }
            arr[insert] = c;
        }
        cout << ctr << ' ' << ans << endl;
    }
}
