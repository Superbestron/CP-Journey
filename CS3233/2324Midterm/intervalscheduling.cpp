#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

vector<string> split(string& s, char delimiter) {
    size_t pos;
    string token;
    vector<string> arr;
    if (s.empty()) return arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.emplace_back(token);
        s.erase(0, pos + 1);
    }
    arr.emplace_back(s);
    return arr;
}

void pr(int x) {
    if (x < 10) cout << 0 << x;
    else cout << x;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, mn = 1e9, mx = 0;
    string s;
    cin >> N;
    cin.ignore();
    vii arr;
    for (int i = 0; i < N; i++) {
        getline(cin, s);
        vector<string> temp = split(s, '-');
        int time1, time2;
        vector<string> t1 = split(temp[0], ':');
        time1 = stoi(t1[0]) * 60 + stoi(t1[1]) - 960;
        vector<string> t2 = split(temp[1], ':');
        time2 = stoi(t2[0]) * 60 + stoi(t2[1]) - 960;
        arr.emplace_back(time1, time2);
        mn = min(mn, time2 - time1);
        mx = max(mx, time2 - time1);
    }

    auto can = [&](int x) {
        int lim = arr[0].first;
        for (int i = 0; i < N; i++) {
            auto &[t1, t2] = arr[i];
            int dur = t2 - t1;
            if (lim > t1) {
                return false;
            }
            if (dur >= x) {
                lim = t2;
            } else {
                int start = max(lim, t1 - (x - dur));
                int end = max(start + x, t2);
                lim = end;
            }
        }
        return lim <= arr.back().second;
    };

    int lo = mn, hi = 640;
    while (hi > lo) {
        int mid = lo + (hi - lo + 1) / 2;
        can(mid) ? lo = mid : hi = mid - 1;
    }

    vector<pair<int, int>> ans(N);
    auto can2 = [&](int x) {
        int lim = arr[0].first;
        for (int i = 0; i < N; i++) {
            auto &[t1, t2] = arr[i];
            int dur = t2 - t1;
            if (lim > t1) return false;
            if (dur >= x) {
                ans[i].first = t1;
                ans[i].second = t2;
                lim = t2;
            } else {
                int start = max(lim, t1 - (x - dur));
                int end = max(start + x, t2);
                ans[i].first = start;
                ans[i].second = end;
                lim = end;
            }
        }
        return lim <= arr.back().second;
    };
    can2(lo);
    for (auto &[x, y] : ans) {
        x += 960;
        y += 960;
        pr(x / 60); cout << ':'; pr(x % 60);
        cout << " - ";
        pr(y / 60); cout << ':'; pr(y % 60);
        cout << '\n';
    }
}
