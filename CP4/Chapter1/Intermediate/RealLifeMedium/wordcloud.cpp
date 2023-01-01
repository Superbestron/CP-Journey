#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int cmax;

int P(pair<string, int>& p) {
    return 8 + static_cast<int>(ceil(40.0 * (p.second - 4) / (cmax - 4)));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int w, n, ctr = 1, count; string s;
    while (cin >> w >> n && w != 0 && n != 0) {
        vector<pair<string, int>> v;
        int num = 0, height = 0;
        cmax = 0;
        for (int i = 0; i < n; i++) {
            cin >> s >> count;
            cmax = max(cmax, count);
            v.emplace_back(s, count);
        }
        while (num < n) {
            double curr_width = -10;
            int curr_height = 0;
            while (num < n) {
                int p = P(v[num]);
                int width = static_cast<int>(ceil(9.0 / 16 * v[num].first.size() * p));
                if (curr_width + 10 + width <= w) {
                    curr_width += 10 + width;
                    curr_height = max(curr_height, p);
                } else break;
                num++;
            }
            height += curr_height;
        }
        cout << "CLOUD " << ctr++ << ": " <<  height << endl;
    }
}