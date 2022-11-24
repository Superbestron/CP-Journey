#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
using namespace std;

void solution(int n, vector<string> employees, vector<vector<int>> shifts) {
    vector<int> time;
    vector<unordered_set<string>> arr;
    for (size_t i = 0; i < 22; i++){
        unordered_set<string> temp;
        arr.push_back(temp);
    }

    for (size_t i = 0; i < employees.size(); i++) {
        for (int j : shifts[i]) {
            arr[j].insert(employees[i]);
        }
    }

    int start = 0; int count = 0;
    set<string> curr;
    string toPrint[22];
    for (size_t i = 0; i < arr.size(); i++){
        if (!arr[i].empty()){
            if (start != 0) {
                string str = to_string(start) + ' ' + to_string(i) + ' ' + to_string(curr.size());
                for (const string& name : curr){
                    str += ' ' + name;
                }
                toPrint[i] = str;
                if (curr.empty()) {
                    toPrint[i] += ' ';
                }
                count++;
            }
            start = i;
            for (const string& str : arr[i]){
                if (curr.count(str) == 1){
                    curr.erase(str);
                } else {
                    curr.insert(str);
                }
            }
        }
    }
    cout << count << '\n';
    for (const string& str : toPrint) {
        if (!str.empty()) cout << str << '\n';
    }
}

//int main() {
//    int n;
//    cin >> n;
//
//    vector<string> employees;
//    string name;
//    for(int i = 0; i < n; i++){
//        cin >> name;
//        employees.push_back(name);
//    }
//
//    vector<vector<int>> shifts;
//    vector<int> shift(2);
//    for (int i = 0; i < n; i++) {
//        cin >> shift[0] >> shift[1];
//        shifts.push_back(shift);
//    }
//
//    solution(n, employees, shifts);
//}
