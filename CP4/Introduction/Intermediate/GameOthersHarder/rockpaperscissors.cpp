#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<string> split(string s, const string& delimiter) {
    size_t pos;
    string token;
    vector<string> arr;
    if (s.empty()) return arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    arr.emplace_back(s);
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; string s;
    while (cin >> n && n != 0) {
        cin >> k; cin.ignore();
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) v.emplace_back(0, 0);
        int games = n * k * (n - 1) / 2;
        while (games--) {
            getline(cin, s);
            vector<string> splitted = split(s, " ");
            if (splitted[1] != splitted[3]) {
                v[stoi(splitted[0]) - 1].second++;
                v[stoi(splitted[2]) - 1].second++;
                if (splitted[1] == "rock" && splitted[3] == "paper") {
                    v[stoi(splitted[2]) - 1].first++;
                } else if (splitted[1] == "rock" && splitted[3] == "scissors") {
                    v[stoi(splitted[0]) - 1].first++;
                } else if (splitted[1] == "paper" && splitted[3] == "rock") {
                    v[stoi(splitted[0]) - 1].first++;
                } else if (splitted[1] == "paper" && splitted[3] == "scissors") {
                    v[stoi(splitted[2]) - 1].first++;
                } else if (splitted[1] == "scissors" && splitted[3] == "paper") {
                    v[stoi(splitted[0]) - 1].first++;
                } else {
                    v[stoi(splitted[2]) - 1].first++;
                }
            }
        }
        for (auto& p : v) {
            if (p.second == 0) cout << '-' << endl;
            else cout << fixed << setprecision(3) << static_cast<double>(p.first) / p.second << endl;
        }
        cout << endl;
    }
}