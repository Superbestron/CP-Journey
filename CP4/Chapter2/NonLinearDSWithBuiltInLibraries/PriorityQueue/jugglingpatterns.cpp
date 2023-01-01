#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string n;
    while (cin >> n) {
        unordered_set<int> s;
        int sum = 0;
        for (char i : n) sum += i - '0';
        if (sum % n.size() != 0) {
            cout << n << ": " << "invalid # of balls" << endl;
            continue;
        }
        int balls = sum / n.size();
        // Key idea is to notice that after 1 whole pattern, the balls itself have to land on unique
        // timestamps so that no 2 balls will land at the same time
        for (int i = 0; i < n.size(); i++) s.insert((n[i] - '0' + i) % n.size());
        if (s.size() == n.size()) cout << n << ": " << "valid with " << balls << " balls" << endl;
        else cout << n << ": " << "invalid pattern" << endl;
    }
}