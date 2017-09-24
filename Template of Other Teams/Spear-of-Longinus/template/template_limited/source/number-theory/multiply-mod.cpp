LL mul(LL a,LL b,LL p){//保证a,b非负 
    a=(a+p)%p; 
    b=(b+p)%p;
	LL t=(a*b-LL((long double)a*b/p)*p)%p;
	return (t+p)%p;	
}
LL mul(LL x,LL k,LL p){
    LL ans=0;
    for(;k;k>>=1){
        if(k&1)ans=(ans+x)%p;
        x=(x+x)%p;
    }
    return ans;
}