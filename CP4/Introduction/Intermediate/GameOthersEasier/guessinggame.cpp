#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int num; string s;
    while (true) {
        vector<bool> v(11);
        fill(v.begin(), v.begin() + 11, true);
        while (true) {
            cin >> num; cin.ignore();
            if (num == 0) return 0;
            getline(cin, s);
            if (s[4] == 'h') {
                for (int i = num; i <= 10; i++) v[i] = false;
            } else if (s[4] == 'l') {
                for (int i = 0; i <= num; i++) v[i] = false;
            } else {
                if (v[num]) cout << "Stan may be honest" << endl;
                else cout << "Stan is dishonest" << endl;
                break;
            }
        }
    }
}