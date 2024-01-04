#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K, x, Q, L, R;
  cin >> N >> K;
  vi seq(N);
  vll prefix(N + 1);
  unordered_map<int, int> X;
  for (int i = 0; i < K; i++) {
    cin >> x;
    X[x]++;
  }
  auto something = [&](int jump, int val) {
    int i = 0;
    while (i < N) {
      seq[i] += val;
      i += jump;
    }
  };
  for (auto &[num, cnt] : X) something(num, cnt);
  for (int i = 0; i < N; i++) {
    prefix[i + 1] = prefix[i] + seq[i];
  }
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    cin >> L >> R;
    cout << prefix[R + 1] - prefix[L] << '\n';
  }
}
