#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n;
    string name, s, s1 = "pea soup", s2 = "pancakes";
    while (n--) {
        cin >> k; cin.ignore();
        getline(cin, name);
        bool b1 = false, b2 = false;
        while (k--) {
            getline(cin, s);
            if (s == s1) b1 = true;
            else if (s == s2) b2 = true;
            if (b1 && b2) {
                cout << name;
                return 0;
            }
        }
    }
    cout << "Anywhere is fine I guess";
}