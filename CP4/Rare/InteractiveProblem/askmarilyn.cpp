#include<bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  int drink;
  char pos;
  for (int i = 0; i < 1000; i++) {
    unordered_set<char> st({'A', 'B', 'C'});
    char ch = rand() % 3 + 'A';
    st.erase(ch);
    cout << ch << endl;
    cin >> pos >> drink;
    if (drink == 1) cout << pos << endl;
    else {
      st.erase(pos);
      cout << *st.begin() << endl;
    }
    cin >> drink >> pos;
  }
}
