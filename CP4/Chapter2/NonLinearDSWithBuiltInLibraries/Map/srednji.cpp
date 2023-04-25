#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // m's value tracks the number of "numbers" I need in the left portion of the array (before b)
    // to maintain the median
    // positive value x means i has x extra "numbers" on the right portion of the array that are > b
    unordered_map<int, int> m;
    int n, b, pos, ans = 0, sum = 0; cin >> n >> b;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] == b) pos = i;
    }
    map<int, int> s;
    m[0] = 1; // an array of 1 element containing b itself fits the definition above
    for (int i = pos + 1; i < n; i++) {
        if (arr[i] > b) sum++;
        else sum--;
        m[sum]++;
    }
    sum = 0;
    // add 1 * m[0] because they can "exist" with b (without involvement of left portion of array)
    ans += m[0];
    for (int i = pos - 1; i >= 0; i--) {
        if (arr[i] > b) sum++;
        else sum--;
        ans += m[-sum];
    }
    cout << ans;
}
