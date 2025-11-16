#include <bits/stdc++.h>
using namespace std;

void solution(int n, const vector<int>& flows) {
    int arr[flows.size() + 1];
    vector<int> ansArr;
    int ctr = 0;
    fill(arr, arr + flows.size() + 1, 0);
    int next; int count;
    for (int i = 1; i <= flows.size(); i++) {
        if (arr[i] == 0) {
            count = 1;
            arr[i] = ctr;
            next = flows[i - 1];
            while (next != i) {
                arr[next] = ctr;
                next = flows[next - 1];
                count++;
            }
            ansArr.push_back(count);
            ctr++;
        }
    }
    string ans;
    for (int i = 1; i <= flows.size(); i++){
        ans += to_string(ansArr[arr[i]]);
        ans += " ";
    }
    cout << ans << '\n';
}

int main() {
    int n, q;
    cin >> n;
    vector<int> flows;
    for(int i = 0; i < n; i++) {
        cin >> q;
        flows.push_back(q);
    }
    solution(n,flows);
}
