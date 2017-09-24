import java.io.*;
import java.math.*;
import java.util.*;

public class Main{
	public static long max(long a,long b){
		if(a>b)return a;
		return b;
	}
	public static long Calc(long A, int x){
		long Ret = (A / (1L << x)) * (1L << (x - 1));
	
		Ret += max(A % (1L << x) - (1L << (x - 1)) + 1, 0L);
	
		return Ret;
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

      public long nextLong() {
          return Long.parseLong(next());
      }      
  }
	
	public static void main(String arg[]){
		InputReader cin = new InputReader(System.in);
		//Scanner cin = new Scanner(System.in);
		int N = 70;

		long k[] = new long[N];
		int n;

		while(true){
			n=cin.nextInt();
			if (n == 0) break;
		
			for (int i = 1; i <= n; i ++){
				k[i]=cin.nextLong();
				//System.out.println(k[i]);
				
			}
		
			long Len;
			BigInteger Sum;
			long A, B;
			long AnsA = -1, AnsB = -1;
			int Ans = 0;
		
			for (int i = -1; i <= 1; i++){
				Len = k[1] * 2 + i;
				
				if(Len<=0)continue;
			
				Sum = BigInteger.ZERO;
				for (int j = 1; j <= n; j++){
					Sum = Sum.add(BigInteger.valueOf(1L << (j - 1)) .multiply(BigInteger.valueOf(k[j])));
				}
				//System.out.println(Sum);
			
			/*
						Sum = 0;
			for (int j = 1; j <= n; j++)
				Sum += (1LL << (j - 1)) * k[j];
			
			
			LL x = Len;
			
			
			if ((2 * Sum) % Len > 0) continue;
			
			LL y = (2 * Sum) / Len;
			*/
				long x = Len;
			

				//System.out.println("len="+Len);					
								
				if ((Sum.multiply(BigInteger.valueOf(2))) .mod (BigInteger.valueOf(Len)).compareTo(BigInteger.ZERO) > 0) continue;
			
				long y = Sum.multiply(BigInteger.valueOf(2)).divide(BigInteger.valueOf(Len)).longValue();
			
				if ((y - x + 1) % 2 > 0) continue;
			
				A = (y - x + 1) / 2;
			
				if ((x + y - 1) % 2 > 0) continue;
			
				B = (x + y - 1) / 2;
			
				if (A < 1 || A > (long)1e18) continue;
				if (B < 1 || B > (long)1e18) continue;
			
				int flag = 1;
			
				long Cnt;
				long Cnt_B;
				long Cnt_A;
			
				//printf("%lld %lld\n", A, B);
			
				for (int j = 1; j <= n; j++){
				
					Cnt_B = Calc(B, j);
					Cnt_A = Calc(A - 1, j);
				
				
				
					if (Cnt_B - Cnt_A != k[j]){
						flag = 0;
						break;
					}
				}
			
				if (flag==1){
					Ans++;
					//printf("%lld %lld\n", A, B);
					//System.out.println(A+" "+B);
					AnsA = A;
					AnsB = B;
				}
			}
		
			if (Ans == 0) System.out.println("None");//puts("None");
			else
			if (Ans == 1)
				System.out.println(AnsA+" "+AnsB);//cout << AnsA << ' ' << AnsB << endl;
			else
				System.out.println("Many");//puts("Many");
		}
		
	}
}
