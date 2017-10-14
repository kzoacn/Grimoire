LL Lucas(LL n,LL m,LL p){
	LL ans=1;
	while(n&&m){
		LL a=n%p,b=m%p;
		if(a<b)return 0;
		ans=(ans*C(a,b,p))%p;
		n/=p;m/=p;
	}return ans%p;
}
