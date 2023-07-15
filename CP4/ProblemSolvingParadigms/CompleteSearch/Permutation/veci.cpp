#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string str;
    cin >> str;
    int arr[str.size()];
    for (int i = 0; i < str.size(); i++) {
        arr[i] = str[i] - '0';
    }
    bool ans = next_permutation(arr, arr + str.size());
    if (!ans) cout << 0;
    else {
        for (int i = 0; i < str.size(); i++) cout << arr[i];
    }
}
