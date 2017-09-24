import java.util.*;
import java.io.*;
import java.math.*;
import java.lang.*;

public class Main{
	static String[] str;
	static BigInteger[][][] f;
	static BigInteger[][] sum,cnt;
	static String fix(String s){
		String ans="";
		for(int i=0;i<s.length();i++)if(s.charAt(i)!='N')
			ans+=s.charAt(i);
		return ans;
	}
	static char solve(String st,int n,BigInteger k){
		BigInteger s=BigInteger.ZERO,ss=BigInteger.ZERO;
		if(n==0)
			return st.charAt(k.intValue());
		st=fix(st);
		int c=-1;
		for(int i=0;i<st.length();i++){
			int x=(int)st.charAt(i)-(int)'A';
			if(s.compareTo(k)<=0){
				c=x;
				ss=s;
			}
			if(0<=x&&x<26)
				s=s.add(sum[x][n]);
			else
				s=s.add(BigInteger.ONE);
		}
		if(0<=c&&c<26)
			return solve(str[c],n-1,k.subtract(ss));
		else	
			return (char)(c+(int)'A');
	}
	
	public static void main(String[] arg){
		f=new BigInteger[30][111][30];
		sum=new BigInteger[30][111];
		cnt=new BigInteger[30][30];
		
		str=new String[26];
		str[0]="ACM-ICPC";
		str[1]="BIDU";
		str[2]="consonant:BCDFGHJKLMNPQRSTVXZWY";
		str[3]="D41D8CD98F00B204E9800998ECF8427E";
		str[4]="2.718281828459...";
		str[5]="0xFACEB00C";
		str[6]="1E100.net";
		str[7]="\\Huge{String}";
		str[8]="InternationalCollegiateProgrammingContest";
		str[9]="JinKeLa";
		str[10]="KeepItSimpleStupid";
		str[11]="1000mL";
		str[12]="Micro$oftCorp";
		str[13]="";
		str[14]="Oops";
		str[15]="pneumonoultramicroscopicsilicovolcanoconiosis";
		str[16]="A";
		str[17]="P";
		str[18]="M";
		str[19]="TheQuickBrownFoxJumpsOverTheLazyDog";
		str[20]="\\bigcup";
		str[21]="vowel:AEIOU";
		str[22]="WWW";
		str[23]="X-ray";
		str[24]="YOOOOOO!";
		str[25]="ZheJiangUniversity";
		for(int i=0;i<26;i++){
			for(int j=0;j<=26;j++){
				cnt[i][j]=BigInteger.ZERO;
			}
			for(int j=0;j<=100;j++){
				sum[i][j]=BigInteger.ZERO;
			}
		}
		for(int i=0;i<26;i++){
			for(int j=0;j<str[i].length();j++){
				char c=str[i].charAt(j);
				int x=(int)c-(int)'A';
				if(0<=x&&x<26)
					cnt[i][x]=cnt[i][x].add(BigInteger.ONE);
				else
					cnt[i][26]=cnt[i][26].add(BigInteger.ONE);
			}
		}
		for(int i=0;i<=26;i++)
		for(int j=0;j<=100;j++)
		for(int k=0;k<=26;k++)
			f[i][j][k]=BigInteger.ZERO;
		
		for(int i=0;i<26;i++)
			f[i][0][i]=BigInteger.ONE;
			
		BigInteger inf=(new BigInteger("10")).pow(82);
			
		for(int j=1;j<=100;j++){
			for(int i=0;i<26;i++){
				for(int k=0;k<=26;k++){
					for(int l=0;l<26;l++){
						f[i][j][k]=f[i][j][k].add(f[i][j-1][l].multiply(cnt[l][k]));
					}
				}
				f[i][j][26]=f[i][j][26].add(f[i][j-1][26]);
				
				for(int k=0;k<=26;k++){
					if(f[i][j][k].compareTo(inf)>=0)
						f[i][j][k]=inf;
				}
			}
		}
		for(int i=0;i<26;i++)
		for(int j=0;j<=100;j++){
			for(int k=0;k<=26;k++)
				sum[i][j]=sum[i][j].add(f[i][j][k]);
		}
		
		
		Scanner cin = new Scanner(System.in);
		while(cin.hasNext()){
			String s=cin.next();
			int n,m;BigInteger k;
			n=cin.nextInt();
			m=cin.nextInt();
			k=cin.nextBigInteger();
			String str="";
			BigInteger len=BigInteger.ZERO;
			for(int i=0;i<s.length();i++){
				int x=(int)s.charAt(i)-(int)'A';
				
				if(0<=x&&x<26)
					len=len.add(sum[x][n]);
				else
					len=len.add(BigInteger.ONE);
			}
			for(int i=0;i<m;i++){
				if(k.add(BigInteger.valueOf(i)).compareTo(len)>=0)
					break;
				str+=solve(s,n,k.add(BigInteger.valueOf(i)));
			}
			System.out.println(str);
		}
	}
}/*
ACM-ICPC 1 0
0 1
2 1
12 1
-20 1
8 1
2 1
15 1
2 1
ACM-ICPC 0 0
A

*/
