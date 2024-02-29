import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class C1626A {
    public static void main(String[] arg) {
        Scanner sc = new Scanner(System.in);
        int tc = sc.nextInt();

        while (tc-- > 0) {
            String str = sc.next();
            Map<Character, Integer> map = new HashMap<>();
            for (int i = 0; i < str.length(); i++) {
                int val = map.getOrDefault(str.charAt(i), 0);
                map.put(str.charAt(i), ++val);
            }
            StringBuilder complement = new StringBuilder();
            StringBuilder test = new StringBuilder();
            for (Map.Entry<Character, Integer> entry : map.entrySet()) {
                if (entry.getValue() == 2) {
                    complement.append(entry.getKey());
                } else {
                    test.append(entry.getKey());
                }
            }
            complement.append(new String(complement));
            complement.append(test);
            System.out.println(complement);
        }
    }
}
