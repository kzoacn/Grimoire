import java.util.*;
import java.math.*;
import java.io.*;
import java.lang.*;

public class Main{

	public static BigInteger S,sum;
	public static BigInteger calc(BigInteger mid,BigInteger[] o,BigInteger[] p,int sz){
		BigInteger s=BigInteger.ZERO;
		for(int i=0;i<sz;i++){
			s=s.add(o[i].multiply(mid.pow(p[i].intValue())));
			if(s.compareTo(S)>0)
				return s;
		}
		return s;
	}
	public static void main(String[] arg){
		Scanner cin=new Scanner(System.in);
		int n=cin.nextInt();
		S=BigInteger.ZERO;
		sum=BigInteger.ZERO;
		BigInteger[] o,p;
		int sz=0;
		o=new BigInteger[n];
		p=new BigInteger[n];
		for(int i=0;i<n;i++){
			BigInteger tmpo,tmpp;
			tmpp=cin.nextBigInteger();
			tmpo=cin.nextBigInteger();
			
			if(tmpo.signum()>0)
				S=S.add(tmpo);
			else{
				tmpo=tmpo.multiply(BigInteger.valueOf(tmpo.signum()));
				sum=sum.add(tmpo);
				o[sz]=tmpo;
				p[sz]=tmpp;
				sz++;
			}
		}
		BigInteger mxP=BigInteger.ZERO;
		for(int i=0;i<sz;i++){
			if(mxP.compareTo(p[i])<0)
				mxP=p[i];
		}
		System.out.println(S+" "+sum);
		if(S.compareTo(sum)==0){
			System.out.println("Yes 1");
			return ;
		}
		
		
		BigInteger two=new BigInteger("2");
		if(mxP.compareTo(new BigInteger("200"))<0){
			BigInteger l=BigInteger.ONE;
			BigInteger r=BigInteger.valueOf(10).pow(30);
			
			while(l.compareTo(r)<0){
				BigInteger mid=l.add(r).divide(two);
				if(calc(mid,o,p,sz).compareTo(S)<0)
					l=mid.add(BigInteger.ONE);
				else
					r=mid;
			}
			if(calc(l,o,p,sz).compareTo(S)==0)
				System.out.println("Yes "+l);
			else
				System.out.println("No");	
		}else{
			System.out.println("No");
		}
	}
}
