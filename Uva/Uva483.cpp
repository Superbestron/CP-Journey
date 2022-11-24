#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    char c;
    vector<char> arr;
    cin >> noskipws;
    while (cin>>c) {
        if (cin.eof()) break;
        if (c==' ' || c=='\n') {
            reverse(arr.begin(), arr.end());
            cout<<string(arr.begin(), arr.end())<<c;
            arr.clear();
        } else {
            arr.push_back(c);
        }
    }
}

