#include<bits/stdc++.h>
#define out(x) cerr<< #x <<"="<< x <<endl

//#define DEBUG

using namespace std;
const int maxn=1e5+5;
int l,d;
string str[3];
int cnt1[maxn];
int cnt2[maxn][3];
int cnt3[maxn];
int rest[3];
bool check(int x){

	//cerr<< x << endl;
	//cerr<<rest[0]<<" "<<rest[1]<<" "<<rest[2]<<endl;

	for(int i=0;i<3;i++){
		int r[3]={rest[0],rest[1],rest[2]};
		int sum=cnt1[x]+cnt2[x][0]+cnt2[x][1]+cnt2[x][2];
		//out(sum);
		r[0]-=sum;
		r[1]-=sum;
		r[2]-=sum;
		/*out(r[0]);
		out(r[1]);
		out(r[2]);*/
		for(int j=0;j<3;j++){
			if(i!=j){
				r[0]+=cnt2[x][j];
				r[1]+=cnt2[x][j];
				r[2]+=cnt2[x][j];
				r[j]-=cnt2[x][j];
			}
		}
		//r[0] r[1] r[2]
		//out(r[0]);
	//	out(r[1]);
	//	out(r[2]);
		int j=(i+1)%3;
		int k=(i+2)%3;
		int C=cnt2[x][i];
	//	out(C);
		if(r[j]<0 && r[k]<0){
			if(r[j]<r[k]){
				if(C+r[k]>=0){
					r[k]=0;
					r[j]+=-r[k];
					C+=r[k];
				}else{
					r[k]+=C;
					r[j]+=C;
					C=0;
				}
			}else{
				if(C+r[j]>=0){
					r[j]=0;
					r[k]+=-r[j];
					C+=r[j];
				}else{
					r[j]+=C;
					r[k]+=C;
					C=0;
				}
			}
		}
	//	out(r[0]);
	//	out(r[1]);
	//	out(r[2]);
	//	out(C);
		if(C+cnt1[x]>=-min(0,r[0])-min(0,r[1])-min(0,r[2]))
			return true;
	}
	return false;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	while(cin>>l>>d){
		if(!l)break;
		
		
		cin>>str[0]>>str[1]>>str[2];
		cnt1[l]=0;cnt3[l]=0;
		cnt2[l][0]=cnt2[l][1]=cnt2[l][2]=0;
		for(int i=l-1;i>=0;i--){
			cnt1[i]=cnt1[i+1];
			cnt3[i]=cnt3[i+1];
			cnt2[i][0]=cnt2[i+1][0];
			cnt2[i][1]=cnt2[i+1][1];
			cnt2[i][2]=cnt2[i+1][2];
			vector<int>vec;
			vec.push_back(str[0][i]);
			vec.push_back(str[1][i]);
			vec.push_back(str[2][i]);
			sort(vec.begin(),vec.end());
			vec.erase(unique(vec.begin(),vec.end()),vec.end());
			if(vec.size()==3){
				cnt1[i]++;
			}else
			if(vec.size()==2){
				//cerr<<str[0][i]<<" "<<str[1][i]<<" "<<str[2][i]<<endl;
				if(str[0][i]==str[1][i])
					cnt2[i][2]++;
				if(str[0][i]==str[2][i])
					cnt2[i][1]++;
				if(str[2][i]==str[1][i])
					cnt2[i][0]++;
			}else{
				cnt3[i]++;
			}
		}
		rest[0]=rest[1]=rest[2]=d;
		string ans;
		ans.resize(l);
		for(int i=0;i<l;i++){
		//	printf("%d %d %d %d\n",cnt1[i],cnt2[i][0],cnt2[i][1],cnt2[i][2]);
		}
		
		for(int i=0;i<l;i++){
			vector<char>can;
			can.push_back('A');
			can.push_back(str[0][i]);
			can.push_back(str[1][i]);
			can.push_back(str[2][i]);
			
			sort(can.begin(),can.end());
			can.erase(unique(can.begin(),can.end()),can.end());
			int flag=0;
			for(int j=0;j<can.size();j++){
				ans[i]=can[j];
				int tmp[3]={rest[0],rest[1],rest[2]};
				
				rest[0]-=(str[0][i]!=can[j]);
				rest[1]-=(str[1][i]!=can[j]);
				rest[2]-=(str[2][i]!=can[j]);
				
				
				if(check(i+1)){
					flag=1;
					break;
				}
				rest[0]+=(str[0][i]!=can[j]);
				rest[1]+=(str[1][i]!=can[j]);
				rest[2]+=(str[2][i]!=can[j]);
				
			}
			if(flag==0){
				ans="-1";
				break;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
