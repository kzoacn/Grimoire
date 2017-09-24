import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args) {
        InputReader cin = new InputReader(System.in);
        PrintWriter cout = new PrintWriter(System.out);
        
        
        out.close();
    }
    
  private static class InputReader {

      public BufferedReader rea;
      public StringTokenizer tok;

      public InputReader(InputStream stream) {
          rea = new BufferedReader(new InputStreamReader(stream), 32768);
          tok = null;
      }

      public String next() {
          while (tok == null || !tok.hasMoreTokens()) {
              try {
                  tok = new StringTokenizer(rea.readLine());
              } catch (IOException e) {
                  throw new RuntimeException(e);
              }
          }
          return tok.nextToken();
      }

      public int nextInt() {
          return Integer.parseInt(next());
      }
  }
    
}
public class JavaBigInteger{
	public static void main(String [] arg){
		Scanner cin=new Scanner(System.in);
		BigInteger a;
		BigInteger b=new BigInteger("101",2);
		BigDecimal c;
		a=BigInteger.valueOf(4);
		a=cin.nextBigInteger();
		b=cin.nextBigInteger(2);
		c=cin.nextBigDecimal();
		BigInteger[] Ar=new BigInteger[10];
		BigInteger[][] Arr=new BigInteger[10][10];
		int x=a.intValue();
		a=a.min(b);
		a=a.add(b);
		a=a.subtract(b);
		a=a.divide(b);
		a=a.multiply(b);
		a=a.mod(b);
		a=a.pow(b.intValue());
		a=a.gcd(b);	
		a=a.abs();
		a=a.negate();
		a=a.shiftLeft(3);
		a=a.xor(b);
		int y=a.signum();
		int l=a.bitLength();
		int bt=a.bitCount();
		boolean prim=a.isProbablePrime(50);
		boolean eq=a.equals(b);
		if(a.compareTo(b)<0){
			//	equals a.subtract(b).signum , I think.
		}
		System.out.println(b);
	}
}

//Coming soon : java stl
