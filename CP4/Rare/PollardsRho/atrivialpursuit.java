import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.*;
import java.security.SecureRandom;
import java.util.HashMap;
import java.util.StringTokenizer;

class Main {
    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer rmqSt = new StringTokenizer("");

        String next() {
            while (!rmqSt.hasMoreTokens())
                try {
                    rmqSt = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                }
            return rmqSt.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }
    }

    private static final BigInteger TWO = BigInteger.valueOf(2);
    private final static SecureRandom random = new SecureRandom();
    private final static HashMap<BigInteger, Integer> g_output = new HashMap<>();
    private final static HashMap<BigInteger, Integer> l_output = new HashMap<>();
    private final static BigInteger MOD = BigInteger.valueOf(1000000007);

    private static BigInteger f(BigInteger x, BigInteger b, BigInteger n) {
        return x.multiply(x).mod(n).add(b).mod(n);     // x = (x^2 % n + b) % n
    }

    private static BigInteger rho(BigInteger n) {
        if (n.mod(TWO).compareTo(BigInteger.ZERO) == 0) return TWO;  // special
        BigInteger b = new BigInteger(n.bitLength(), random);  // rand for luck
        BigInteger x = new BigInteger(n.bitLength(), random);
        BigInteger y = x;                                    // initially y = x
        while (true) {
            x = f(x, b, n);                                           // x = f(x)
            y = f(f(y, b, n), b, n);                               // y = f(f(y))
            BigInteger d = x.subtract(y).gcd(n);                 // d = (x-y) % n
            if (d.compareTo(BigInteger.ONE) != 0)                    // if d != 1
                return d;          // d is one of the divisor of composite number n
        }
    }

    public static void pollard_rho(BigInteger n, boolean is_g) {
        if (n.compareTo(BigInteger.ONE) == 0) return;    // special case, n = 1
        if (n.isProbablePrime(10)) {
            if (is_g) g_output.put(n, g_output.getOrDefault(n, 0) + 1);
            else l_output.put(n, l_output.getOrDefault(n, 0) + 1);
            return;  // n is a prime, the only factor is n
        }
        BigInteger divisor = rho(n);   // n is a composite number, can be split
        pollard_rho(divisor, is_g);                     // recursive check to divisor
        pollard_rho(n.divide(divisor), is_g);                        // and n/divisor
    }

    public static void main(String[] args) {
        FastScanner sc = new FastScanner();
        long p = sc.nextLong();
        BigInteger P = BigInteger.valueOf(p);
        int N = sc.nextInt();
        int M = sc.nextInt();
        for (int i = 0; i < N; i++) {
            String gi = sc.next();
            BigInteger n = new BigInteger(gi);
            pollard_rho(n, true);
        }
        for (int i = 0; i < M; i++) {
            String gi = sc.next();
            BigInteger n = new BigInteger(gi);
            pollard_rho(n, false);
        }
        // make sure each output has same number of factors
        for (HashMap.Entry<BigInteger, Integer> entry : g_output.entrySet()) {
            if (!l_output.containsKey(entry.getKey())) {
                l_output.put(entry.getKey(), 0);
            }
        }
        BigInteger ANS = BigInteger.ONE;
        for (HashMap.Entry<BigInteger, Integer> entry : l_output.entrySet()) {
            if (!g_output.containsKey(entry.getKey())) {
                g_output.put(entry.getKey(), 0);
            }
            long l = g_output.get(entry.getKey());
            long r = entry.getValue();
            if (l > r) {
                ANS = BigInteger.ZERO;
                break;
            } else if (l == r) {
                continue;
            }
            if (ANS.compareTo(BigInteger.ZERO) == 0) break;
            // Inclusion exclusion principle
            // [a, b] - (a, b] - [a, b) + (a, b)
            // (a, b] because we need at least 1 prime to have a (if not GCD will not be a but a + 1)
            // [a, b) because we need at least 1 prime to have b (if not LCM will not be b but b - 1)
            BigInteger t1 = BigInteger.valueOf(r - l + 1).modPow(P, MOD);
            BigInteger t2 = BigInteger.valueOf(r - l).modPow(P, MOD).shiftLeft(1);
            BigInteger t3 = BigInteger.valueOf(r - l - 1).modPow(P, MOD);
            BigInteger sum = t1.subtract(t2).add(t3).add(MOD).mod(MOD);
            ANS = ANS.multiply(sum).mod(MOD);
        }
        System.out.println(ANS);
    }
}
