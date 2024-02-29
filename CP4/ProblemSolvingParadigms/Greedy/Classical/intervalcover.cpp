#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef tuple<double, double, int> iii;
typedef vector<iii> vii;

const double EPS = 1e-9;

auto cmp = [](iii &a, iii &b) {
  auto &[a_l, a_r, idx1] = a;
  auto &[b_l, b_r, idx2] = b;
  if (fabs(a_l - b_l) > EPS) return a_l < b_l;
  return a_r > b_r;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  double A, B;
  int n;
  while (cin >> A >> B >> n) {
    vii arr;
    vi output;
    for (int i = 0; i < n; i++) {
      double a, b; cin >> a >> b;
      arr.emplace_back(a, b, i);
    }
    if (fabs(A - B) < EPS) {
      bool found = false;
      for (int i = 0; i < n; i++) {
        auto &[a, b, idx] = arr[i];
        if (a <= A && b >= B) {
          cout << 1 << '\n' << i << '\n';
          found = true;
          break;
        }
      }
      if (!found) cout << "impossible\n";
      continue;
    }
    sort(arr.begin(), arr.end(), cmp);
    bool possible = true;
    double covered = A;
    int ans = 0;
    for (int i = 0; (i < n) && possible; ++i) {
      if (covered >= B) break; // done
      if (get<1>(arr[i]) < covered + EPS) continue; // inside prev interval
      if (get<0>(arr[i]) < covered + EPS) { // can cover
        double max_r = A - 1;
        int max_id;
        for (; (i < n) && (get<0>(arr[i]) < covered + EPS); ++i) {
          if (get<1>(arr[i]) > max_r) {
            max_r = get<1>(arr[i]);
            max_id = get<2>(arr[i]);
          }
        }
        ++ans;
        output.push_back(max_id);
        covered = max_r;                       // jump here
        i--;  // minus 1 because sprinkler[i].x_l > covered
      } else possible = false;
    }
    if (!possible || (covered < B)) cout << "impossible\n";
    else {
      cout << ans << '\n';
      for (int i : output) cout << i << ' ';
      cout << '\n';
    }
  }
}
