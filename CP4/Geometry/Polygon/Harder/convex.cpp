#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n;
vii starting_vector = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vii dir = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

vii generate_vector() {
  int target_num_vectors = ceil(n / 8.0);
  vii vecs;
  for (int j = 1; vecs.size() < target_num_vectors; j++) {
    for (int den = 1; j - den + 1 >= den; den++) {
      int num = j - den + 1;
      if (gcd(num, den) == 1) {
        vecs.emplace_back(num, den);
        if ((int) vecs.size() == target_num_vectors) break;
      }
    }
  }
  // Get the reciprocal of the vectors, excluding 1/1 -> 1/1
  for (int i = 1; i < target_num_vectors; i++) {
    vecs.emplace_back(vecs[i].second, vecs[i].first);
  }
  return vecs;
}

bool comp(pair<int, int> &a, pair<int, int> &b) {
  return (a.first / (double) a.second > b.first / (double) b.second);  // 1/gradient of a > 1/gradient of b
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  vii vecs = generate_vector(), ans;
  sort(vecs.begin(), vecs.end(), comp);

  int x = 0, y = 0;
  for (int part = 0; part < 4 && ((int) ans.size() < n); part++) {
    x += starting_vector[part].first;
    y += starting_vector[part].second;

    ans.emplace_back(x, y);

    for (int i = 0; i < (int) vecs.size() && ((int) ans.size() < n); i++) {
      int index = (part % 2 == 0) ? (vecs.size() - i - 1) : i;
      x += dir[part].first * vecs[index].first;
      y += dir[part].second * vecs[index].second;
      ans.emplace_back(x, y);
    }
  }
  int minimum_y = INT_MAX;
  for (auto &an : ans) minimum_y = min(minimum_y, an.second);

  for (int i = 0; i < n; i++) cout << ans[i].first << " " << -minimum_y + ans[i].second << endl;
}
