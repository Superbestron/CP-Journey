#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; string s; cin >> t;
    while (t--) {
        cin >> s; int total = 0;
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; i--) {
            int sum;
            if ((s.size() - i) % 2 == 0) {
                sum = (s[i] - '0') * 2;
                if (sum >= 10) {
                    string temp = to_string(sum);
                    sum = (temp[0] - '0') + (temp[1] - '0');
                }
            } else {
                sum = s[i] - '0';
            }
            total += sum;
        }
        cout << (total % 10 ? "FAIL" : "PASS") << endl;
    }
}