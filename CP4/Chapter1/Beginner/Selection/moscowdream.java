import java.util.Scanner;
import java.lang.Math;

class Moscow_Dream {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            int temp = sc.nextInt();
            if (temp == 0) {
                System.out.println("NO");
                return;
            }
            sum += temp;
        }
        int last = sc.nextInt();
        if (sum < last || last < 3) {
            System.out.println("NO");
            return;
        }
        System.out.println("YES");
    }
}

