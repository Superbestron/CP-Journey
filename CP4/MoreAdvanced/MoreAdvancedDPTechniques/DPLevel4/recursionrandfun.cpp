#include <bits/stdc++.h>
using namespace std;

int a, b, c, num, k, t = 0;
bool memo[10001][101];
int last_visit[10001][101]; // to avoid memo table reinitialisation

bool dp(int input, int output) {
    if (input <= 0) return output == 1;
    if (output <= 0) return false;
    if (last_visit[output][input] == t) return memo[output][input];
    last_visit[output][input] = t;
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < c; j++) {
            int input_t = input - 1 - j;
            int output_t = output - a - i;
            if (dp(input_t, output_t)) {
                memo[output][input] = true;
                return true;
            }
        }
    }
    memo[output][input] = false;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(last_visit, 0, sizeof last_visit);
    while (cin >> a >> b >> c >> num >> k) {
        t++;
        cout << (dp(num, k) ? "possible\n" : "impossible\n");
    }
}