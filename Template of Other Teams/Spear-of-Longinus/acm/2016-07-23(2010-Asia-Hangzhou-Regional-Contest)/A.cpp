#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 67108863;

int q[N];
bool vis[N];

int main(){
	
	q[1] = N;
	int ii = 0, jj = 1;
	while (ii < jj){
		++ii;
		int Cur = q[ii];
		if (Cur % 2 == 0){
			if (!vis[Cur >> 1]){
				vis[Cur >> 1] = 1;
				q[++jj] = Cur >> 1;
			}
		} else {
			if (Cur > 1 && !vis[Cur - 1]){
				vis[Cur - 1] = 1;
				q[++jj] = Cur - 1;
			}
			if (Cur < N && !vis[Cur + 1]){
				vis[Cur + 1] = 1;
				q[++jj] = Cur + 1;
			}
		}
	}
	for (int i = 1; i <= jj; i++){
		printf("%d\n",q[i]);
	}
	printf("%d\n",jj);	
	
}
