LL china(int n,int *a,int *m){
	LL M=1,d,x=0,y;
	for(int i=0;i<n;i++)
		M*=m[i];
	for(int i=0;i<n;i++){
		LL w=M/m[i];
		d=exgcd(m[i],w,d,y);
		y=(y%M+M)%M;
		x=(x+y*w%M*a[i])%M;
	}
	while(x<0)x+=M;
	return x;
}
