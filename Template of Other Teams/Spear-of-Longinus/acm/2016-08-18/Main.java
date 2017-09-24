import java.io.*;
import java.math.*;
import java.util.*;

public class Main{

	public static void main(String arg[]){
		Scanner cin = new Scanner(System.in);
		int n,m,k,c,l;
		n=cin.nextInt();
		m=cin.nextInt();
		k=cin.nextInt();
		c=cin.nextInt();
		l=cin.nextInt();
		String[] s =new String[50];
		for(int i=0;i<n;i++){
			s[i]=cin.next();
		}
		BigInteger son=BigInteger.ZERO;
		BigInteger mom=BigInteger.ONE;
		while(c-->0){
		
		
			String str;
			str=cin.next();
			BigInteger money=cin.nextBigInteger();
			BigInteger tmp=money;
			for(int i=0;i<n;i++){
				int cnt=0;
				for(int j=0;j<m;j++){
					if(s[i].charAt(j)==str.charAt(i)||str.charAt(i)=='*')
						cnt++;
				}
				tmp=tmp.multiply(BigInteger.valueOf(cnt));
			}
			son=son.add(tmp);		
		}
		
		
		for(int i=0;i<n;i++){
			mom=mom.multiply(BigInteger.valueOf(m));
		}
		
		son=son.subtract(mom);
		if(son.compareTo(BigInteger.ZERO)<=0){
			System.out.println("0/1");
			System.out.println(0);
		}else{
			BigInteger d = son.gcd(mom);
			son=son.divide(d);
			mom=mom.divide(d);
			System.out.println(son+"/"+mom);
			System.out.println(1);
			System.out.println(1);
		}
	}
	
}	
