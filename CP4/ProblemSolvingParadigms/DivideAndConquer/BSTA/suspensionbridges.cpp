#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
int d, s;

// a + s = a * cosh(d/2a)
// a(1-cosh(d/2a)) = -s
// a = s/(cosh(d/2a)-1)
bool can(double a) {
    return a + s >= a * cosh(d / (2 * a));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> d >> s;
    double lo = 0, hi = 1000000;
    while (fabs(hi - lo) > EPS) {
        double mid = (lo + hi) / 2;
        can(mid) ? hi = mid : lo = mid;
    }
    cout << fixed << setprecision(5) << 2 * hi * sinh(d / (2 * hi));
}