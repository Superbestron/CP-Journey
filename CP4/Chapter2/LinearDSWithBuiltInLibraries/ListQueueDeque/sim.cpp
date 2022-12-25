#include <iostream>
#include <list>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    string s;
    cin >> t;
    cin.ignore();
    list<char> l;
    while (t--) {
        getline(cin, s);
        l.clear();
        auto it = l.begin();
        for (char c : s) {
            if (c == '[') {
                it = l.begin();
            } else if (c == ']') {
                it = l.end();
            } else if (c == '<') {
                if (it != l.begin()) {
                    it = l.erase(--it);
                }
            } else {
                it = l.insert(it, c);
                it++;
            }
        }
        for (char c : l) cout << c;
        cout << endl;
    }
}