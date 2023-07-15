#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string v, bin, ans;
    cin >> v;
    for (auto i : v) {
        if (i == '0') bin += "000";
        if (i == '1') bin += "001";
        if (i == '2') bin += "010";
        if (i == '3') bin += "011";
        if (i == '4') bin += "100";
        if (i == '5') bin += "101";
        if (i == '6') bin += "110";
        if (i == '7') bin += "111";
    }
    reverse(bin.begin(), bin.end());
    while (bin.size() % 4) {
        bin.push_back('0');
    }
    reverse(bin.begin(), bin.end());

    for (int i = 0; i < bin.size(); i += 4) {
        string here = bin.substr(i, 4);
        if (here == "0000") ans.push_back('0');
        if (here == "0001") ans.push_back('1');
        if (here == "0010") ans.push_back('2');
        if (here == "0011") ans.push_back('3');
        if (here == "0100") ans.push_back('4');
        if (here == "0101") ans.push_back('5');
        if (here == "0110") ans.push_back('6');
        if (here == "0111") ans.push_back('7');
        if (here == "1000") ans.push_back('8');
        if (here == "1001") ans.push_back('9');
        if (here == "1010") ans.push_back('A');
        if (here == "1011") ans.push_back('B');
        if (here == "1100") ans.push_back('C');
        if (here == "1101") ans.push_back('D');
        if (here == "1110") ans.push_back('E');
        if (here == "1111") ans.push_back('F');
    }

    // remove starting zeroes
    reverse(ans.begin(), ans.end());
    while (ans.back() == '0') ans.pop_back();
    reverse(ans.begin(), ans.end());

    // edge case
    if (ans.empty()) ans.push_back('0');

    cout << ans;
}