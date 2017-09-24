double area(double l,double r){
	double mid=(l+r)/2;
	return (r-l)*(f(l)+4*f(mid)+f(r))/6;
}
double simpson(double l,double r){
	double mid=(l+r)/2;
	double S=area(l,r),lS=area(l,mid),rS=area(mid,r);
	if(sgn(S-lS-rS)==0)
		return (S+(lS+rS))/2.0;
	return simpson(l,mid) + simpson(mid,r);
}
