import java.util.*;

class trik {
    public static void main(String[] args) {
        Scanner sc =  new Scanner(System.in);
        String moves = sc.next();
        int length = moves.length();
        int pos = 1;

        for (int i = 0; i < length; i++) {
            char move = moves.charAt(i);
            if (move == 'A') {
                if (pos == 1) {
                    pos = 2;
                } else if (pos == 2) {
                    pos = 1;
                }
            } else if (move == 'B') {
                if (pos == 2) {
                    pos = 3;
                } else if (pos == 3) {
                    pos = 2;
                }
            } else {
                if (pos == 1) {
                    pos = 3;
                } else if (pos == 3) {
                    pos = 1;
                }
            }
        }
        System.out.println(pos);

        sc.close();
    }
}
