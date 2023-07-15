#include <iostream>
#include <vector>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    int x,y,n,ans,curr;
    while (cin>>x>>y) {
        ans=0;
        cout<<x<<' '<<y<<' ';
        if (x>y) swap(x,y);
        for (int i=x; i<=y; i++) {
            curr=1;
            n=i;
            while (n>1) {
                if (n%2!=0) n=3*n+1;
                else n/=2;
                curr++;
            }
            ans=max(ans,curr);
        }
        cout<<ans<<'\n';
    }
}

