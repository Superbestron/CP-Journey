#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, prev, curr;
    while (cin >> n) {
        cin >> prev;
        bool arr[n];
        bool isJolly = true;
        fill(arr, arr + n, false);
        for (int i = 1; i < n; i++) {
            cin >> curr;
            int temp = abs(curr - prev);
            if (temp > 0 && temp < n)
                arr[temp] = true;
            prev = curr;
        }
        for (int i = 1; i < n; i++) {
            if (!arr[i]) {
                isJolly = false;
            }
        }
        if (isJolly)
            cout << "Jolly" << endl;
        else
            cout << "Not Jolly" << endl;
    }
}