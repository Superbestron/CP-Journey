#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;
typedef vector<int> vi;

int reverseBit(int x, int m) {
  int ret = 0;
  for (int k = 0; k < m; k++) {
    if (x & (1 << k)) ret |= 1 << (m - k - 1);
  }
  return ret;
}

// In-Place FFT
void FFT(vector<cd> &A) {
  int m = 0;
  while ((1 << m) < A.size()) m++;  // m needs to be a power of 2

  for (int k = 0; k < A.size(); k++) {
    if (k < reverseBit(k, m)) swap(A[k], A[reverseBit(k, m)]);
  }

  for (int n = 2; n <= A.size(); n <<= 1) {
    for (int k = 0; 2 * k < n; k++) {
      cd x = cd(cos(2 * M_PI * k / n), sin(2 * M_PI * k / n));
      for (int j = 0; j < A.size(); j += n) {
        cd A0_k = A[k + j], A1_k = A[k + j + n / 2];
        A[k + j] = A0_k + x * A1_k;
        A[k + j + n / 2] = A0_k - x * A1_k;
      }
    }
  }
}

void IFFT(vector<cd> &A) {
  for (auto &p : A) p = conj(p);    // complex conjugate: a + bi -> a - bi
  FFT(A);
  for (auto &p : A) p = conj(p);    // complex conjugate **not needed for our purpose**
  for (auto &p : A) p /= A.size();  // scale down (1 / n)
}

vi multiply(vi &p1, vi &p2) {
  int n = 1;                                     // n needs to be a power of 2
  while (n < p1.size() + p2.size() - 1) n <<= 1;

  vector<cd> A(p1.begin(), p1.end());            // prepare A and B for FFT calls
  vector<cd> B(p2.begin(), p2.end());
  A.resize(n);
  B.resize(n);

  FFT(A);                                        // transform
  FFT(B);

  vector<cd> C(n);                               // perform the multiplication
  for (int k = 0; k < n; k++) C[k] = A[k] * B[k];

  IFFT(C);                                       // inverse transform

  vi res;                                        // prepare output
  for (auto &p : C) res.push_back(round(p.real()));

  res.resize(p1.size() + p2.size() - 1);         // resize to original degree

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, alo, ahi;
  cin >> n;
  vi div(500001);
  for (int i = 1; i <= 500000; i++) {
    for (int j = 1; j * i <= 500000; j++) div[i * j]++;
  }
  vi output = multiply(div, div);
  for (int i = 0; i < n; i++) {
    cin >> alo >> ahi;
    int mx_w = 0, area;
    for (int j = alo; j <= ahi; j++) {
      if (output[j] > mx_w) {
        mx_w = output[j];
        area = j;
      }
    }
    cout << area << ' ' << mx_w << '\n';
  }
}
