#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int arr[5];
    for (int & i : arr) {
        cin >> i;
    }
    for (int i = 4; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                for (int k = 0; k < 5; k++) {
                    cout << arr[k] << ' ';
                }
                cout << endl;
            }
        }
    }
}
