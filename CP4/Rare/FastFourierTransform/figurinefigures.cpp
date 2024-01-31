#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;
typedef long long ll;
typedef long double ld;
typedef vector<ll> vi;

int reverseBit(int x, int m) {
  int ret = 0;
  for (int k = 0; k < m; k++) {
    if (x & (1 << k)) ret |= 1 << (m - k - 1);
  }
  return ret;
}

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
  int N, x, mn = 1e9, mx = 0, distinct = 0;
  ld sum = 0, freq = 0;  // sum is very huge so use ld
  cin >> N;
  vi f(60001);
  for (int i = 0; i < N; i++) {
    cin >> x;
    f[x]++;
  }
  vi output = f;
  for (int i = 0; i < 3; i++) {
    output = multiply(output, f);
  }
  for (int i = 0; i < output.size(); i++) {
    if (output[i]) {
      mn = min(mn, i);
      mx = max(mx, i);
      sum += output[i] * i;
      freq += output[i];
      distinct++;
    }
  }
  cout << mx << ' ' << mn << ' ' << distinct << ' ' << setprecision(4) << fixed << sum / freq << '\n';
}
