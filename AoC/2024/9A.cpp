#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Used a "2-pointer" approach where I iterate the vector normally from the left and greedily fill up the answer string
// whenever a number represents a file (even-indexed), and whenever it's odd-indexed, I greedily pop from the vector
// to extract out the number of remaining files I can fit into the space or fit whatever I can from the file that I had
// already popped earlier. This implementation might seem tricky to some, but I find it elegant enough

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vi nums, fin;
    string s;
    int val_left = -1, cnt_left = 0;
    ll ans = 0;
    while (cin >> s) {
        istringstream str(s);
        for (char c : s) nums.push_back(c - '0');
    }
    for (int i = 0; i < nums.size(); i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < nums[i]; j++) {
                fin.push_back(i / 2);
            }
        } else {
            for (int j = 0; j < nums[i]; j++) {
                if (cnt_left == 0) {
                    val_left = (nums.size() - 1) / 2;
                    cnt_left = nums.back(); nums.pop_back();
                    if (!nums.empty()) nums.pop_back();
                }
                fin.push_back(val_left); cnt_left--;
            }
        }
    }
    while (cnt_left) fin.push_back(val_left); cnt_left--;
    for (int i = 0; i < fin.size(); i++) ans += i * fin[i];

    cout << ans << '\n';
}
