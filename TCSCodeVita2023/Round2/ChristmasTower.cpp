#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vi memo(10001, -1), nxt(10001, -1), arr(5);
unordered_map<int, int> mp;
int H;

int dp(int height) {
  int &ans = memo[height];
  if (height == H) return ans = 0;
  if (ans != -1) return ans;

  ans = -1e9;
  for (int b : arr) {
    if (height + b <= H) {
      int temp = 1 + dp(height + b);
      if (temp > ans) {
        ans = temp;
        nxt[height] = height + b;
      }
    }
  }
  return ans;
}

void get_output(int height) {
  if (height == H) return;
  int nxt_h = nxt[height];
  mp[nxt_h - height]++;
  get_output(nxt_h);
}

auto comp = [](ii &t1, ii &t2) {
  if (get<1>(t1) == get<1>(t2)) return get<0>(t1) < get<0>(t2);
  return get<1>(t1) > get<1>(t2);
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> H;
  for (int &i : arr) cin >> i;
  dp(0);
  if (memo[H] == -1) cout << "Impossible\n";
  else {
    get_output(0);
    vii t = vii(mp.begin(), mp.end());
    sort(t.begin(), t.end(), comp);
    for (auto &p : t) {
      cout << get<0>(p) << ' ';
    }
    cout << '\n';
  }
}
