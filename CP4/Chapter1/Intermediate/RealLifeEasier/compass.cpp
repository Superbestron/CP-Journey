#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n1, n2; cin >> n1 >> n2;
    if (n2 < n1) n2 += 360;
    if (n2 - n1 > 360 - (n2 - n1)) cout << -(360 - (n2 - n1));
    else cout << n2 - n1;
}