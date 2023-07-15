#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int base = 1000;
int nums[1000000], f[base], temp[1000000];

void counting_sort(int n, int exp) {
    memset(f, 0, sizeof f);
    for (int i = 0; i < n; i++) {
        f[(nums[i] / exp) % base]++;
    }
    for (int i = 1; i < base; i++) {
        f[i] += f[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        temp[f[(nums[i] / exp) % base]-- -1] = nums[i];
    }
    copy(begin(temp), end(temp), begin(nums));
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, a, b, c, x, y;
    cin >> t;
    while (t-- > 0) {
        cin >> n >> a >> b >> c >> x >> y;
        // generate sequence
        nums[0] = a;
        for (int i = 1; i < n; i++) nums[i] = (static_cast<long long>(nums[i - 1]) * b + a) % c;
        for (int j = 0; j < 3; j++) counting_sort(n, pow(base, j));
        long long V = 0;
        for (int i = 0; i < n; i++) {
            V = (V * x + nums[i]) % y;
        }
        cout << V << endl;
    }
}