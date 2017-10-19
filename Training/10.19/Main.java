import java.util.*;
import java.io.*;
import java.math.*;

public class Main{
	public static BigInteger ans=BigInteger.ZERO;
	public static BigInteger four=new BigInteger("4");
	public static BigInteger three=new BigInteger("3");
	public static BigInteger two=new BigInteger("2");
	public static BigInteger one=new BigInteger("1");
	public static BigInteger zero=new BigInteger("0");
	public static int[] a;
	public static BigInteger[] f;
	
	public static BigInteger solve(int n) {
		if (n == 1) {
			if (a[1] == 1) {
				return three;
			} else {
				return two;
			}
		}
		BigInteger ret = zero;
		if (a[n * 2 - 1] == n * 2 - 1) {
			ret = ret.add(f[n + 1]);
			//ret = ret.add((f[n].subtract(one)).multiply(three));
			//swap(a[n * 2 - 3], a[n * 2 - 2]);
			//int tmp = a[n * 2 - 3];
			//a[n * 2 - 3] = a[n * 2 - 2];
			//a[n * 2 - 2] = tmp;
			ret = ret.add(solve(n - 1));
			return ret;
		} else {
			ret = ret.add(f[n]);
			int tmp = a[n * 2 - 3];
			a[n * 2 - 3] = a[n * 2 - 2];
			a[n * 2 - 2] = tmp;
			ret = ret.add(solve(n - 1));
			return ret;
		}
	}
	
	public static void main(String arg[]){
		Scanner cin=new Scanner(System.in);
		int n=cin.nextInt();
		a=new int[2*n+10];
		for(int i=1;i<=n*2;i++){
			a[n * 2 - i + 1]=cin.nextInt();
		}
		f = new BigInteger[2 * n + 10];
		f[0] = one;
		for (int i = 1; i <= n + n; ++i) {
			f[i] = f[i - 1].multiply(two);
		}
		
		/*BigInteger f=BigInteger.ZERO;
		BigInteger four=new BigInteger("4");
		BigInteger three=new BigInteger("3");
		BigInteger two=new BigInteger("2");
		for(int i=1;i<=n*2;i+=2){
			if(a[i]==2*(n-i+1)&&a[i+1]==2*(n-i+1)-1){
				f=f.multiply(four).add(three);
			}else{
				f=f.multiply(two).add(two);
			}
		}
		System.out.println(f);*/
		System.out.println(solve(n));
	}
}
