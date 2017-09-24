#include<bits/stdc++.h>
using namespace std;

double sgn(double x,double y){
	return fabs(x-y)/max(max(x,y),0.0) > 1e-6;
}

int main(int argc,char **argv){

	FILE *f1=fopen(argv[1],"r"),*f2=fopen(argv[2],"r");
	int x;
	double y1,y2;
	char s1[22],s2[33];
	while(fscanf(f1,"Case #%d: %s",&x,&s1)==2){
		fscanf(f2,"Case #%d: %s",&x,&s2);
		if(s1[0]=='i'&&s2[0]=='i')continue;
		else{
			if(s1[0]=='i'||s2[0]=='i'){
				cerr<<y1<<" "<<y2<<endl;
				cerr<<"No"<<endl;
				return -1;
			}
		}
		sscanf(s1,"%lf",&y1);
		sscanf(s2,"%lf",&y2);
		if(sgn(y1,y2)){
			cerr<<y1<<" "<<y2<<endl;
			cerr<<"No"<<endl;
			return -1;
		}
	}
	cerr<<"Yes"<<endl;

	return 0;
}
