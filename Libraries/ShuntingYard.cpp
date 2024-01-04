#include <bits/stdc++.h>
using namespace std;

vector<int> values;

string shunting_yard(string &s) {
  int var_counter = 0;
  string ans;
  stack<char> st;
  for (auto &c : s) {
    if (isalpha(c)) {
      ans.push_back('0' + var_counter);
      var_counter++;
    } else if (c == '(') {
      st.emplace(c);
    } else if (c == ')') {
      ans += (st.top());
      st.pop();
      st.pop();
    } else {  // operator
      st.emplace(c);
    }
  }
  while (!st.empty()) {
    ans += st.top();
    st.pop();
  }
  return ans;
}

int substitute(string &expr) {
  stack<int> st;
  int a, b;
  for (auto &c : expr) {
    if (isdigit(c)) {
      st.emplace(values[c - '0']);
    } else if (c == '+') {
      a = st.top(); st.pop();
      b = st.top(); st.pop();
      st.emplace(a + b);
    } else if (c == '-') {
      a = st.top(); st.pop();
      b = st.top(); st.pop();
      st.emplace(b - a);
    } else if (c == '*') {
      a = st.top(); st.pop();
      b = st.top(); st.pop();
      st.emplace(a * b);
    }
  }
  return st.top();
}
