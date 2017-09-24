import java.io.*;
import java.util.*;
import java.math.*;
public class Main{
	public static BigInteger n,m;
	public static Map<BigInteger,Integer> M = new HashMap();
//	public static BigInteger dfs(BigInteger x){
//		if(M.get(x)!=null)return M.get(x);
//		if(x.mod(BigInteger.valueOf(2))==1){
//		
//		}else{
//		
//		}
//		M.put();		
//	}
	public static void main(String []arg){
		Scanner cin = new Scanner(System.in);
		while(true){
			n = cin.nextBigInteger();
			m = cin.nextBigInteger();
			M.clear();
			if(n.compareTo(BigInteger.ZERO)==0)break;			
			if(n.compareTo(m)<=0){
				System.out.println(m.subtract(n));
				continue;
			}
			
			BigInteger[] QB = new BigInteger[5000*20];
			Integer[] QD = new Integer[5000*20];
			
			int head=0,tail=0;
			
			QB[tail]=n;
			QD[tail]=0;
			tail++;
			BigInteger ans = n.subtract(m).abs();
			while(head<tail){
				BigInteger now = QB[head],nxt;
				int dep = QD[head];
				
				//System.out.println("now is "+now+" dep is "+dep);
				
				if(ans.compareTo(BigInteger.valueOf(dep).add(m.subtract(now).abs()))>0)
					ans=BigInteger.valueOf(dep).add(m.subtract(now).abs());				
				
				head++;
				if(now.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ONE)!=0){
					nxt=now.divide(BigInteger.valueOf(2));
					if(M.get(nxt)==null){
						QB[tail]=nxt;
						QD[tail]=dep+1;
						tail++;
						M.put(nxt,1);
					}
				}else{
					nxt=now.subtract(BigInteger.ONE);
					if(M.get(nxt)==null&&nxt.compareTo(BigInteger.ZERO)!=0){
						QB[tail]=nxt;
						QD[tail]=dep+1;
						tail++;
						M.put(nxt,1);
					}					
					
					nxt=now.add(BigInteger.ONE);
					if(M.get(nxt)==null){
						QB[tail]=nxt;
						QD[tail]=dep+1;
						tail++;
						M.put(nxt,1);
					}					
				}
			}
			System.out.println(ans);
			
		}
	}
}
