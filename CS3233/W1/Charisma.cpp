#include<bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int A, B, C, D;
  while (cin >> A >> B >> C >> D) {
    int diff = C - A;
    if (diff == 0) {
      if (D != B) cout << 0 << ' ' << A << '\n';
      else cout << "More than one possible answer!\n";
    } else if (diff > 0) {
      if (D >= B) cout << "No possible answer!\n";
      else {
        int pages = diff / (B - D);
        if (diff % (B - D) != 0 || pages > 555) cout << "No possible answer!\n";
        else cout << pages << ' ' << A + pages * B << '\n';
      }
    } else {
      diff = -diff;
      if (B >= D) cout << "No possible answer!\n";
      else {
        int pages = diff / (D - B);
        if (diff % (D - B) != 0 || pages > 555) cout << "No possible answer!\n";
        else cout << pages << ' ' << A + pages * B << '\n';
      }
    }
  }
}