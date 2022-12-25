#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int p, a, b, c, d, n;
    double curr, maxi_so_far, maxi = 0;
    cin >> p >> a >> b >> c >> d >> n;
    for (int k = 1; k <= n; k++) {
        curr = static_cast<double>(p) * (sin(a * k + b) + cos(c * k + d) + 2) ;
        maxi_so_far = max(maxi_so_far, curr);
        maxi = max(maxi, maxi_so_far - curr);
    }
    cout << setprecision(12) << maxi;
}