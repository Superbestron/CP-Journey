#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int solution(int N, int M, const int P[]) {
    int val = 0;
    for (int i = 0; i < N; i++) {
        if (P[i] >= val) {
            val = P[i];
        } else if (val + P[i] > M) {
            return 0;
        }
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    int P[n];
    for(int i=0;i<n;i++){
        cin>>P[i];
    }
    cout<<solution(n,m,P)<<endl;
    return 0;
}
