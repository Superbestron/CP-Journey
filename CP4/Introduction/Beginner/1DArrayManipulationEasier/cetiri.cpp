#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int arr[3], diff1, diff2;
    cin >> arr[0] >> arr[1] >> arr[2];
    sort(arr, arr + 3);
    diff1 = arr[1] - arr[0];
    diff2 = arr[2] - arr[1];
    if (diff1 == diff2) cout << arr[0] - diff1;
    else if (diff1 > diff2) cout << arr[0] + diff1/2;
    else cout << arr[1] + diff2/2;
}