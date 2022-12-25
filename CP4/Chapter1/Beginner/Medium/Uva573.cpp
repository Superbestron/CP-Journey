#include <iostream>
#include <vector>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    int n,m,c,consum,device,seq=1;
    while(true){
        cin>>n>>m>>c;
        if(n==0)break;
        vector<pair<int,int>> arr;
        int curr=0,maxi=0;
        bool blown=false;
        while(n-->0){
            cin>>consum;
            arr.emplace_back(consum,0);
        }
        while(m-->0){
            cin>>device;
            pair<int,int>& p = arr[device-1];
            if(p.second==0){
                curr+=p.first;

                maxi=max(maxi,curr);
                p.second=1;
                if(curr>c) {
                    blown = true;
                    break;
                }
            }else{
                curr-=p.first;
                p.second=0;
            }
        }
        if(blown){
            cout<<"Sequence "<<seq<<endl<<"Fuse was blown."<<endl<<endl;
        }else{
            cout<<"Sequence "<<seq<<endl<<"Fuse was not blown."<<endl<<"Maximal power consumption was "<<maxi<<" amperes."<<endl<<endl;
        }
        seq++;
    }
}
