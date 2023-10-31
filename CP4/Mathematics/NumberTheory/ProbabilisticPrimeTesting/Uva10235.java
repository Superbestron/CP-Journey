import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNext()) {
      int N = sc.nextInt(); System.out.printf("%d is ", N);
      BigInteger BN = BigInteger.valueOf(N);
      String R = new StringBuffer(BN.toString()).reverse().toString();
      int RN = Integer.parseInt(R);
      BigInteger BRN = BigInteger.valueOf(RN);
      if (!BN.isProbablePrime(10))               // certainty 10 is enough
        System.out.println("not prime.");
      else if ((N != RN) && BRN.isProbablePrime(10))
        System.out.println("emirp.");
      else
        System.out.println("prime.");
    }
  }
}
