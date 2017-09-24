import java.util.*;
import java.math.*;
import java.io.*;
public class Main{
	static class Task{
		void solve(int testId, InputReader cin, PrintWriter cout) {
			// Write down the code you want
		}
	};
	public static void main(String args[]) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		TaskA solver = new TaskA();
		solver.solve(1, in, out);
		out.close();
	}
	static class InputReader {
		public BufferedReader reader;
		public StringTokenizer tokenizer;
		public InputReader(InputStream stream) {
			reader = new BufferedReader(new InputStreamReader(stream), 32768);
			tokenizer = null;
		}
		public String next() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					tokenizer = new StringTokenizer(reader.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return tokenizer.nextToken();
		}
		public int nextInt() {
			return Integer.parseInt(next());
		}
	}
};
// Arrays
int a[];
.fill(a[,int fromIndex,int toIndex],val);|.sort(a[, int fromIndex, int toIndex])
// String
String s;
.charAt(int i);|compareTo(String)|compareToIgnoreCase ()|contains(String)|
length ()|substring(int l, int len)
// BigInteger
.abs()|.add()|bitLength()|subtract()|divide()|remainder()|divideAndRemainder()|
modPow(b, c)|pow(int) | multiply () | compareTo () |
gcd() | intValue () | longValue () | isProbablePrime(int c) (1 - 1/2^c) |
nextProbablePrime () | shiftLeft(int) | valueOf ()
// BigDecimal
.ROUND_CEILING | ROUND_DOWN_FLOOR | ROUND_HALF_DOWN | ROUND_HALF_EVEN | ROUND_HALF_UP | ROUND_UP
.divide(BigDecimal b, int scale , int round_mode) | doubleValue () | movePointLeft(int) | pow(int) |
setScale(int scale , int round_mode) | stripTrailingZeros ()
// StringBuilder
StringBuilder sb = new StringBuilder ();
sb.append(elem) | out.println(sb)
// TODO Java STL的使用方法以及上面这些方法的检验
