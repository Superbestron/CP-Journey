#include <bits/stdc++.h>
using namespace std;

struct vertex {
  char alphabet;
  bool exist;
  vector<vertex *> child;
  vertex(char a) : alphabet(a), exist(false) {
    child.assign(26, nullptr); // assumption is only UPPER
  }
};

class Trie {                                     // this is TRIE
 private:                                         // NOT Suffix Trie
  vertex *root;
 public:
  Trie() { root = new vertex('!'); }

  void insert(string word) {                     // insert a word into trie
    vertex *cur = root;
    for (char i : word) { // O(n)
      int alphaNum = i - 'A';
      if (cur->child[alphaNum] == nullptr)          // add new branch if NULL
        cur->child[alphaNum] = new vertex(i);
      cur = cur->child[alphaNum];
    }
    cur->exist = true;
  }

  bool search(string word) {                     // true if word in trie
    vertex *cur = root;
    for (char i : word) { // O(m)
      int alphaNum = i - 'A';
      if (cur->child[alphaNum] == nullptr)          // not found
        return false;
      cur = cur->child[alphaNum];
    }
    return cur->exist;                           // check exist flag
  }

  bool startsWith(string prefix) {               // true if match prefix
    vertex *cur = root;
    for (int i = 0; i < (int) prefix.size(); ++i) {
      int alphaNum = prefix[i] - 'A';
      if (cur->child[alphaNum] == nullptr)          // not found
        return false;
      cur = cur->child[alphaNum];
    }
    return true;                                 // reach here, return true
  }
};

int main() {
  Trie T;
  set <string> S = {"CAR", "CAT", "RAT"};
  for (auto &str : S) {
    printf("Insert %s\n", str.c_str());
    T.insert(str);
  }
  printf("'CAR' exist? %d\n", T.search("CAR"));  // 1 (true)
  printf("'DOG' exist? %d\n", T.search("DOG"));  // 0 (false)
  printf("Starts with 'CA' exist? %d\n", T.startsWith("CA")); // 1 (true)
  printf("Starts with 'Z' exist? %d\n", T.startsWith("Z")); // 0 (false)
  // 0 (false) for this Trie, but in a Suffix Trie, we have a suffix "AT" (from "CAT" or "RAT") that starts with "AT"
  printf("Starts with 'AT' exist? %d\n", T.startsWith("AT"));
  return 0;
}
