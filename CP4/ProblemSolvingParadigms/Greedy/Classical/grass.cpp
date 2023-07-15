#include <bits/stdc++.h>

using namespace std;
const double EPS = 1e-9;
pair<double, double> sprinkler[10000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, l, w, x, r;
    auto cmp = [](pair<double, double>& p1, pair<double, double>& p2) {
        if (fabs(p1.first - p2.first) < EPS) return p1.second > p2.second;
        else return p1.first < p2.first;
    };
    while (cin >> n >> l >> w) {
        for (int i = 0; i < n; i++) {
            cin >> x >> r;
            if (2 * r >= w) {
                double dx = sqrt(r * r - (w / 2.0) * (w / 2.0));
                sprinkler[i] = make_pair(x - dx, x + dx);
            } else {
                sprinkler[i] = make_pair(x, x);
            }
        }
        sort(sprinkler, sprinkler + n, cmp);
        bool possible = true;
        double covered = 0;
        int ans = 0;
        for (int i = 0; (i < n) && possible; i++) {
            if (covered > l) break;
            if (sprinkler[i].second < covered + EPS) continue;
            if (sprinkler[i].first < covered + EPS) {
                double max_r = sprinkler[i].second;
                int max_id = i;
                for (int j = i + 1; (j < n) && (sprinkler[j].first < covered + EPS); j++) {
                    if (sprinkler[j].second > max_r) {
                        max_r = sprinkler[j].second;
                        max_id = j;
                    }
                }
                ans++;
                covered = max_r;
                i = max_id;
            } else possible = false;
        }
        if (!possible || (covered < l)) cout << -1;
        else cout << ans;
        cout << '\n';
    }
}