#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, ncs, ne; cin >> n;
    while (n--) {
        cin >> ncs >> ne;
        double sum_cs = 0, sum_e = 0, ans = 0;
        vector<int> cs(ncs), e(ne);
        for (int i = 0; i < ncs; i++) {
            cin >> cs[i];
            sum_cs += cs[i];
        }
        for (int i = 0; i < ne; i++) {
            cin >> e[i];
            sum_e += e[i];
        }
        int avg_cs = ceil(sum_cs / ncs);
        int avg_e = floor(sum_e / ne);
        for (int i : cs) {
            if (i < avg_cs && i > avg_e) ans++;
        }
        cout << ans << endl;
    }
}
