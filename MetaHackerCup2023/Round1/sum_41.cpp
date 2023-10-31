#include <bits/stdc++.h>
using namespace std;

int T, P;
vector<vector<int>> v;
vector<long long> product;

void printArray(int p[], int n) {
  vector<int> t;
  long long pro = 1;
  for (int i = 0; i < n; i++) {
    t.push_back(p[i]);
    pro *= p[i];
  }
  v.push_back(std::move(t));
  product.push_back(pro);
}

void printAllUniqueParts(int n) {
  int p[n]; // An array to store a partition
  int k = 0; // Index of last element in a partition
  p[k] = n; // Initialize first partition as number itself

  // This loop first prints current partition then generates next
  // partition. The loop stops when the current partition has all 1s
  while (true) {
    // print current partition
    printArray(p, k + 1);

    // Generate next partition

    // Find the rightmost non-one value in p[]. Also, update the
    // rem_val so that we know how much value can be accommodated
    int rem_val = 0;
    while (k >= 0 && p[k] == 1) {
      rem_val += p[k];
      k--;
    }

    // if k < 0, all the values are 1 so there are no more partitions
    if (k < 0) return;

    // Decrease the p[k] found above and adjust the rem_val
    p[k]--;
    rem_val++;


    // If rem_val is more, then the sorted order is violated. Divide
    // rem_val in different values of size p[k] and copy these values at
    // different positions after p[k]
    while (rem_val > p[k]) {
      p[k + 1] = p[k];
      rem_val = rem_val - p[k];
      k++;
    }

    // Copy rem_val to next position and increment position
    p[k + 1] = rem_val;
    k++;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  printAllUniqueParts(41);
  for (int i = 1; i <= T; i++) {
    cin >> P;
    cout << "Case #" << i << ": ";
    int mini = INT32_MAX, idx = -1;
    for (int j = 0; j < v.size(); j++) {
      if (product[j] == P) {
        if (v[j].size() < mini) {
          mini = v[j].size();
          idx = j;
        }
      }
    }
    if (idx == -1) cout << -1 << '\n';
    else {
      cout << v[idx].size() << ' ';
      for (int &k : v[idx]) cout << k << ' ';
      cout << '\n';
    }
  }
}