#include <bits/stdc++.h>

int main() {
    int n,m,c,sequence = 1,maxpower,total;
    bool blown;
    while(scanf("%d %d %d",&n,&m,&c) != EOF)  {
        if(n == 0 && m == 0 && c == 0) break;
        maxpower = total = 0;
        blown = false;
        int values[n];
        bool status[n];
        for(int i=0;i<n;i++) {
            scanf("%d",&values[i]);
            status[i] = false;
        }
        for(int i=0;i<m;i++) {
            scanf("%d",&n);
            if(!status[n-1]) {
                total += values[n-1];
                status[n-1] = !status[n-1];
            }
            else {
                total -= values[n-1];
                status[n-1] = !status[n-1];
            }
            if(total > c) blown = true;
            else {
                if(total > maxpower) maxpower = total;
            }
        }
        if(blown) printf("Sequence %d\nFuse was blown.\n\n",sequence);
        else printf("Sequence %d\nFuse was not blown.\nMaximal power consumption was %d amperes.\n\n",sequence,maxpower);
        sequence++;
    }
    return 0;
}