#include<bits/stdc++.h>
using namespace std;

int solve(int year,int month,int day){
	int answer;
	if(month==1||month==2){
		month+=12;
		year--;
	}
	answer=(day+2*month+3*(month+1)/5+year+year/4-year/100+year/400)%7;
	return answer;
}

int main(){
	int T;cin>>T;
	while(T--){
		int year,month,day,h,m,s;
		scanf("%d-%d-%d %d:%d:%d\n",&year,&month,&day,&h,&m,&s);
		pair<int,int>day1,day2;
		int cnt1=0,cnt2=0;
		for(int i=1;i<40;i++){
			if(solve(year,3,i)==6){
				cnt1++;
				if(cnt1==2){
					day1=make_pair(3,i);
				}
			}
			
			if(solve(year,11,i)==6){
				cnt2++;
				if(cnt2==1){
					day2=make_pair(11,i);
				}
			}
		}
	
//		cerr<<year<<" "<<month<<" "<<day<<" "<<h<<" "<<m<<" "<<s<<endl;
		static int tt=0;
		if(make_pair(month,day)==day1){
			if(make_tuple(h,m,s)<make_tuple(2,0,0)){
				printf("Case #%d: PST\n",++tt);
			}else if(make_tuple(h,m,s)>=make_tuple(3,0,0)){
				printf("Case #%d: PDT\n",++tt);
			}else{
				printf("Case #%d: Neither\n",++tt);
			}
		}else if(make_pair(month,day)==day2){
			if(make_tuple(h,m,s)<make_tuple(1,0,0)){
				printf("Case #%d: PDT\n",++tt);
			}else if(make_tuple(h,m,s)>=make_tuple(2,0,0)){
				printf("Case #%d: PST\n",++tt);
			}else{
				printf("Case #%d: Both\n",++tt);
			}
		}else{
			if(day1<make_pair(month,day)&&make_pair(month,day)<day2){
				printf("Case #%d: PDT\n",++tt);
			}else{
				printf("Case #%d: PST\n",++tt);
			}
		}
	}

	return 0;
}
