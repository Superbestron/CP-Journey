import java.util.Scanner;
import java.lang.Math;

class Main {
    static final int CAPACITY = 12;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int num_matches_without_N = sc.nextInt();

        for (int i = 0; i < num_matches_without_N; i++) {
            String str = sc.next();
            StringBuilder string = new StringBuilder(str);
            int pebbles = 0;
            for (int j = 0; j < CAPACITY; j++) {
                if (string.charAt(j) == 'o') {
                    pebbles++;
                }
            }
            int complement = minPebbles(string, pebbles);
            System.out.println(complement);
        }
    }

    public static int minPebbles(StringBuilder original, int pebbles) {
        //System.out.println("original:" + original);
        //System.out.println("pebbles:" + pebbles);
        int minimum = pebbles;

        for (int j = 0; j < CAPACITY; j++) {
            StringBuilder str = new StringBuilder(original);
            int currentPebbles = pebbles;
            int currentMinimum = 9999;

            int complement = canMove(j, original);

            if (complement == 1) {
                str.setCharAt(j, '-');
                str.setCharAt(j - 1, '-');
                str.setCharAt(j - 2, 'o');
                currentPebbles--;

                currentMinimum = minPebbles(str, currentPebbles);
                //System.out.println(currentMinimum);
            } else if (complement == 2) {
                str.setCharAt(j, '-');
                str.setCharAt(j + 1, '-');
                str.setCharAt(j + 2, 'o');
                currentPebbles--;
                currentMinimum = minPebbles(str, currentPebbles);
                //System.out.println(currentMinimum + "rs");
            } else if (complement == 3) {
                StringBuilder str1 = new StringBuilder(str);
                StringBuilder str2 = new StringBuilder(str);
                int current1 = currentPebbles;
                int current2 = currentPebbles;
                str1.setCharAt(j, '-');
                str1.setCharAt(j - 1, '-');
                str1.setCharAt(j - 2, 'o');
                current1--;
                int place1 = minPebbles(str1, current1);
                str2.setCharAt(j, '-');
                str2.setCharAt(j + 1, '-');
                str2.setCharAt(j + 2, 'o');
                current2--;
                int place2 = minPebbles(str2, current2);
                currentMinimum = Math.min(place1, place2);
            }
            if (currentMinimum < minimum) {
                minimum = currentMinimum;
            }
        }
        return minimum;
    }

    // 0 = cant move, 1 = ls, 2 = rs, 3 = ls and rs
    public static int canMove(int index, StringBuilder str) {
        int number = 0;
        if (str.charAt(index) == 'o') {
            // check move ls
            if (index >= 2) {
                if (str.charAt(index - 1) == 'o' && str.charAt(index - 2) == '-') {
                    number += 1;
                }
            }
            // check move rs
            if (index < str.length() - 2) {
                if (str.charAt(index + 1) == 'o' && str.charAt(index + 2) == '-') {
                    number += 2;
                }
            }
        }
        return number;
    }
}

