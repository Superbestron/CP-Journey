import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class C1616C {
    public static class Solution {
        int len;
        int pos;
        double step;
        Solution(int len, int pos, double step) {
            this.len = len;
            this.pos = pos;
            this.step = step;
        }
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        int tc = sc.nextInt();

        while (tc-- > 0) {
            int n = sc.nextInt();
            int[] arr = new int[n];
            for (int i = 0; i < n; i++) {
                arr[i] = sc.nextInt();
            }

            if (n <= 2) {
                System.out.println(0);
                continue;
            }

            Solution best = new Solution(-1, 0, 0 );

            for (int i = 1; i < arr.length; ++i) {
                Map<Double, Integer> bestForStep = new HashMap<>();
                for (int j = 0; j < i; ++j) {
                    double step = (arr[i] - arr[j]) / (double) (i - j);
                    // This j gives an integer step size: record that j lies on this AP
                    int val = bestForStep.getOrDefault(step, 0);
                    ++val;
                    int len = val;
                    bestForStep.put(step, val);
                    // int len = ++bestForStep[step];
                    if (len > best.len) {
                        best.len = len;
                        best.pos = i;
                        best.step = step;
                    }
                }
            }
            ++best.len;
            System.out.println(n - best.len);
        }

    }
}
