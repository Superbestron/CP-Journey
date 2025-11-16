#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

class Node {
  public:
    bool x, y, is_x_set = false, is_y_set = false;
    int op;
    // 0: OR, 1: AND, 2: XOR
    Node() {
        x = false, y = false, op = 0;
    }
    Node(bool x, bool y, int op) : x(x), y(y), op(op) {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<string, Node> mp;
    map<string, bool, greater<>> z_mp;
    unordered_map<string, unordered_set<string>> AL;
    queue<string> q;
    string s;
    bool first = true;
    while (getline(cin, s)) {
        if (s.empty()) {
            first = false;
            continue;
        }
        if (first) {
            string name = s.substr(0, 3);
            bool is_on = s.substr(5, 1) == "1";
            Node n {is_on, is_on, 0};
            mp[name] = n;
            q.push(name);
        } else {
            // y08 AND x08 -> pkh
            string n1 = s.substr(0, 3);
            int idx = 4, op;
            if (s[idx] == 'O') {
                idx += 3; op = 0;
            } else if (s[idx] == 'A') {
                idx += 4; op = 1;
            } else {
                idx += 4; op = 2;
            }
            string n2 = s.substr(idx, 3);
            idx += 7;
            string n3 = s.substr(idx, 3);
            Node n {true, true, op};
            mp[n3] = n;
            AL[n1].insert(n3);
            AL[n2].insert(n3);
        }
    }
    while (!q.empty()) {
        string name = q.front(); q.pop();
        bool value;
        Node& n = mp[name];
        if (n.op == 0) {
            value = n.x | n.y;
        } else if (n.op == 1) {
            value = n.x & n.y;
        } else {
            value = n.x ^ n.y;
        }
        if (name[0] == 'z') {
            z_mp[name] = value;
        }
        for (const string& o : AL[name]) {
            Node& n_o = mp[o];
            if (!n_o.is_x_set) {
                n_o.is_x_set = true;
                n_o.x = value;
            } else if (!n_o.is_y_set) {
                n_o.is_y_set = true;
                n_o.y = value;
                q.push(o);
            } else {
                assert(false);
            }
        }
    }
    string binary_string;
    for (auto& [x, y] : z_mp) {
        binary_string += y ? '1' : '0';
    }
    ll ans = stoll(binary_string, nullptr, 2);
    cout << ans << '\n';
}
