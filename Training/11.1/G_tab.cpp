#include<bits/stdc++.h>
#define player first
#define num first
#define type second
#define stone second
using namespace std;

/*
map<pair<int,vector<pair<int,int> > >,int >M;
// player {(num,type)}

void print(pair<int,vector<pair<int,int> > >sta){
	cerr<<sta.player<<endl;
	for(auto x:sta.stone)
		fprintf(stderr,"{%d,%d} ",x.first,x.second);
	cerr<<endl;
}
int dfs(pair<int,vector<pair<int,int> > > sta){
	//print(sta);
	if(sta.stone.size()==0)
		return 0;
	
	if(M.count(sta))
		return M[sta];
	for(int i=0;i<sta.stone.size();i++){
		if(sta.player==0){
			for(int j=1;j<=sta.stone[i].num;j++){
				if(sta.stone[i].type==1&&j%2==0)continue;
				if(sta.stone[i].type==2&&j%2==1)continue;
				vector<pair<int,int> >tmp=sta.stone;
				tmp[i].first-=j;
				if(tmp[i].first==0)tmp.erase(tmp.begin()+i);
				if(!dfs({1,tmp}))
					return M[sta]=1;
			}
		}else{		
			for(int j=1;j<=sta.stone[i].num;j++){
				vector<pair<int,int> >tmp=sta.stone;
				tmp[i].first-=j;
				if(tmp[i].first==0)tmp.erase(tmp.begin()+i);
				if(!dfs({0,tmp}))
					return M[sta]=1;
			}
		}
	}	
		
	return M[sta]=0;
}

int bf(){

	for(int i=1;i<=10;i++)
	for(int b1=0;b1<=2;b1++)
	for(int j=1;j<=10;j++)
	for(int b2=0;b2<=2;b2++)if((b1+b2!=0)&&dfs({0,{{i,b1},{j,b2}}})){
		printf("{%d,%d},{%d,%d} := %d\n",i,b1,j,b2,dfs({0,{{i,b1},{j,b2}}}));
	}
	
	

	for(int i=1;i<=10;i++)
	for(int b1=0;b1<=2;b1++)
	for(int j=1;j<=10;j++)
	for(int b2=0;b2<=2;b2++)
	for(int k=1;k<=10;k++)
	for(int b3=0;b3<=2;b3++)
	if((b1==2 || b2==2|| b3==2) && dfs({0,{{i,b1},{j,b2},{k,b3}}})){
		printf("{%d,%d},{%d,%d},{%d,%d} := %d\n",i,b1,j,b2,k,b3,dfs({0,{{i,b1},{j,b2},{k,b3}}}));
	}

	int w=6;
	for(int i=1;i<=w;i++)
	for(int b1=0;b1<=1;b1++)
	for(int j=1;j<=w;j++)
	for(int b2=0;b2<=1;b2++)
	for(int k=1;k<=w;k++)
	for(int b3=0;b3<=1;b3++)
	for(int l=1;l<=w;l++)
	for(int b4=0;b4<=1;b4++)
	if( 1 ){
		//For Bob
		int t1=dfs({1,{{i,b1},{j,b2},{k,b3},{l,b4}}});
		//if(!t1)continue;
		
		if(b1!=1 || i!=3)continue;
		assert(t1==1);
		int cnt=0;
		vector<int>tt;
		int all=0;
		if(b1&&i>1)cnt++,all=i;
		if(b2&&j>1)cnt++,all=j;
		if(b3&&k>1)cnt++,all=k;
		if(b4&&l>1)cnt++,all=l;
		if(cnt!=1)continue;
		
		int t2;
		if(all%2==1){
			t2=!((i^j^k^l^all));
		}else{
			t2=!((i^j^k^l^all^1));
		}
		
//		cout<<tt.front()<<endl;
//		int ti=b1?(i+1)/2:i,tj=b2?(j+1)/2:j,tk=b3?(k+1)/2:k,tl=b4?(l+1)/2:l;
		
	
		printf("{%d,%d},{%d,%d},{%d,%d},{%d,%d} := %d\n",i,b1,j,b2,k,b3,l,b4,dfs({1,{{i,b1},{j,b2},{k,b3},{l,b4}}}));
	//	assert(t1==t2);
	}
	

	return 0;
}

*/
const int maxn=1e5+5;
int a[maxn],b[maxn],n;
int main(){

	int T;cin>>T;
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
			if(a[i]==1&&b[i]==1)b[i]=0;
		}
		/*
		n=rand()%5+1;
		for(int i=1;i<=n;i++){
			a[i]=rand()%5+1;
		}
		
		for(int i=1;i<=n;i++){
			//scanf("%d",&b[i]);
			b[i]=rand()%3;
			if(a[i]==1&&b[i]==1)b[i]=0;
		}
		cerr<<n<<endl;
		for(int i=1;i<=n;i++)
			cerr<<a[i]<<" ";cerr<<endl;
		for(int i=1;i<=n;i++)
			cerr<<b[i]<<" ";cerr<<endl;
			*/
		int ps2=0,ps1=0,cnt1=0,cnt2=0;
		for(int i=1;i<=n;i++){
			if(b[i]==1){
				ps1=i;
				cnt1++;
			}
			if(b[i]==2){
				ps2=i;
				cnt2++;
			}
		}
		
		bool flag=true;
		
		if(cnt2>=2||(cnt2==1&&a[ps2]%2==1)){
			flag=false;
			goto END;
		}
		if(cnt2==1){
			if(cnt1)flag=false;
			else{
				int x=0;
				for(int i=1;i<=n;i++)if(i!=ps2)
					x^=a[i];
				flag=!x;
			}
			goto END;
		}		
		
		if(cnt1>=2){
			flag=false;
			goto END;
		}
		
		if(cnt1==1){
			int x=0;
			for(int i=1;i<=n;i++){
				if(i==ps1)
					x^=(!(a[i]&1));
				else
					x^=a[i];
			}
			flag=!x;
			goto END;
		}else{
			int x=0;
			for(int i=1;i<=n;i++){
				x^=a[i];
			}
			flag=!!x;
		}	
		
		END:
		/*
		vector<pair<int,int> >par;
		for(int i=1;i<=n;i++)
			par.push_back({a[i],b[i]});
		bool tmp=dfs({0,par});
		assert(tmp==flag);*/
		puts(flag?"Alice":"Bob");
	}
	return 0;
}
