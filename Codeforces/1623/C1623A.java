import java.util.Scanner;

public class C1623A {
    public static void main(String[] arg) {
        Scanner sc = new Scanner(System.in);
        int tc = sc.nextInt();

        while (tc-- > 0) {
            int N = sc.nextInt();
            int m = sc.nextInt();
            int rb = sc.nextInt();
            int cb = sc.nextInt();
            int rd = sc.nextInt();
            int cd = sc.nextInt();
            int dr = 1;
            int dc = 1;
            int curr_time = 0;

            while (rb != rd && cb != cd) {
                curr_time++;
                if (rb == N && dr == 1 || rb == 1 && dr == -1) {
                    dr = -dr;
                }
                if (cb == m && dc == 1 || cb == 1 && dc == -1) {
                    dc = -dc;
                }

                rb += dr;
                cb += dc;
                // System.out.println(rb);
                // System.out.println(cb);

            }
            System.out.println(curr_time);
        }
    }
}
