#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, size;
    string commands;
    cin >> n;
    deque<int> d;

    while (n--) {
        d.clear();
        bool front = true, printed = false;
        cin >> commands >> size;
        cin.ignore(); // ignore '/n'
        for (int i = 0; i < size; i++) {
            cin.ignore();
            int t;
            cin >> t;
            d.push_back(t);
        }
        cin.ignore();
        if (size == 0) {
            cin.ignore();
        }
        for (char c : commands) {
            if (c == 'R') front = !front;
            else {
                if (d.empty()) {
                    cout << "error" << endl;
                    printed = true;
                    break;
                }
                if (front) d.pop_front();
                else d.pop_back();
            }
        }
        if (!printed) {
            cout << '[';
            while (!d.empty()) {
                if (front) {
                    cout << d.front();
                    d.pop_front();
                } else {
                    cout << d.back();
                    d.pop_back();
                }
                if (!d.empty()) {
                    cout << ",";
                }
            }
            cout << ']' << endl;
        }
    }
}