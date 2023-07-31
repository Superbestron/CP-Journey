import java.math.*;
import java.util.*;

public class primes2 {
    public static int gcd(int a, int b) {
        if (b==0) return a;
        return gcd(b, a % b);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        int[] arr = {2, 8, 10, 16};
        for (int t = 0; t < T; t++) {
            String s = sc.next();
            int num = 0;
            int denom = 0;
            for (int i = 0; i < 4; i++) {
                try {
                    BigInteger value = new BigInteger(s, arr[i]);
                    denom++;
                    if (value.isProbablePrime(10)) num++;
                } catch (Exception e) {

                }
            }
            int d = gcd(num, denom);
            System.out.println((num / d) + "/" + (denom / d));
        }
    }
}