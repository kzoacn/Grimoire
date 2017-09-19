import java.util.*;
import java.io.*;
import java.lang.*;
import java.math.*;


public class Main{


	public static class Point{
		public BigInteger x,y;
		public Point(){}
		public Point(BigInteger _x,BigInteger _y){
			x=_x;
			y=_y;
		}
		public BigInteger dot(Point oth){
			return x.multiply(oth.x).add(y.multiply(oth.y));
		}
		
		public BigInteger det(Point oth){
			return x.multiply(oth.y).subtract(y.multiply(oth.x));
		}
		public BigInteger len2(){
			return x.multiply(x).add(y.multiply(y));
		}
		public boolean onLeft(Point oth){
			return det(oth).signum()>0;
		}
	
		public Point subtract(Point oth){
			return new Point(x.subtract(oth.x),y.subtract(oth.y));
		}
		public String toString(){
			return "("+x+","+y+")";
		}
	}
	public static boolean greater(int s1,BigInteger a,BigInteger b2,int s2,BigInteger c,BigInteger d2){
		//s1*a/b > s2* c/d ?
		//System.out.println(s1+" "+a+" "+b2+" ??? "+s2+" "+c+" "+d2);
		
		if(s1!=s2){
			return s1>s2;
		}
		if(s1==0&&s2==0)
			return false; 
		if(s1==1){
			return a.multiply(a).multiply(d2).compareTo(c.multiply(c).multiply(b2))>0;
		}else{
			return a.multiply(a).multiply(d2).compareTo(c.multiply(c).multiply(b2))<0;
		}
	}


	public static boolean check(Point A,Point B,Point C,Point P){
		Point AC,AB,PC,PB,BC;
		BC=C.subtract(B);
		AC=C.subtract(A);
		AB=B.subtract(A);
		PC=C.subtract(P);
		PB=B.subtract(P);

		int s1=0,s2=0;		
		
		BigInteger dot1,dot2;
		dot1=AC.dot(AB);
		s1=dot1.signum();
		dot1=dot1.abs();
		
		dot2=PC.dot(PB);
		s2=dot2.signum();
		dot2=dot2.abs();
		/*
		System.out.println(A);
		System.out.println(B);
		System.out.println(C);
		System.out.println(P);
		
		
		System.out.println(AC);
		System.out.println(AB);
		System.out.println(PC);
		System.out.println(PB);
		
		*/
		
		if(BC.onLeft(A.subtract(B))==BC.onLeft(P.subtract(B))){
			//System.out.println("same side");
			return greater(s2,dot2,PC.len2().multiply(PB.len2()),s1,dot1,AC.len2().multiply(AB.len2()));
		}else{
			//System.out.println("not same side");
			return greater(s1,dot1,AC.len2().multiply(AB.len2()),s2*(-1),dot2,PC.len2().multiply(PB.len2()));
		}
	}

	public static void main(String[] arg){
		Scanner cin=new Scanner(System.in);
		
		int T=cin.nextInt();
		while(T-->0){
			Point A,B,C,P;
			A=new Point();
			B=new Point();
			C=new Point();
			P=new Point();
			A.x=cin.nextBigInteger();
			A.y=cin.nextBigInteger();
			B.x=cin.nextBigInteger();
			B.y=cin.nextBigInteger();
			C.x=cin.nextBigInteger();
			C.y=cin.nextBigInteger();
			P.x=cin.nextBigInteger();
			P.y=cin.nextBigInteger();
			boolean ok=true;
			ok&=check(A,B,C,P);
//			System.out.println(ok);
			ok&=check(C,A,B,P);
			
//			System.out.println(ok);
			ok&=check(B,C,A,P);
			
//			System.out.println(ok);
			System.out.println(ok?"Accepted":"Rejected");
		}
	}
}/*
(-2,0)
(0,-2)
(2,0)
(2,-2)
(4,0)
(2,-2)
(0,2)
(-2,0)
not same side
0 0 16 ??? 1 8 128
Rejected


*/
