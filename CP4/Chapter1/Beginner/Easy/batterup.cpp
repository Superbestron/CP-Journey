#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, ctr = 0, val, sum = 0; cin >> n;
    while (n--) {
        cin >> val;
        if (val != -1) {
            sum += val;
            ctr++;
        }
    }
    cout << setprecision(10) << static_cast<double>(sum) / ctr;
}