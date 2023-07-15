#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void process(vector<string>& v) {
    int size = 0;
    for (auto & i : v) {
        reverse(i.begin(), i.end());
        size = max(size, static_cast<int>(i.size()));
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        string s;
        reverse(v[i].begin(), v[i].end());
        for (int j = 0; j < size - v[i].size(); j++) {
            s += ' ';
        }
        s += v[i];
        v[i] = s;
    }
    for (auto& i : v) {
        cout << i << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    string s;
    vector<string> v;
    while (getline(cin, s)) {
        if (s.empty()) {
            process(v);
            cout << endl;
            v.clear();
        } else {
            v.push_back(s);
        }
    }
    process(v);
}
