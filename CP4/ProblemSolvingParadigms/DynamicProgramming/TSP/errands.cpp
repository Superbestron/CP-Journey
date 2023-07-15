#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))

using namespace std;

const int MAX_N = 12;
const double EPS = 1e-5;

int t, n, child[MAX_N];
double x, y, memo[MAX_N][1 << (MAX_N - 1)], dist[MAX_N][MAX_N];
unordered_map<string, pair<double, double>> vertices;
vector<string> locations;

vector<string> split(string s, char delimiter) {
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

void reconstruct(int u, int mask) {
    if (mask == 0) return;
    int m = mask;
    while (m) {                                    // up to O(n)
        int two_pow_v = LSOne(m);                    // but this is fast
        int v = __builtin_ctz(two_pow_v) + 1;          // offset v by +1
        // be careful with precision errors
        if (abs(memo[u][mask] - dist[u][v] - memo[v][mask ^ two_pow_v]) < EPS) {
            cout << locations[v] << ' ';
            reconstruct(v, mask ^ two_pow_v);
            break;
        }
        m -= two_pow_v;
    }
}

double dp(int u, int mask) {                        // mask = free coordinates
    double &ans = memo[u][mask];
    if (ans != -1) return ans;                     // computed before
    if (mask == 0) return ans = dist[u][n - 1];              // close the loop
    ans = 2000000000;
    int m = mask;
    while (m) {                                    // up to O(n)
        int two_pow_v = LSOne(m);                    // but this is fast
        int v = __builtin_ctz(two_pow_v) + 1;          // offset v by +1
        ans = min(ans, dist[u][v] + dp(v, mask ^ two_pow_v));
        m -= two_pow_v;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    string location, tc;
    for (int j = 0; j < n; j++) {
        cin >> location >> x >> y;
        vertices[location].first = x;
        vertices[location].second = y;
    }
    cin.ignore();
    while (getline(cin, tc)) {
        fill(memo[0], memo[0] + MAX_N * (1 << (MAX_N - 1)), -1);
        memset(child, -1, sizeof child);
        locations = split(tc, ' ');
        locations.insert(locations.begin(), "work");
        locations.emplace_back("home");
        n = locations.size();
        for (int i = 0; i < n; i++)                  // build distance table
            for (int j = i; j < n; j++) {
                dist[i][j] = dist[j][i] = sqrt(pow( vertices[locations[i]].first - vertices[locations[j]].first, 2)
                                               + pow(vertices[locations[i]].second - vertices[locations[j]].second, 2));
            }
        dp(0, (1 << (n - 2)) - 1);
        reconstruct(0, (1 << (n - 2)) - 1);
        cout << '\n';
    }
}
