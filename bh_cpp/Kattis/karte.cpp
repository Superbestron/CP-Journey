#include<bits/stdc++.h>
using namespace std;

int main(){
    unordered_map<char,unordered_set<int>> m;
    m.insert(pair{'P',unordered_set<int>{}});
    m.insert(pair{'K',unordered_set<int>{}});
    m.insert(pair{'H',unordered_set<int>{}});
    m.insert(pair{'T',unordered_set<int>{}});
    char x,y,z;
    int val;
    while (true){
        cin >> x >> y >> z;
        if (cin.eof()) break;
        val = y == '0' ? z - '0' : z - '0' + 10;
        if (m.at(x).find(val) != m.at(x).end()){
            cout << "GRESKA";
            return 0;
        }
        m.at(x).insert(val);
    }
    cout << 13 - m.at('P').size() << " " << 13 - m.at('K').size() << " " << 13 - m.at('H').size() << " " << 13 - m.at('T').size();
}
