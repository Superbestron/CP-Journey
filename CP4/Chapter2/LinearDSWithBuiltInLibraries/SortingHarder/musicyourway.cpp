#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> v;
    vector<vector<string>> songs;
    string s, header, attribute;
    int m, n;
    getline(cin, s);
    header = s;
    string delimiter = " ";
    size_t pos;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        v.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    v.emplace_back(s);
    cin >> m;
    getline(cin, s); // skip line
    while (m-- > 0) {
        vector<string> song;
        getline(cin, s);
        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            song.emplace_back(token);
            s.erase(0, pos + delimiter.length());
        }
        song.emplace_back(s);
        songs.emplace_back(song);
    }

    cin >> n;
    getline(cin, s);
    while (n-- > 0) {
        cin >> attribute;
        cout << header << endl;
        auto comparator = [&](auto& v1, auto& v2) {
            int ctr = 0;
            for (auto& i : v) {
                if (attribute == i) {
                    break;
                }
                ctr++;
            }
            return v1[ctr] < v2[ctr];
        };
        stable_sort(songs.begin(), songs.end(), comparator);
        for (auto& i : songs) {
            for (auto& j : i) {
                cout << j << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
}
