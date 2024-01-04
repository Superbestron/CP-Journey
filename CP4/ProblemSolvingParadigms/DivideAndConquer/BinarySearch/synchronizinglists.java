import java.util.*;

public class synchronizinglists {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int len = sc.nextInt();
        while (true) {
            int[] first = new int[len]; // store numbers
            int[] second = new int[len]; // store counts
            Map<Integer, Integer> indexMap = new HashMap<>();

            for (int i = 0; i < len; i++) {
                int next = sc.nextInt();
                indexMap.put(next, i);
                first[i] = next;
            }
            for (int i = 0; i < len; i++) {
                second[i] = sc.nextInt();
            }
            Arrays.sort(first);
            Arrays.sort(second);
            int[] newSecond = new int[len];
            for (int i = 0; i < len; i++) newSecond[indexMap.get(first[i])] = second[i];
            for (int i : newSecond) System.out.println(i);
            len = sc.nextInt();

            if (len == 0) break;
            else System.out.print("\n");


        }
    }
}
