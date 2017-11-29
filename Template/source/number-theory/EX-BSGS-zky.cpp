LL BSGS(LL a,LL b,LL p){
    LL m=0;for(;m*m<=p;m++);
    map<LL,int>hash;hash[1]=0;
    LL e=1,amv=inv(pw(a,m,p),p);
    for(int i=1;i<m;i++){
        e=e*a%p;
        if(!hash.count(e))
            hash[e]=i;  
        else break;
    }
    for(int i=0;i<m;i++){
        if(hash.count(b))
            return hash[b]+i*m;
        b=b*amv%p;  
    }
    return -1;
}
LL solve2(LL a,LL b,LL p){
    //a^x=b (mod p)
    b%=p;
    LL e=1%p;
    for(int i=0;i<100;i++){
        if(e==b)return i;
        e=e*a%p;
    }
    int r=0;
    while(gcd(a,p)!=1){
        LL d=gcd(a,p);
        if(b%d)return -1;
        p/=d;b/=d;b=b*inv(a/d,p);
        r++;
    }LL res=BSGS(a,b,p);
    if(res==-1)return -1;
    return res+r;
}
