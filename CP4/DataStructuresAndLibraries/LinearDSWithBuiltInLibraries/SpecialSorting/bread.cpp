#include <iostream>
#include <vector>

using namespace std;

int merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left, j = mid, k = left, inv_count = 0;
    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else {
            temp[k++] = arr[j++];
            inv_count += mid - i;
        }
    }
    while (i <= mid - 1) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left; i <= right; i++) arr[i] = temp[i];
    return inv_count;
}

int merge_sort(vector<int>& arr, vector<int>& temp, int left, int right) {
    int mid, inv_count = 0;
    if (right > left) {
        mid = (right + left) / 2;
        inv_count += merge_sort(arr, temp, left, mid);
        inv_count += merge_sort(arr, temp, mid + 1, right);
        inv_count += merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, i1 = 0, i2 = 0;
    cin >> n;
    vector<int> v1(n), temp(n), v2(n);
    for (int i = 0; i < n; i++) cin >> v1[i];
    for (int i = 0; i < n; i++) cin >> v2[i];
    i1 = merge_sort(v1, temp, 0, n - 1);
    i2 = merge_sort(v2, temp, 0, n - 1);
    if (abs(i1 - i2) % 2 == 0) cout << "Possible";
    else cout << "Impossible";
}
