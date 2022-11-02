#include<bits/stdc++.h>
using namespace std;

const int MAX = 1000;
int deck[MAX],temp[MAX];


int main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
    for (int i=0;i<MAX;i++){
        deck[i] = i;
    }
    int n;string s;cin>>n>>s;
    int ans=1; bool flag = true;
    while (true){
        for (int i=0;i<n;i++){
            temp[i] = deck[i];
        }
        if (s == "out"){
            for (int i=0;i<n>>1;i++){
                deck[i<<1] = temp[i];
                deck[(i<<1) + 1] = (n&1 == 1) ? temp[i + (n>>1) + 1] : temp[i + (n>>1)];
            }
            if (n&1 == 1) deck[n-1] = temp[n>>1];
        } else {
            for (int i=0;i<n>>1;i++){
                deck[i<<1] = temp[i + (n>>1)];
                deck[(i<<1) + 1] = temp[i];
            }
            if (n&1 == 1) deck[n-1] = temp[n-1];
        }
        for (int i=0;i<n;i++){
            if (deck[i] != i) {
                ans++; goto loop;
            }
        }
        break;
        loop:;
    }
    cout << ans;
}