#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

const int N = 1e6;
int s = sqrt(N) + 1;

struct tquery {
  int idx, L, R;
};

bool operator<(const tquery &a, const tquery &b) {
  if (a.L / s != b.L / s) return a.L < b.L;
  return a.R < b.R;
}

struct toutput {
  int idx, value;
};

bool operator<(const toutput &a, const toutput &b) {
  return a.idx < b.idx;
}

void remove(int idx) {}
void add(int idx) {}
toutput get_answer() { return {0, 0}; }

vi answerAllQueries(vi &A, vector<tquery> &query) {
  int L = 0, R = -1;
  vector<toutput> out;
  sort(query.begin(), query.end());
  for (auto &q : query) {
    while (L > q.L) {
      L--;
      add(L);
    }
    while (R < q.R) {
      R++;
      add(R);
    }
    while (L > q.L) {
      remove(L);
      L++;
    }
    while (R > q.R) {
      remove(R);
      R++;
    }
    out[q.idx] = get_answer();
  }
  sort(out.begin(), out.end());
  vi ans;
  for (auto &t : out) ans.push_back(t.value);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int V; cin >> V;
  int srt = sqrt(V), ans = 1e9;
  for (int i = 1; i <= srt; i++) {
    for (int j = 1; j <= srt; j++) {
      int prod = i * j;
      if (V % prod) continue;
      int side = V / prod;
      ans = min(ans, 2 * prod + 2 * i * side + 2 * j * side);
    }
  }
  cout << ans << '\n';
}
