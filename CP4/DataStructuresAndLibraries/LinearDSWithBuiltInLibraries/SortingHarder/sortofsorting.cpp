#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n = 1;
    cin >> n;
    while (n != 0) {
        string arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        auto comparator = [](auto& s1, auto& s2) {
            if (s1[0] == s2[0]) {
                return s1[1] < s2[1];
            }
            return s1[0] < s2[0];
        };
        stable_sort(arr, arr + n, comparator);
        for (int i = 0; i < n; i++) {
            cout << arr[i] << endl;
        }
        cout << endl;
        cin >> n;
    }
}
