import java.util.*;

class parking2 {
    public static void main(String[] args) {
        Scanner sc =  new Scanner(System.in);
        int testCases = sc.nextInt();

        for (int i = 0; i < testCases; i++) {
            int stores = sc.nextInt();
            int store = sc.nextInt();
            int min = store;
            int max = store;

            for (int j = 1; j < stores; j++) {
                store = sc.nextInt();
                if (store > max) {
                    max = store;
                } else if (store < min) {

                    min = store;
                }
            }

            System.out.println(2 * (max - min));
        }
        sc.close();
    }
}
