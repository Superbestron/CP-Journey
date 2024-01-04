#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int s;

struct tquery {
  int idx, L, R;
};

bool operator<(const tquery &a, const tquery &b) {
  if (a.L / s != b.L / s) return a.L < b.L;
  return a.R < b.R;
}

unordered_map<int, int> m;

void remove(int idx) {
  m[idx]--;
  if (m[idx] == 0) m.erase(idx);
}

void add(int idx) {
  m[idx]++;
}

vi answerAllQueries(vi &A, vector<tquery> &query) {
  int L = 0, R = -1;
  vi out(query.size());
  sort(query.begin(), query.end());
  for (auto &q : query) {
    while (L > q.L) {
      L--;
      add(A[L]);
    }
    while (R < q.R) {
      R++;
      add(A[R]);
    }
    while (L < q.L) {
      remove(A[L]);
      L++;
    }
    while (R > q.R) {
      remove(A[R]);
      R--;
    }
    out[q.idx] = m.size();
  }
  return out;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q; cin >> n >> q;
  s = sqrt(n) + 1;
  vector<int> A(n);
  vector<tquery> queries;
  for (int &i : A) cin >> i;
  for (int i = 0; i < q; i++) {
    int L, R;
    cin >> L >> R;
    queries.push_back(tquery{i, L, R});
  }
  vi output(answerAllQueries(A, queries));
  for (int i : output) cout << i << '\n';
}
