import java.math.*;
import java.util.Scanner;

public class flowergarden {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        double EPS = 1e-9;
        for (int cost = 0; cost < T; cost++) {
            int N = sc.nextInt();
            int D = sc.nextInt();
            long temp = 0;
            double total = 0;
            double prev_X = 0;
            double prev_Y = 0;
            for (int i = 0; i < N; i++) {
                double X = sc.nextInt();
                double Y = sc.nextInt();
                total += Math.sqrt((X - prev_X) * (X - prev_X) + (Y - prev_Y) * (Y - prev_Y));
                prev_X = X;
                prev_Y = Y;
                if (total - D > EPS) continue;
                else temp++;
            }

            BigInteger ANS = BigInteger.valueOf(temp);
            if (temp < 2) {
                System.out.println(0);
            } else {
                while (!ANS.isProbablePrime(10)) {
                    ANS = ANS.subtract(BigInteger.valueOf(1));
                }
                System.out.println(ANS);
            }
        }
    }
}