#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, player = 0; cin >> n;
    char prev = ' ';
    string s;
    unordered_set<string> set;
    while (n--) {
        cin >> s;
        if (prev != ' ' && (prev != s[0] || set.count(s) == 1)) {
            cout << "Player " << player + 1 << " lost";
            return 0;
        }
        prev = s[s.size() - 1];
        player = (player + 1) % 2;
        set.insert(s);
    }
    cout << "Fair Game";
}