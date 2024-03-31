import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            String s = sc.nextLine();
            System.out.println(s.replaceAll("[^a-zA-Z]+", " ").trim().split(" ").length);
        }
    }
}
