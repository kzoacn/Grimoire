#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100000;

int x, y;

int main(){
	int Case;
	scanf("%d", &Case);
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d%d", &x, &y);
		
		double p = 1.0;
		double Ans = 0.0;
		double Cnt = 0.0;
		
		for (int i = 1; i <= N; i++){
			p = p * 0.5;
			int x1 = x - min(x,y), y1 = y + min(x,y);
			int x2 = x + min(x,y), y2 = y - min(x,y);
			int tmpx = x, tmpy = y;
			
			if (x1 == 0){
				Cnt = Cnt + i * p;
				
				x = x2; y = y2;
				
			}
			
			if (y2 == 0){
				Cnt = Cnt + i * p;
				Ans = Ans + p;
				
				x = x1; y = y1;
			}
			if(tmpx == tmpy) {
				break;
			}
		}
		printf("Case %d: %.6f %.6f\n", ii, Cnt, Ans);
	}
	return 0;
}
