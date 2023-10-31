import java.util.Scanner;

public class C1626B {
    public static void main(String[] arg) {
        Scanner sc = new Scanner(System.in);
        int tc = sc.nextInt();

        while (tc-- > 0) {
            String test = sc.next();
            boolean hasFound = false;
            int sum = 0;
            int ctr = 0;
            String res;

            for (int i = test.length() - 1; i > 0; i--) {
                sum = Character.getNumericValue(test.charAt(i - 1)) + Character.getNumericValue(test.charAt(i));
                if (sum >= 10) {
                    hasFound = true;
                    ctr = i - 1;
                    break;
                }
            }
            if (hasFound) {
                String complement = String.valueOf(sum);
                String first = test.substring(0, ctr);
                String second;
                if (ctr == test.length() - 2) {
                    second = "";
                } else {
                    second = test.substring(ctr + 2);
                }
                res = first + complement + second;
            } else {
                String temp = test.substring(2);
                sum = Character.getNumericValue(test.charAt(0)) + Character.getNumericValue(test.charAt(1));
                res = sum + temp;
            }

            System.out.println(res);
        }
    }
}
