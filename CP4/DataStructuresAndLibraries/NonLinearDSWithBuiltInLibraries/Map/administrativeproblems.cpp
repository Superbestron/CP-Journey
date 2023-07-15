#include <bits/stdc++.h>

using namespace std;

// To be honest, the hard part about this question is the implementation
// Mine wasn't very good, so I'll suggest to use more maps to represent the
// different details of cars/spies

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, m, p, q, k, time, d, s; cin >> t;
    string N, name, C;
    char e;
    while (t--) {
        // catalog price, pickup cost, cost per km
        unordered_map<string, vector<int>> cars;
        // status, car, cost
        map<string, vector<string>> spies; // demarcate g as inconsistent
        cin >> n >> m;
        while (n--) {
            cin >> N >> p >> q >> k;
            cars[N] = {p, q, k};
        }
        while (m--) {
            cin >> time >> name >> e;
            if (!spies.count(name)) {
                vector<string> temp(3);
                spies[name] = std::move(temp);
                spies[name][0] = "r";
                spies[name][2] = "0";
            }
            if (e == 'p') {
                cin >> C;
                // A spy can use at most one car at a time
                if (spies[name][0] != "r") spies[name][0] = "g";
                else {
                    spies[name][0] = "p"; spies[name][1] = C;
                    spies[name][2] = to_string(stoll(spies[name][2]) + cars[C][1]);
                }
            } else if (e == 'r') {
                cin >> d;
                // A spy will pick up a car before returning it
                if (spies[name][0] != "p" ) spies[name][0] = "g";
                else {
                    spies[name][2] = to_string(stoll(spies[name][2]) + d * cars[spies[name][1]][2]);
                    spies[name][0] = "r";
                }
            } else {
                cin >> s;
                // Accidents can only happen when a spy is using a car
                if (spies[name][0] != "p" ) spies[name][0] = "g";
                else {
                    int bill = s * cars[spies[name][1]][0];
                    // careful about how you do the division
                    // it can lead to nasty precision errors (I learnt it the hard way)
                    spies[name][2] = to_string(stoll(spies[name][2]) + bill / 100 + (bill % 100 ? 1 : 0));
                }
            }
        }
        for (auto& spy : spies) {
            cout << spy.first << ' ';
            // A spy will always return a car they picked up
            if ((spy.second)[0] == "g" || (spy.second)[0] != "r") cout << "INCONSISTENT" << endl;
            else cout << spy.second[2] << endl;
        }
    }
}
