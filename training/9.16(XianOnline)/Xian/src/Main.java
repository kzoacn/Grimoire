import java.util.*;
import java.math.*;

public class Main {
	static public void main(String[] arg) {
		BigDecimal ttt = BigDecimal.valueOf(0);
		for (int i = 1; i < 15; ++i) {
			ttt = ttt.divide(BigDecimal.valueOf(1000000000), 50, BigDecimal.ROUND_DOWN);
		}
		//System.out.println("asdf");
		Scanner cin = new Scanner(System.in);
		int n;
		String s;
		boolean[] fir = new boolean[2];
		while (cin.hasNext()) {
			fir[0] = fir[1] = false;
			n = cin.nextInt();
			BigDecimal ans = new BigDecimal("0.0");
			for (int i = 1; i <= n; ++i) {
				s = cin.next();
//				fir[(int)s.charAt(0) - (int)'0'] = true;
				int l = s.length();
				int j = 0;
				BigDecimal tmp = new BigDecimal("2.0");
				BigDecimal two = tmp;
				while (j < l && s.charAt(j) != '(') {
					tmp = tmp.divide(two, 200, BigDecimal.ROUND_DOWN);
					if (s.charAt(j) == '0') {
						ans = ans.add(tmp);						
					} else {
						ans = ans.subtract(tmp);
					}
					++j;
				}
				//System.out.println(ans + " " + tmp + " " + ttt);
				if (j < l && s.charAt(j) == '(') {
					if (s.charAt(j + 2) == ')') {
						if (s.charAt(j + 1) == '0') {
							ans = ans.add(tmp);
							ans = ans.subtract(ttt);
						} else {
							ans = ans.subtract(tmp);
							ans = ans.add(ttt);
						}
						continue;
					}
					++j;
					int k = j;
					while (s.charAt(k) != ')') {
						++k;
					}
					tmp = tmp.divide(BigDecimal.valueOf(((long)(1) << (k - j)) - 1), 200, BigDecimal.ROUND_DOWN);
				//System.out.println("tmp:  " + j + " " + k + " " + tmp);
					for (int t = j; t < k; ++t) {
						if (s.charAt(t) == '0') {
							ans = ans.add(tmp.multiply(BigDecimal.valueOf((long)(1) << (k - t - 1))));						
						} else {
							ans = ans.subtract(tmp.multiply(BigDecimal.valueOf((long)(1) << (k - t - 1))));
						}
					}
				}
				System.out.println(ans);
			}
			
			BigDecimal eps = BigDecimal.valueOf(1);
			BigDecimal eps1 = BigDecimal.valueOf(-1);
			for (int i = 1; i < 11; ++i) {
				eps = eps.divide(BigDecimal.valueOf(1000000000), 200, BigDecimal.ROUND_DOWN);
				eps1 = eps1.divide(BigDecimal.valueOf(1000000000), 200, BigDecimal.ROUND_DOWN);
			}
			if (fir[0] == false && fir[1] == true) {
				System.out.println("1 wins");
				continue;
			}
			if (fir[1] == false && fir[0] == true) {
				System.out.println("0 wins");
				continue;
			}
			//System.out.println(ans + " " + eps + ans.compareTo(eps));
			if (ans.compareTo(eps) == 1) {
				System.out.println("0 wins");
			} else {
				if (ans.compareTo(eps1) == -1) {
					System.out.println("1 wins");
				} else {
					System.out.println("tie");
				}
			}
		}
	} 
}


