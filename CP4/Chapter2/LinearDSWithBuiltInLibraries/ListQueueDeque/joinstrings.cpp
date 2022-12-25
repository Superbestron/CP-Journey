#include <iostream>
#include <queue>

using namespace std;

void process_queue(string* arr, queue<int>* q, int curr_index) {
    while (!q[curr_index].empty()) {
        int idx = q[curr_index].front();
        cout << arr[idx];
        process_queue(arr, q, idx);
        q[curr_index].pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, v1, v2, curr_index;
    cin >> n;
    string arr[n];
    queue<int> q[n];

    for (int i = 0; i < n; i++) cin >> arr[i];
    if (n == 1) {
        cout << arr[0]; // to pass 3rd test case
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> v1 >> v2;
        q[v1 - 1].push(v2 - 1);
    }
    curr_index = v1 - 1;
    cout << arr[curr_index];
    process_queue(arr, q, curr_index);
}