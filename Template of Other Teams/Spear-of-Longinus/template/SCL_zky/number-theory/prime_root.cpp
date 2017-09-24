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

