#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, val;
    string command;
    cin >> n;
    deque<int> d1, d2;
    while (n--) {
        cin >> command >> val;
        if (command.size() == 3) { // get
            if (val < d1.size()) {
                cout << d1[val] << endl;
            } else {
                cout << d2[val - d1.size()] << endl;
            }
        } else if (command[5] == 'b') {
            d2.push_back(val);
            if (d1.size() != d2.size()) {
                d1.push_back(d2.front());
                d2.pop_front();
            }
        } else if (command[5] == 'f') {
            d1.push_front(val);
            if (d1.size() - d2.size() == 2) {
                d2.push_front(d1.back());
                d1.pop_back();
            }
        } else {
            if (d1.size() == d2.size()) d1.push_back(val);
            else d2.push_front(val);
        }
    }
}