#include <bits/stdc++.h>

using namespace std;

int main() {
    string temp;
    getline(cin, temp);
    istringstream s(temp);
    vector<string> input, team1, team2;
    int len = 0, n, ctr = -1;
    bool is_team1 = true;
    while (s >> temp) {
        len++;
    }
    cin >> n;
    while (n--) {
        cin >> temp;
        input.push_back(temp);
    }
    while (!input.empty()) {
        ctr = (ctr + len) % input.size();
        // cout << input[ctr];
        if (is_team1) {
            team1.push_back(input[ctr]);
        } else {
            team2.push_back(input[ctr]);
        }
        is_team1 = !is_team1;
        input.erase(input.begin() + ctr);
        ctr--;
    }

    cout << team1.size() << '\n';
    for (auto& str : team1) cout << str << '\n';
    cout << team2.size() << '\n';
    for (auto& str : team2) cout << str << '\n';

    return 0;
}
