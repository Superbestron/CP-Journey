#include <iostream>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    char c;
    bool first = true;
    cin >> noskipws;
    while (cin>>c) {
        if (cin.eof()) break;
        if (first) {
            if (c=='"') {
                cout<<"``";
                first=false;
            } else cout<<c;
        } else {
            if (c=='"') {
                cout << "''";
                first = true;
            } else cout<<c;
        }
    }
}

