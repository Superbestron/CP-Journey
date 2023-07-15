#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;
typedef tree<string, null_type, less<string>, rb_tree_tag, tree_order_statistics_node_update> ost;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int command, gender;
    string name;
    ost t_m, t_f;
    string lb, ub;
    while (cin >> command && command != 0) {
        if (command == 1) {
            cin >> name >> gender;
            if (gender == 1) t_m.insert(name);
            else t_f.insert(name);
        } else if (command == 2) {
            cin >> name;
            auto it = t_m.lower_bound(name);
            if (*it == name) t_m.erase(it);
            else t_f.erase(name);
        } else {
            cin >> lb >> ub >> gender;
            if (gender == 0) {
                cout << t_m.order_of_key(ub) - t_m.order_of_key(lb)
                        + t_f.order_of_key(ub) - t_f.order_of_key(lb) << '\n';
            } else if (gender == 1) {
                cout << t_m.order_of_key(ub) - t_m.order_of_key(lb) << '\n';
            } else {
                cout << t_f.order_of_key(ub) - t_f.order_of_key(lb) << '\n';
            }
        }
    }
}
