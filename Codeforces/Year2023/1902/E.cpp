#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct vertex {
  ll count = 0;
  vector<vertex*> child;
  explicit vertex(char a) { child.assign(26, nullptr); }
};

class Trie {                                     // this is TRIE
 private:                                         // NOT Suffix Trie
  vertex *root;
 public:
  Trie() { root = new vertex('!'); }

  void insert(string &word) {                     // insert a word into trie
    vertex *cur = root;
    for (char c : word) { // O(n)
      int alphaNum = c - 'a';
      if (cur->child[alphaNum] == nullptr)          // add new branch if NULL
        cur->child[alphaNum] = new vertex(c);
      cur = cur->child[alphaNum];
      cur->count++;
    }
  }

  ll search(string& word) {                     // true if word in trie
    vertex *cur = root;
    ll cnt = 0;
    for (char i : word) { // O(m)
      int alphaNum = i - 'a';
      if (cur->child[alphaNum] == nullptr)          // not found
        break;
      cur = cur->child[alphaNum];
      cnt += cur->count;
    }
    return 2 * cnt;
  }
};

int main() {
  Trie T;
  int n; cin >> n;
  string s;
  vector<string> v;
  ll total = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> s;
    string reversed(s);
    reverse(reversed.begin(), reversed.end());
    T.insert(reversed);
    v.push_back(s);
    total += s.size();
  }
  for (auto &str : v) {
    ll num = total + (ll) str.size() * n;
    ans += num - T.search(str);
  }
  cout << ans << '\n';
}
