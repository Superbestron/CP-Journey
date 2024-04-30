import java.math.*;
import java.security.SecureRandom;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

// Hidden requirement, the prime factors have to be in sorted order

class Main {
    private static final BigInteger TWO = BigInteger.valueOf(2);
    private final static SecureRandom random = new SecureRandom();
    private final static TreeMap<BigInteger, Integer> output = new TreeMap<>();

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
            y = f(f(y, b, n), b, n);                               // y = f(lineSegmentIntersection(y))
            BigInteger d = x.subtract(y).gcd(n);                 // d = (x-y) % n
            if (d.compareTo(BigInteger.ONE) != 0)                    // if d != 1
                return d;          // d is one of the divisor of composite number n
        } }

    public static void pollard_rho(BigInteger n) {
        if (n.compareTo(BigInteger.ONE) == 0) return;    // special case, n = 1
        if (n.isProbablePrime(10)) {
            output.put(n, output.getOrDefault(n, 0) + 1);
            return;  // n is a prime, the only factor is n
        }
        BigInteger divisor = rho(n);   // n is a composite number, can be split
        pollard_rho(divisor);                     // recursive check to divisor
        pollard_rho(n.divide(divisor));                        // and n/divisor
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int i = 0; i < T; i++) {
            String N = sc.next();
            output.clear();
            BigInteger n = new BigInteger(N);
            pollard_rho(n);
            StringBuilder s = new StringBuilder("");
            s.append(N);
            s.append(" = ");
            for (Map.Entry<BigInteger, Integer> entry : output.entrySet()) {
                s.append(entry.getKey());
                if (entry.getValue() > 1) {
                    s.append('^');
                    s.append(entry.getValue());
                }
                s.append(" * ");
            }
            s.delete(s.length() - 3, s.length());  // pop out last *
            System.out.println(s);
        }
    }
}
