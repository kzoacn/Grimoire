#include<bits/stdc++.h>
using namespace std;
const int maxn=2000010;
typedef unsigned long long UL;

UL hash_l[maxn];
const UL base=233;

UL *s[30010];
char str[maxn];
int ty[30010],lens[30010];
UL a,b,c,d;
int lena,lenb,lenc,lend;
UL get(int t,int l,int r){
	return s[t][r]-s[t][l-1]*hash_l[r-l+1];
}
int id[30010];

bool check(int k){
	int n=lens[k];
	if(lena+lenb>n/2||lenc+lend>n/2)
		return false;
	if(get(k,1,lena)!=a)
		return false;
	if(get(k,n/2-lenb+1,n/2)!=b)
		return false;
//	cerr<<c<<" "<<lenc<<endl;
//	cerr<<c<<" "<<lenc<<endl;
	if(get(k,n/2+1,n/2+lenc)!=c)
		return false;
	if(get(k,n-lend+1,n)!=d)
		return false;
	return true;
}

int main(){
	hash_l[0]=1;
	for(int i=1;i<maxn;i++)
		hash_l[i]=hash_l[i-1]*base;
	
	int T;cin>>T;
	while(T--){
		int q;
		int sz=0;
		scanf("%d",&q);
		for(int t=1;t<=q;t++){
			scanf("%d",&ty[t]);
			
			if(ty[t]==1){
				id[++sz]=t;
				scanf("%s",str+1);
				lens[t]=strlen(str+1);
				s[t]=new UL[lens[t]+5];
				s[t][0]=0;
				for(int i=1;i<=lens[t];i++)
					s[t][i]=s[t][i-1]*base+str[i];
			}else{
				scanf("%s",str+1);lena=strlen(str+1);
				a=0;
				for(int i=1;i<=lena;i++)
					a=a*base+str[i];
					
				scanf("%s",str+1);lenb=strlen(str+1);
				b=0;
				for(int i=1;i<=lenb;i++)
					b=b*base+str[i];
					
				scanf("%s",str+1);lenc=strlen(str+1);
				c=0;
				for(int i=1;i<=lenc;i++)
					c=c*base+str[i];
					
				scanf("%s",str+1);lend=strlen(str+1);
				d=0;
				for(int i=1;i<=lend;i++)
					d=d*base+str[i];
					
				int ans=0;
				for(int i=1;i<=sz;i++){
					int k=id[i];
					if(check(k))
						ans++;
				}
				printf("%d\n",ans);
			}
		}
		
		
		for(int t=1;t<=q;t++){
			if(ty[t]==1){
				delete[] s[t];
				s[t]=0;
			}
		}
	}		
	
	return 0;
}
