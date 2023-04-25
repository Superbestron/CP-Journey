#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int T, M, R, N, pos;
    cin >> T;
    auto cmp = [](pair<int, int>& p1, pair<int, int>& p2) {
        if (p1.first == p2.first) return p1.second > p2.second;
        return p1.first < p2.first;
    };
    for (int t = 1; t <= T; t++) {
        cin >> M >> R >> N;
        pair<int, int> lights[N];
        for (int i = 0; i < N; i++) {
            cin >> pos;
            lights[i] = make_pair(pos - R, pos + R);
        }
        sort(lights, lights + N, cmp);
        bool possible = true;
        int covered = 0, ans = 0;
        for (int i = 0; (i < N) && possible; i++) {
            if (covered >= M) break;
            if (lights[i].second <= covered) continue;
            if (lights[i].first <= covered) {
                int max_r = lights[i].second;
                int max_id = i;
                for (int j = i + 1; (j < N) && lights[j].first <= covered; j++) {
                    if (lights[j].second > max_r) {
                        max_r = lights[j].second;
                        max_id = j;
                    }
                }
                ans++;
                covered = max_r;
                i = max_id;
            } else possible = false;
        }
        cout << "Case #" << t << ": " << (possible && covered >= M ? to_string(ans) : "IMPOSSIBLE") << '\n';
    }
}

