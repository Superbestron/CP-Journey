#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string binary;
    cin >> binary;
    while (binary.size() % 3 != 0) {
        binary = '0' + binary;
    }
    for (int i = 0; i < binary.size(); i += 3) {
        string_view temp = binary.substr(i, 3);
        if (temp == "000") cout << 0;
        else if (temp == "001") cout << 1;
        else if (temp == "010") cout << 2;
        else if (temp == "011") cout << 3;
        else if (temp == "100") cout << 4;
        else if (temp == "101") cout << 5;
        else if (temp == "110") cout << 6;
        else if (temp == "111") cout << 7;
    }
}