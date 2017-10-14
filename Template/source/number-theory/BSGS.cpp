LL BSGS(LL a,LL b,LL p){
	LL m=sqrt(p)+.5,v=inv(pw(a,m,p),p),e=1;
	map<LL,LL>hash;hash[1]=0;
	for(int i=1;i<m;i++)
		e=e*a%p,hash[e]=i;
	for(int i=0;i<=m;i++){
		if(hash.count(b))return i*m+hash[b];
		b=b*v%p;
	}return -1;
}
