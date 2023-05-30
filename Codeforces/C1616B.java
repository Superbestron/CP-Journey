import java.util.Scanner;

public class C1616B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int tc = sc.nextInt();

        while (tc-- > 0) {
            int n = sc.nextInt();
            sc.nextLine();
            String str = sc.nextLine();
            char c = '{';
            int i = 0;
            if (str.length() >= 2) {
                if (str.charAt(0) == str.charAt(1)) {
                    System.out.println(str.substring(0, 2));
                    continue;
                }
            }
            while (i < n) {
                char curr = str.charAt(i);
                // if curr letter is greater than prev, cfm dw take
                if (curr <= c) {
                    c = curr;
                } else {
                    break;
                }
                i++;
            }
            if (i == 0) i = n;

            StringBuilder complement = new StringBuilder(str.substring(0, i));
            StringBuilder rev = new StringBuilder(complement).reverse();
            complement.append(rev);
            System.out.println(complement);
        }
    }
}
