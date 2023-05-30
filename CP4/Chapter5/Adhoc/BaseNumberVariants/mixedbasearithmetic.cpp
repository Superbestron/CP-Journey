#include <bits/stdc++.h>
using namespace std;

// Recursive approach
// everytime you add, just increment last digit, unless there is overflow, then you increment the next digit

inline void add(string& str, int index) {
    char& last_char = str[index];
    if (last_char == '9' || last_char == 'z' || last_char == 'Z') {
        if (last_char == '9') last_char = '0';
        else if (last_char == 'z') last_char = 'a';
        else last_char = 'A';
        if (index == 0) {
            if (last_char == '0') str = '1' + str;
            else if (last_char == 'a') str = 'a' + str;
            else str = 'A' + str;
        } else add(str, index - 1);
    } else last_char++;
}

int main() {
    string c;
    int i;
    while (cin >> c >> i) {
        while (i--) add(c, c.size() - 1);
        cout << c << '\n';
    }
}