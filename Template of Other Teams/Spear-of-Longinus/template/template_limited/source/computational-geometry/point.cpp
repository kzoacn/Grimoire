struct P{
	double x,y;
	P turn90(){return P(-y,x);}
};
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
P intersect(L l1,L l2){
	double s1=det(l1.a,l1.b,l2.a);
	double s2=det(l1.a,l1.b,l2.b);
	return (l2.a*s2-l2.b*s1)/(s2-s1);
}
P project(P p,L l){
	return l.a+l.v()*((p-l.a)^l.v())/l.v().len2();
}
double dis(P p,L l){
	return fabs((p-l.a)*l.v())/l.v().len();
}

