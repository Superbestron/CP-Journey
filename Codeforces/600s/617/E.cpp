#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

const int N = 1e6 + 1;
int s = sqrt(N) + 1;
int n, m, k;
int cnt[1 << 20];
ll result = 0;

struct tquery {
  int idx, L, R;
};

bool operator<(const tquery &a, const tquery &b) {
  if (a.L / s != b.L / s) return a.L < b.L;
  return a.R < b.R;
}

void add(ll v) {
  result += cnt[v ^ k];
  cnt[v]++;
}

void remove(ll v) {
  cnt[v]--;
  result -= cnt[v ^ k];
}

vll answerAllQueries(vll &A, vector<tquery> &query) {
  int L = 1, R = 0;
  vll out(query.size());
  sort(query.begin(), query.end());
  for (auto &q : query) {
    while (L > q.L) {
      L--;
      add(A[L - 1]);
    }
    while (R < q.R) {
      R++;
      add(A[R]);
    }
    while (L < q.L) {
      remove(A[L - 1]);
      L++;
    }
    while (R > q.R) {
      remove(A[R]);
      R--;
    }
    out[q.idx] = result;
  }
  return out;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m >> k;
  memset(cnt, 0, sizeof cnt);
  cnt[0] = 1;
  vll A(n), pref(n + 2);
  vector<tquery> query;
  for (ll &i : A) cin >> i;
  for (int i = 1; i <= n; i++) {
    pref[i] = pref[i - 1] ^ A[i - 1];
  }
  for (int i = 0; i < m; i++) {
    int L, R;
    cin >> L >> R;
    query.push_back(tquery{i, L, R});
  }
  vll output(answerAllQueries(pref, query));
  for (ll i : output) cout << i << '\n';
}
