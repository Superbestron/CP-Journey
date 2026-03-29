#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// This is a very tough question. Firstly, you need to recognise that for every move you make in the ith board, in the
// (i + 1)th board, you will always start and end at 'A'. This information is important, as it ensures that every move
// from x to y in the ith board will always generate the same resulting movement in the (i + 1)th board, which means
// that there is a potential of memoisation. Furthermore, if we visualise the boards as layers, a movement in the ith
// layer will set off a chain reaction of commands in the (i + 1)th, (i + 2)th... layers and so on, which means using
// Dynamic Programming is a suitable algorithm for this question. Secondly, the implementation of movements can be
// tricky, and some insight is needed to simplify it, or else mistakes will be made easily during implementation. The
// trick that I use is to remap the keys on the board as integers, which makes it easier for me to determine a key's
// row and column, by using division and modulo operations respectively. This works regardless it's the initial keypad,
// or the directional keypad. Thirdly, I've no idea why they decided to introduce a random "hole" in the keypads, but my
// guess was to prevent us from making certain movements to complicate our code further. You need to explicitly
// check for that during the DP itself, and consequently my trick of quickly calculating rows and columns in my second
// point is useful, as it allows me to know the src and dest of a movement. There is a follow-up point to this; don't be
// fooled into thinking for example, moving from left to up or moving from up to left to reach a top-left hand position
// will both generate the same output. I made this mistake, and it took me a couple of hours to realise this. The reason
// lies in the fact that a particular path taken in the ith board might result in a different final position in the
// (i + 1)th board, which might lead to a shorter movement for the next movement in the latter. We need to explicitly
// try these 2 different paths and take the minimum in the DP. Finally, given the ith board, src, and dest, we need to
// simulate the entire path, and for each movement, we compute the (i + 1)th board, and don't forget to keep track of
// the current position in the latter board. Remember to always end the path with a visit to 'A'. The same algorithm
// can be used to solve both 21A and 21B.

vector<vector<vll>> memo;

void up(int& num) { num += 3; }

void down(int& num) { num -= 3; }

void left(int& num) { num--; }

void right(int& num) { num++; }

int layers = 26;

ll dp(int layer, const int src, const int dest) {
    ll& ans = memo[layer][src][dest];
    if (ans != -1) return ans;
    if (layer < layers) {
        ans = LONG_LONG_MAX;
        int src_num = src;
        int dest_num = dest;
        if ((layer != 0 || !(dest_num / 3 == 0 && src_num % 3 == 0)) && (layer == 0 || !(src_num % 3 == 0 && dest_num / 3 == 1))) {
            int prev = 5;
            ll cnt = 0;
            while (src_num != dest_num) {
                int src_row = src_num / 3;
                int dest_row = dest_num / 3;
                if (src_row > dest_row) {
                    down(src_num);
                    cnt += dp(layer + 1, prev, 1);
                    prev = 1;
                } else if (src_row < dest_row) {
                    up(src_num);
                    cnt += dp(layer + 1, prev, 4);
                    prev = 4;
                } else {
                    if (src_num < dest_num) {
                        right(src_num);
                        cnt += dp(layer + 1, prev, 2);
                        prev = 2;
                    } else {
                        left(src_num);
                        cnt += dp(layer + 1, prev, 0);
                        prev = 0;
                    }
                }
            }
            cnt += dp(layer + 1, prev, 5);
            ans = min(ans, cnt);
        }

        src_num = src;
        dest_num = dest;
        if ((layer != 0 || !(dest_num % 3 == 0 && src_num / 3 == 0)) && (layer == 0 || !(src_num / 3 == 1 && dest_num % 3 == 0))) {
            ll cnt = 0;
            int prev = 5;
            while (src_num != dest_num) {
                int src_col = src_num % 3;
                int dest_col = dest_num % 3;
                if (src_col > dest_col) {
                    left(src_num);
                    cnt += dp(layer + 1, prev, 0);
                    prev = 0;
                } else if (src_col < dest_col) {
                    right(src_num);
                    cnt += dp(layer + 1, prev, 2);
                    prev = 2;
                } else {
                    if (src_num < dest_num) {
                        up(src_num);
                        cnt += dp(layer + 1, prev, 4);
                        prev = 4;
                    } else {
                        down(src_num);
                        cnt += dp(layer + 1, prev, 1);
                        prev = 1;
                    }
                }
            }
            cnt += dp(layer + 1, prev, 5);
            ans = min(ans, cnt);
        }
        return ans;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    ll ans = 0;
    while (cin >> s) {
        memo.assign(27, vector(12, vll(12, -1)));
        int numeric = stoi(s.substr(0, 3));
        ll cnt = 0;
        string input = 'A' + s;
        string output;
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
        ans += cnt * numeric;
    }
    cout << ans << '\n';
}
