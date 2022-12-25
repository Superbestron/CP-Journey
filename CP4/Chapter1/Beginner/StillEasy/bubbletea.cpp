#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int i, j, n, m, k, idx, money, ans = 1000; cin >> n;
    int arr[n];
    for (i = 0; i < n; i++) cin >> arr[i];
    cin >> m;
    int toppings[m];
    for (i = 0; i < m; i++) cin >> toppings[i];
    for (i = 0; i < n; i++) {
        cin >> k;
        int cheapest = 1000;
        for (j = 0; j < k; j++) {
            cin >> idx;
            cheapest = min(cheapest, toppings[idx - 1]);
        }
        ans = min(ans, cheapest + arr[i]);
    }
    cin >> money;
    int students = money / ans - 1;
    cout << (students < 0 ? 0 : students);
}