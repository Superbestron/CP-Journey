#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

void up(string& output, int& num) {
    output += '^';
    num += 3;
}

void down(string& output, int& num) {
    output += 'v';
    num -= 3;
}
void left(string& output, int& num) {
    output += '<';
    num--;
}
void right(string& output, int& num) {
    output += '>';
    num++;
}

vector<vector<vi>> memo;

int dp(int layer, int src, int dest) {
    int&ans = memo[layer][src][dest];
    if (ans != -1) return ans;
    string output;
    if (layer < 3) {
        // 029A
        int src_num = src;
        int dest_num = dest;
        int prev = 5; // A
        int cnt1 = 0;
        while (src_num != dest_num) {
            int src_row = src_num / 3;
            int dest_row = dest_num / 3;
            if (src_row > dest_row) {
                down(output, src_num);
                cnt1 += dp(layer + 1, prev, 1);
                prev = 1;
            } else if (src_row < dest_row) {
                up(output, src_num);
                cnt1 += dp(layer + 1, prev, 4);
                prev = 4;
            } else {
                if (src_num < dest_num) {
                    right(output, src_num);
                    cnt1 += dp(layer + 1, prev, 2);
                    prev = 2;
                } else {
                    left(output, src_num);
                    cnt1 += dp(layer + 1, prev, 0);
                    prev = 0;
                }
            }
        }
        src_num = src;
        dest_num = dest;
        prev = 5; // A
        int cnt2 = 0;
        while (src_num != dest_num) {
            int src_col = src_num % 3;
            int dest_col = dest_num % 3;
            if (src_col > dest_col) {
                left(output, src_num);
                cnt2 += dp(layer + 1, prev, 0);
                prev = 0;
            } else if (src_col < dest_col) {
                right(output, src_num);
                cnt2 += dp(layer + 1, prev, 2);
                prev = 2;
            } else {
                if (src_num < dest_num) {
                    up(output, src_num);
                    cnt2 += dp(layer + 1, prev, 4);
                    prev = 4;
                } else {
                    down(output, src_num);
                    cnt2 += dp(layer + 1, prev, 1);
                    prev = 1;
                }
            }
        }
//        int cnt = min(cnt1, cnt2);
            int cnt = cnt2;
        cnt += dp(layer + 1, prev, 5);
        return ans = cnt;
    } else {
        return 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int ans = 0;
    while (cin >> s) {
        memo.assign(25, vector<vi>(12, vi(12, -1)));
        int numeric = stoi(s.substr(0, 3)), cnt = 0;
        string input = 'A' + s;
        for (int i = 0; i < input.size() - 1; i++) {
            char src = input[i], dest = input[i + 1];
            if (src == '0') src = '2';
            else if (src == 'A') src = '3';
            else src += 3;
            if (dest == '0') dest = '2';
            else if (dest == 'A') dest = '3';
            else dest += 3;
            int src_num = src - '0' - 1;
            int dest_num = dest - '0' - 1;
            cnt += dp(0, src_num, dest_num);
        }
        cout << cnt << '\n';
        ans += cnt * numeric;
    }
    cout << ans << '\n';
}
