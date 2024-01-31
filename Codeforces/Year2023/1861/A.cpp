#include <bits/stdc++.h>
using namespace std;

// We will find all primes in the range 1 to 120
int const N = 100;
int is_prime[N];

void sieve() {
    // We cross out all composites from 2 to sqrt(N)
    int i=2;
    // This will loop from 2 to int(sqrt(x))
    while(i*i <= N) {
        // If we already crossed out this number, then continue
        if(is_prime[i] == 0) {
            i++;
            continue;
        }
        int j = 2*i;
        while(j < N) {
            // Cross out this as it is composite
            is_prime[j] = 0;
            // j is incremented by i, because we want to cover all multiples of i
            j += i;
        }
        i++;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;

    // is_prime[i] = 1 means that i is prime and is_prime[i] = 0 means that i is composite
    // Initially, we say all of them are prime
    for(int& i : is_prime) {
        i = 1;
    }
    // We know 0 and 1 are composites
    is_prime[0] = 0;
    is_prime[1] = 0;
    sieve();
    string s;
    while (t--) {
        cin >> s;
        int ans = -1;
        for (int i = 0; i < s.size(); i++) {
            for (int j = i + 1; j < s.size(); j++) {
                string str;
                str += string(1, s[i]) + string(1, s[j]);
                int x = stoi(str);
                if (is_prime[x]) {
                    ans = x;
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
}

