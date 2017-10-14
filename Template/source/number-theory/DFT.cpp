int Pow(int x,int y,int z){
	if (y==0) return 1;
	LL ret=Pow(x,y>>1,z); (ret*=ret)%=z;
	if (y & 1) (ret*=x)%=z;
	return ret;
}


void Prep(){
	for (len=1, ci=0; len<=N+N; len<<=1, ci++);
	Wi[0]=1, Wi[1]=Pow(G,(Mo-1)/len,Mo);
	for (int i=2; i<=len; i++) Wi[i]=(Wi[i-1]*Wi[1])% Mo;
	for (int i=0; i<len; i++){
		int tmp=0;
		for (int j=i, c=0; c<ci; c++, j>>=1 ) tmp=(tmp <<= 1)|= (j & 1);
		Bel[i]=tmp;
	}
}

void Dft(Arr &a,int sig)
{
	for (int i=0; i<len; i++) tp[Bel[i]]=a[i];
	for (int m=1; m<=len; m<<=1){
		int half=m>>1, bei=len/m;
		for (int i=0; i<half; i++){
			LL wi=(sig>0)?Wi[i*bei]:Wi[len-i*bei];
			for (int j=i; j<len; j+=m){
				int u=tp[j],v=wi*LL(tp[j+half]) % Mo;
				tp[j]=(u+v) % Mo; tp[j+half]=(u-v+Mo)% Mo;
			}
		}
	}
	for (int i=0; i<len; i++) a[i]=tp[i];
}

void Mul(Arr &x,Arr &y,Arr &c,bool same)
{
	if (!same){
		for(int i=0; i<len; i++) a[i]=x[i], b[i]=y[i];
		Dft(a,1),Dft(b,1);
		for(int i=0; i<len; i++) a[i]=a[i]*1ll*b[i] % Mo;
		Dft(a,-1);
		for(int i=0; i<=M; i++) c[i]=a[i]*1ll*Rev % Mo;
	} else
	{
		for(int i=0; i<len; i++) a[i]=x[i];
		Dft(a,1);
		for(int i=0; i<len; i++) a[i]=a[i]*1ll*a[i] % Mo;
		Dft(a,-1);
		for(int i=0; i<=M; i++) c[i]=a[i]*1ll*Rev % Mo;
	}
}

Prep();
Ans[0]=1; Rev=Pow(len,Mo-2,Mo);
for(; K; K>>=1){
	if (K & 1) Mul(Ans,F,Ans,0);
	if (K > 1) Mul(F,F,F,1);
}

printf("%d\n",Ans[M]);