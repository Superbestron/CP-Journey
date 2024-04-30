/*** Java version ***/

//import java.math.*;
//import java.security.SecureRandom;
//
//class Pollardsrho {
//    private static final BigInteger TWO = BigInteger.valueOf(2);
//    private final static SecureRandom random = new SecureRandom();
//
//    private static BigInteger f(BigInteger x, BigInteger b, BigInteger n) {
//        return x.multiply(x).mod(n).add(b).mod(n);     // x = (x^2 % n + b) % n
//    }
//
//    private static BigInteger rho(BigInteger n) {
//        if (n.mod(TWO).compareTo(BigInteger.ZERO) == 0) return TWO;  // special
//        BigInteger b = new BigInteger(n.bitLength(), random);  // rand for luck
//        BigInteger x = new BigInteger(n.bitLength(), random);
//        BigInteger y = x;                                    // initially y = x
//        while (true) {
//            x = f(x, b, n);                                           // x = f(x)
//            y = f(f(y, b, n), b, n);                               // y = f(f(y))
//            BigInteger d = x.subtract(y).gcd(n);                 // d = (x-y) % n
//            if (d.compareTo(BigInteger.ONE) != 0)                    // if d != 1
//                return d;          // d is one of the divisor of composite number n
//        }
//    }
//
//    public static void pollard_rho(BigInteger n) {
//        if (n.compareTo(BigInteger.ONE) == 0) return;    // special case, n = 1
//        if (n.isProbablePrime(10)) {
//            System.out.println(n);
//            return;  // n is a prime, the only factor is n
//        }
//        BigInteger divisor = rho(n);   // n is a composite number, can be split
//        pollard_rho(divisor);                     // recursive check to divisor
//        pollard_rho(n.divide(divisor));                        // and n/divisor
//    }
//
//    public static void main(String[] args) {
//        BigInteger n = new BigInteger("124590589650069032140693");       // Big
//        pollard_rho(n);       // factorize n to 7 x 124418296927 x 143054969437
//    }
//}

#include <bits/stdc++.h>
#include "PrimalityCheck.cpp"
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef unsigned long long ull;

ull pollard(ull n) {
  auto f = [n](ull x) { return modmul(x, x, n) + 1; };
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while (t++ % 40 || gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return gcd(prd, n);
}
vector<ull> factor(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}
