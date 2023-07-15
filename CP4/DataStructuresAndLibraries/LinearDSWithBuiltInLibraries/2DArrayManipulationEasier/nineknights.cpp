#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    string s;
    int directions[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, 1},
                            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    auto hash = [](const vector<int>& a) -> int {
        return a[0]*100 + a[1];
    };
    auto equal = [](const vector<int>& a, const vector<int>& b) -> bool {
        return a[0] == b[0] && a[1] == b[1];
    };
    unordered_set<vector<int>, decltype(hash), decltype(equal)> positions(0, hash, equal);
    int knights = 0;
    for (int i = 0; i < 5; i++) {
        cin >> s;
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == 'k') {
                positions.insert(vector<int>({i, j}));
                knights++;
            }
        }
    }
    if (knights != 9) {
        cout << "invalid";
        return 0;
    }

    cout<<endl;
    for (auto& position : positions) {
        // for each direction
        for (auto & direction : directions) {
            int x = position[0] + direction[0];
            int y = position[1] + direction[1];
            if (x < 0 || x >= 5 || y < 0 || y >= 5) {
                continue;
            }
            if (positions.count(vector<int>({x, y})) == 1) {
                cout << "invalid";
                return 0;
            }
        }
    }
    cout << "valid";
}