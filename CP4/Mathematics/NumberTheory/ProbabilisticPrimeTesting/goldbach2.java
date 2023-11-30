import java.math.*;
import java.util.*;

public class goldbach2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        boolean[] arr = new boolean[32000];
        for (int i = 3; i < 32000; i += 2) {
            BigInteger x = BigInteger.valueOf(i);
            arr[i - 1] = x.isProbablePrime(10);
        }
        for (int cost = 0; cost < T; cost++) {
            int N = sc.nextInt();
            List<String> ls = new ArrayList<>();
            if (N == 4) {
                ls.add("2+2");
            } else {
                for (int i = 3; i <= N / 2; i += 2) {
                    if (arr[i - 1] && arr[N - i - 1]) {
                        ls.add(i + "+" + (N - i));
                    }
                }
            }
            System.out.println(N + " has " + ls.size() + " representation(s)");
            for (String s : ls) {
                System.out.println(s);
            }
            System.out.println();
        }
    }
}