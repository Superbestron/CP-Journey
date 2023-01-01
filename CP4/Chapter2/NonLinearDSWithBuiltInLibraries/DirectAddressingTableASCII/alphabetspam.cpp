#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int arr[4]; memset(arr, 0, sizeof arr);
    string s; cin >> s;
    for (char c : s) {
        if (islower(c)) arr[1]++;
        else if (isupper(c)) arr[2]++;
        else if (c == '_') arr[0]++;
        else arr[3]++;
    }
    for (int i : arr) cout << setprecision(6) << static_cast<double>(i) / s.size() << endl;
}