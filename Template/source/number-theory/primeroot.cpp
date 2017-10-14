vector<LL>fct;
bool check(LL x,LL g){
	for(int i=0;i<fct.size();i++)
		if(pw(g,(x-1)/fct[i],x)==1)
			return 0;
	return 1;
}
LL findrt(LL x){
	LL tmp=x-1;
	for(int i=2;i*i<=tmp;i++){
		if(tmp%i==0){
			fct.push_back(i);
			while(tmp%i==0)tmp/=i;
		}
	}if(tmp>1)fct.push_back(tmp);
	// x is 1,2,4,p^n,2p^n
	// x has phi(phi(x)) primitive roots
	for(int i=2;i<int(1e9);i++)if(check(x,i))
		return i;
	return -1;
}
const int BASE[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool check(long long n,int base) {
    long long n2=n-1,res;
    int s=0;
    while(n2%2==0) n2>>=1,s++;
    res=pw(base,n2,n);
    if((res==1)||(res==n-1)) return 1;
    while(s--) {
        res=mul(res,res,n);
        if(res==n-1) return 1;
    }
    return 0; // n is not a strong pseudo prime
}
bool isprime(const long long &n) {
    if(n==2)
        return true;
    if(n<2 || n%2==0)
        return false;
    for(int i=0;i<12&&BASE[i]<n;i++){
        if(!check(n,BASE[i]))
            return false;
    }
    return true;
}
