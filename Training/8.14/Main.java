import java.util.*;
import java.io.*;
import java.math.*;

public class Main{
	static final long mo=998244353;
	static final int maxn=2101;
	static long[] fac;
	static BigInteger[] up;
	static boolean check(int[] num,boolean[] used,int pos){
		if(pos+1==num.length)
			return true;
		int[] a;a=new int[num.length];
		int sz=0;
		for(int i=0;i<num.length;i++)if(!used[i])
			a[sz++]=i;
		//Arrays.sort(a);
		for(int i=pos+1;i<num.length;i++){
			if(num[i]>a[i-pos-1])return true;
			if(num[i]<a[i-pos-1])return false;
		}
		return true;
	}
	static long get(BigInteger n){
		int d=0;
		long ans=0;
		for(int i=2;i<maxn;i++){
			if(up[i].compareTo(n)>0){
				d=i;
				break;
			}else{
				ans=(ans+(long)(i-1)*fac[i-1]%mo)%mo;
			}
		}
		int[] num,tmp;
		num=new int[d];
		tmp=new int[d];
		BigInteger D=BigInteger.valueOf(d);
		int sz=0;
		while(n.signum()>0){
			num[sz++]=n.mod(D).intValue();
			n=n.divide(D);
		}
		
		if(sz!=d)
			return ans;
		for(int i=0;i<d;i++){
			tmp[i]=num[d-1-i];
		}
		for(int i=0;i<d;i++){
			num[i]=tmp[i];
		}
		
		int[] a;
		a=new int[d];
		boolean[] used;
		used=new boolean[d];
		for(int i=0;i<d;i++){
			used[i]=false;
		}


/*		for(int i=0;i<d;i++)
			System.out.print(num[i]+" ");
		System.out.println();
*/
		boolean putted=false;
		for(int i=0;i<d;i++){
			for(int j=num[i];j>=0;j--){
				if(!used[j]){
					a[i]=j;
					used[j]=true;
					if(j<num[i]||check(num,used,i)){
						break;
					}
					used[j]=false;
				}
			}
			if(a[i]!=num[i]){
				for(int j=i+1;j<d;j++){
					for(int k=d-1;k>=0;k--){
						if(!used[k]){
							used[k]=true;
							a[j]=k;
							break;
						}
					}
				}
				break;
			}
		}
		
/*		for(int i=0;i<d;i++)
			System.out.print(a[i]+" ");
		System.out.println();
	*/	
		
		for(int i=0;i<d;i++){
			used[i]=false;
		}
		
	//	System.out.println(ans);
		int[] cnt,s;
		cnt=new int[d];
		s=new int[d];
		for(int i=0;i<d;i++){
			cnt[i]=0;
			s[i]=0;
		}
		if(a[0]==0)
			return ans;
		for (int i = 0; i < d; ++i) {
			s[a[i]] = 1;
		}
		for(int i=0;i<d;i++){
			int nows = 0;
			for (int j = 0; j < a[i]; ++j) {
				nows += s[j];
			}
			int tmp2 = 0;
				tmp2 = nows;
			if (i > 0) {
			} else {
				tmp2 = a[0] - 1;
			}
			ans+=tmp2*fac[d-1-i]%mo;
			ans%=mo;
//System.out.println(i + "  " + tmp2 + " " + fac[d - 1 - i]);
			s[a[i]]--;
		}
		ans+=1;
		ans%=mo;
		return ans;
	}
	
	public static void main(String[] arg){
	
		fac=new long[maxn];
		fac[0]=1;
		for(int i=1;i<maxn;i++)
			fac[i]=(long)fac[i-1]*i%mo;
	
		up=new BigInteger[maxn];
		for(int i=2;i<maxn;i++){
			BigInteger d=BigInteger.valueOf(i);
			BigInteger d1=d.subtract(BigInteger.ONE);
			up[i]=d1.multiply(d.pow(i)).subtract(d.multiply((d.pow(i-1).subtract(BigInteger.ONE)).divide(d1)));
			up[i]=up[i].divide(d1);
		}
		
//		for(int i=2;i<10;i++)
//			System.out.println(up[i]);

//		System.out.println(get(BigInteger.valueOf(76)));
//		System.exit(0);
	
		Scanner cin=new Scanner(System.in);
		int T=cin.nextInt();
		while(T-->0){
			BigInteger l=cin.nextBigInteger(),r=cin.nextBigInteger();
			
			long ans1=get(r);
			long ans2=get(l.subtract(BigInteger.ONE));
			long ans=(ans1-ans2+mo)%mo;
			System.out.println(ans);
		}
		
	}
}

