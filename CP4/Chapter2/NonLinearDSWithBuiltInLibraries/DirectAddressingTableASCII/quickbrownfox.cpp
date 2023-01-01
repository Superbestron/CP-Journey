#include <iostream>
#include <bitset>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n; cin.ignore();
    string s;
    while (n--) {
        bitset<26> bs;
        getline(cin, s);
        for (char c : s) {
            if (isupper(c)) bs.set(c - 'A');
            else if (islower(c)) bs.set(c - 'a');
        }

        string missing;
        for (int i = 0; i < 26; i++) {
            if (!bs[i]) missing += static_cast<char>(i + 'a');
        }
        if (missing.empty()) cout << "pangram" << endl;
        else cout << "missing " << missing << endl;
    }
}