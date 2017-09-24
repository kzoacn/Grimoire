
/*
{(mod,G)}={(81788929,7),(101711873,3),(167772161,3)
			,(377487361,7),(998244353,3),(1224736769,3)
			,(1300234241,3),(1484783617,5)}
*/
int mo=998244353,G=3;
void NTT(int a[],int n,int f){
	for(register int i=0;i<n;i++) 
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for (register int i=2;i<=n;i<<=1){
		static int exp[maxn];
		exp[0]=1;exp[1]=pw(G,(mo-1)/i);
		if(f==-1)exp[1]=pw(exp[1],mo-2);
		for(register int k=2;k<(i>>1);k++)
			exp[k]=1LL*exp[k-1]*exp[1]%mo;
		for(register int j=0;j<n;j+=i){
			for(register int k=0;k<(i>>1);k++){
				register int &pA=a[j+k],&pB=a[j+k+(i>>1)];
				register int A=pA,B=1LL*pB*exp[k]%mo;
				pA=(A+B)%mo;
				pB=(A-B+mo)%mo;
			}
		}
	}
	if(f==-1){
		int rv=pw(n,mo-2)%mo;
		for(int i=0;i<n;i++)
			a[i]=1LL*a[i]*rv%mo;
	}
}
void mul(int m,int a[],int b[],int c[]){
	int n=1,len=0;
	while(n<m)n<<=1,len++;
	for (int i=1;i<n;i++) 
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
	NTT(a,n,1);
	NTT(b,n,1);
	for(int i=0;i<n;i++)
		c[i]=1LL*a[i]*b[i]%mo;
	NTT(c,n,-1);
}

