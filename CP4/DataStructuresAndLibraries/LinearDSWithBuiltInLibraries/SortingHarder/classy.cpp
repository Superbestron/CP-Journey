#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int t, n;
    cin >> t;
    auto comparator = [](auto& v1, auto& v2) {
        if (v1[1] != v2[1]) return stoll(v1[1]) > stoll(v2[1]);
        cout << v1[0] << ' ' << v2[0] << ' ' << bool(v1[0] < v2[0]) << endl;
        return v1[0] < v2[0];
    };
    while (t-- > 0) {
        cin >> n;
        string name, rank;
        vector<vector<string>> v;
        for (int i = 0; i < n; i++) {
            // need to do parsing
            vector<string> temp;
            cin >> name;
            name = name.substr(0, name.find(':'));
            cin >> rank;
            temp.emplace_back(name);
            cin >> name; // ignore class
            unsigned long hyphen_index = rank.find('-');
            string c;
            while (hyphen_index != string::npos) {
                string t1 = rank.substr(0, hyphen_index);
                rank = rank.substr(hyphen_index + 1);
                if (t1 == "lower") c += '1';
                else if (t1 == "middle") c += '2';
                else c += '3';
                hyphen_index = rank.find('-');
            }
            if (rank == "lower") c += '1';
            else if (rank == "middle") c += '2';
            else c += '3';
            reverse(c.begin(), c.end());
            for (int i = c.size(); i < 10; i++) {
                c += '2';
            }
            temp.emplace_back(c);
            v.emplace_back(temp);
        }
        // each vector is [name, rank1, rank2, ..., rankn]
        sort(v.begin(), v.end(), comparator);
        for (auto& str : v) cout << str[0] << endl;
        cout << "==============================" << endl;
    }
}
