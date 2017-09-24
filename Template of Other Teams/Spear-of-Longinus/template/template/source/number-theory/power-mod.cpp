LL pw(LL x,LL k,LL p){
    LL ans=1;
    for(;k;k>>=1){
        if(k&1)ans=ans*x%p;
        x=x*x%p;
    }
    return ans%p;
}