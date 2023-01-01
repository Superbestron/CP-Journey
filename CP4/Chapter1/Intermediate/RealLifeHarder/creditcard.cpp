#include <iostream>
#include <cmath>

using namespace std;

double eps = 1e-3;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    double r, b, m;
    while (t--) {
        int months = 0;
        cin >> r >> b >> m;
        r /= 100;
        while (b >= eps && months < 1200) {
            double interest = round(b * r * 100) / 100 ;
            b += interest;
            // this is crucial in preventing precision errors
            // b will always be 2dp
            b = round(b * 100) / 100;
            b -= m;
            months++;
        }
        if (b >= eps) cout << "impossible" << endl;
        else cout << months << endl;
    }
}
