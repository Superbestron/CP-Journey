#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    string name,space="         ";
    unordered_map<char,int> m;
    for (int i = 'A'; i <= 'Z'; i++) {
        if (i == 'B' || i == 'P' || i == 'F' || i == 'V') {
            m[i]=1;
        } else if (i == 'C' || i == 'S' || i == 'K' || i == 'G' || i == 'J' || i == 'Q' || i == 'X' || i == 'Z') {
            m[i]=2;
        } else if (i == 'D' || i == 'T') {
            m[i]=3;
        } else if (i == 'L') {
            m[i]=4;
        } else if (i == 'M' || i == 'N') {
            m[i]=5;
        } else if (i == 'R') {
            m[i]=6;
        } else {
            m[i]=0;
        }
    }

    name+=space+"NAME";
    for (int i = 14; i < 35; i++) {
        name+=' ';
    }
    cout<<name<<"SOUNDEX CODE"<<endl;

    while (cin>>name) {
        string ans;
        char prev=name[0];
        ans += name[0];
        for (int i = 1; i < name.size(); i++) {
            if (m[name[i]]!=m[prev] && m[name[i]] != 0) {
                ans+=static_cast<char>(m[name[i]] + '0');
            }
            prev=name[i];
            if (ans.size() == 4) {
                break;
            }
        }
        if (ans.size()<4) {
            for (int i = ans.size(); i < 4; i++) {
                ans+='0';
            }
        }
        for (int i = name.size() + 9; i < 34; i++) {
            name+=' ';
        }
        cout<<space<<name<<ans<<endl;
        if (cin.eof()) break;
    }
    cout<<"                   END OF OUTPUT"<<endl;
}
