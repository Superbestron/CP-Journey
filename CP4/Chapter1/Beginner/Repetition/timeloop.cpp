#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    string s = "Abracadabra";
    for (int i = 1; i <= n; i++) {
        cout << i << ' ' << s << endl;
    }
}
