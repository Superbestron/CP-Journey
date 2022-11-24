#include <iostream>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    int T,L,N,D;
    char Di;
    cin>>T;
    for (int t = 1; t <= T; t++) {
        cin>>L>>N;
        long curr = 0,ans = 0;
        for (int k = 0; k < N; k++) {
            cin>>D>>Di;
            if (Di == 'C'){
                curr += D;
                if (curr>0){
                    ans += curr/L;
                    curr %= L;
                }
            } else {
                curr -= D;
                if (curr<0){
                    ans += curr/-L;
                    curr %= -L;
                }
            }
        }
        cout << "Case #" << t << ": " << ans << '\n';
    }
}

