#include <bits/stdc++.h>
using namespace std;

int N, not_reached = 1, same = 0, gabby_steps = 0, spike_steps = 0;

inline void gabby() {
  cout << "NEXT GABBY\n";
  gabby_steps++;
  cout.flush();
  cin >> not_reached >> same;
  cout.flush();
  if (gabby_steps == N) {
    cout << "ASK GABBY\n";
    cout.flush();
    exit(0);
  }
}

inline void spike() {
  cout << "NEXT SPIKE\n";
  spike_steps++;
  cout.flush();
  cin >> not_reached >> same;
  cout.flush();
  if (spike_steps == N) {
    cout << "ASK SPIKE\n";
    cout.flush();
    exit(0);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  while (true) {
    gabby();
    spike();
    spike();
    if (same) break;
  }
  int lambda = 0;
  while (true) {
    spike();
    lambda++;
    if (same) break;
  }

  int left = (N - gabby_steps) % lambda;
  while (left--) {
    spike();
  }
  cout << "ASK SPIKE\n";
  cout.flush();
}
