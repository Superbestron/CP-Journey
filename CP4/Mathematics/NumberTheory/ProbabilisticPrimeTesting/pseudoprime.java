import java.math.*;
import java.util.Scanner;

class pseudoprime {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            int p = sc.nextInt();
            int a = sc.nextInt();
            if (p == 0 && a == 0) return;
            BigInteger P = BigInteger.valueOf(p);
            BigInteger A = BigInteger.valueOf(a);
            if (!P.isProbablePrime(10) && (A.modPow(P, P).equals(A))) {
                System.out.println("yes\n");
            } else {
                System.out.println("no\n");
            }
        }
    }
}
