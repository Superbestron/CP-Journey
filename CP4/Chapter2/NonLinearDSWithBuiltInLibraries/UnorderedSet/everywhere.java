import java.util.*;

class everywhere {
    public static void main(String[] args) {
        Scanner sc =  new Scanner(System.in);
        int t = sc.nextInt();
        for (int i = 0; i < t; i++) {
            int n = sc.nextInt();
            Set<String> set = new HashSet<String>();
            for (int j = 0; j < n; j++) {
                set.add(sc.next());
            }
            System.out.println(set.size());
        }
        sc.close();
    }
}