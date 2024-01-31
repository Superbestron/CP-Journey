#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;
typedef long long ll;
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
  ll N, x, zero_count = 0, ans = 0;
  cin >> N;
  const int OFFSET = 50000;
  vi f(1 + 2 * OFFSET), A;
  for (int i = 0; i < N; i++) {
    cin >> x;
    if (x == 0) zero_count++;
    else {
      f[x + OFFSET]++;
      A.push_back(x);
    }
  }
  vi output = multiply(f, f);

  // x + x = 2x => (x + OFFSET) + (x + OFFSET) = 2(x + OFFSET)
  for (ll a : A) output[2 * (a + OFFSET)]--;
  // x + y = a => (x + OFFSET) + (y + OFFSET) = a + 2 * OFFSET
  for (ll a : A) ans += output[a + 2 * OFFSET];
  // -x + x = 0 => (-x + OFFSET) + (x + OFFSET) = 2 * OFFSET
  ans += output[2 * OFFSET] * zero_count;

  for (int i = 0; i <= 2 * OFFSET; i++) {
    if (f[i] != 0) {
      ans += f[i] * zero_count * (f[i] - 1) * 2;  // a + 0 = a or 0 + a = a
    }
  }

  // 3 zeroes
  ans += (zero_count * (zero_count - 1) * (zero_count - 2));
  cout << ans << '\n';
}
