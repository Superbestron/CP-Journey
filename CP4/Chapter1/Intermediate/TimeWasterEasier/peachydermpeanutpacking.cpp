#include <bits/stdc++.h>

using namespace std;

class box {
public:
    double x1, x2, y1, y2;
    string size;
};

bool in_box(box& b, double x, double y) {
    return (b.x1 <= x && x <= b.x2 && b.y1 <= y && y <= b.y2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    double x, y;
    string size;
    while (cin >> n && n != 0) {
        vector<box> boxes;
        for (int i = 0; i < n; i++) {
            box b;
            cin >> b.x1 >> b.y1 >> b.x2 >> b.y2 >> b.size;
            boxes.push_back(b);
        }
        cin >> n;
        while (n--) {
            cin >> x >> y >> size;
            bool printed = false;
            for (box& b : boxes) {
                if (in_box(b, x, y)) {
                    if (b.size == size) {
                        cout << size << " correct\n";
                    } else {
                        cout << size << ' ' << b.size << '\n';
                    }
                    printed = true;
                    break;
                }
            }
            if (!printed) cout << size << " floor\n";
        }
        cout << '\n';
    }
}