#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, s;
    unordered_map<int, int> m;
    string num;
    cin >> n >> s;
    auto canFlip = [](string& num) -> string {
        string flipped;
        for (int i = num.size() - 1; i >= 0; i--) {
            char c = num[i];
            int x = c - '0';
            if (x == 1 || x == 2 || x == 5 || x == 8 || x == 0) {
                flipped += c;
            } else if (x == 6) {
                flipped += static_cast<char>(c + 3); // change to 5/9
            } else if (x == 9) {
                flipped += static_cast<char>(c - 3);
            } else {
                return "";
            }
        }
        return flipped;
    };
    while (n-- > 0) {
        // routine to check if some number can be flipped, and what number it's flipped to

        // handle edge case where a number appears twice in set
        cin >> num;
        int val = stoi(num);
//        cout << val << endl;
        if (m.count(s - val) == 1) {
            cout << "YES";
            return 0;
        }
        string str = canFlip(num);
        if (!str.empty()) {
            int flippedValue = stoi(str);
            if (m.count(s - flippedValue) == 1) {
                cout << "YES";
                return 0;
            }
            m[stoi(str)]++;
        }
        m[val]++; // don't make the flipped value match with own value
    }
    cout << "NO";
}