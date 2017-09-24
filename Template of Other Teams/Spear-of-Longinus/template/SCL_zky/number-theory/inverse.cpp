LL inv(LL a,LL p){
	LL d,x,y;
	d=exgcd(a,p,x,y);
	return d==1?(x+p)%p:-1;
}
