#include <bits/stdc++.h>

using namespace std;

class Arr {
public:
    int size{},ba{},dimen{};
    string name;
    vector<pair<int,int>> bounds;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,r,dimen,lb,ub,input,ans,sum;
    string name;
    cin>>n>>r;
    unordered_map<string,Arr> m;
    while (n-->0) {
        Arr arr;
        cin>>arr.name>>arr.ba>>arr.size>>arr.dimen;
        dimen=arr.dimen;
        while (dimen-->0) {
            cin>>lb>>ub;
            arr.bounds.emplace_back(lb,ub);
        }
        m[arr.name]=arr;
    }
    while (r-->0) {
        cin>>name;
        Arr arr = m[name];
        ans = arr.ba;
        cout<<name<<'[';
        bool first = true;
        for (int i = 0; i < arr.dimen; i++) {
            cin>>input;
            if (!first) cout<<", ";
            first = false;
            cout<<input;
            sum=(input-arr.bounds[i].first);
            for (int j = i + 1; j < arr.dimen; j++) {
                sum*=(arr.bounds[j].second-arr.bounds[j].first+1);
            }
            ans+=(sum*arr.size);
        }
        cout<<"] = "<<ans<<endl;
    }
}
