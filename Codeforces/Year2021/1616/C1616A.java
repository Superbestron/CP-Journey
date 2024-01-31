import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class C1616A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int tc = sc.nextInt();

        while (tc-- > 0) {
            int N = sc.nextInt();
            Map<Integer, Integer> map = new HashMap<>();

            while (N-- > 0) {
                int x = sc.nextInt();
                if (x < 0) {
                    x = -x;
                }
                int val = map.getOrDefault(x, 0);
                map.put(x, ++val);
            }

            int complement = 0;
            for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
                if (entry.getKey() == 0) {
                    complement += 1;
                    continue;
                }
                complement += Math.min(entry.getValue(), 2);
            }
            System.out.println(complement);
        }
    }
}
