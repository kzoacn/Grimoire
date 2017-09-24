#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int N = 505;

struct node{
	char s1[15], s2[15], s3[15];
	int len1, len2, len3;
	int deg;
	bool Const;
}a[N];

int n;

char Equal[404], add[15];
char First[15];
char pattern[2105];
int f[515][2105];

vector<int> G[515];

map<string, int> Q;

int D[515];

int main(){
	
	int Case;
	scanf("%d", &Case);
	
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d", &n);
		for (int i = 1; i <= n; i++){
			scanf("%s", a[i].s1 + 1);
			a[i].len1 = strlen(a[i].s1 + 1);
			
			scanf("%s", Equal + 1);
			
			scanf("%s", a[i].s2 + 1);
			a[i].len2 = strlen(a[i].s2 + 1);
			
			a[i].Const = 0;
			a[i].deg = 2;
			
			if (a[i].s2[1] >= 'a' && a[i].s2[1] <= 'z') {
				a[i].Const = 1;
				a[i].deg = 0;
			}
			else {
				scanf("%s", add + 1);
				
				scanf("%s", a[i].s3 + 1);
				a[i].len3 = strlen(a[i].s3 + 1);
				
			}
			
			Q[string(a[i].s1 + 1)] = i;
		}
		
		scanf("%s", First + 1);
		scanf("%s", pattern + 1);
		
		int len = strlen(pattern + 1);
		
		int head = 0, tail = 0;
		
		for (int i = 1; i <= n; i++)
			if (a[i].Const == 0){
				G[Q[string(a[i].s2 + 1)]].push_back(i);
				G[Q[string(a[i].s3 + 1)]].push_back(i);
			}
		
		for (int i = 1; i <= n; i++)
			if (a[i].deg == 0){
				++tail;
				D[tail] = i;
			}
		
		while (head < tail){
			int Cur = D[++head];
			
			
			for (int j = 0; j < G[Cur].size(); j++){
				int y = G[Cur][j];
				
				a[y].deg--;
				if (a[y].deg == 0){
					D[++tail] = y;
				}
			}
			
			for (int i = 1; i <= len; i++)
				f[Cur][i] = 0;
			
			if (a[Cur].Const == 1){
				for (int i = 1; i <= len; i++){
					
					f[Cur][i] = i - 1;
					
					int x = i - 1;
					int y = 1;
					while (x + 1 <= len && y <= a[Cur].len2){
						while (y <= a[Cur].len2 && pattern[x + 1] != a[Cur].s2[y]) y++;
						
						
						if (y > a[Cur].len2) break;
						
						x++; y++;
					}
					f[Cur][i] = x;					
				}
			} else {
				int t2 = Q[string(a[Cur].s2 + 1)];
				int t3 = Q[string(a[Cur].s3 + 1)];
				
				
				for (int i = 1; i <= len; i++){
					f[Cur][i] = i - 1;
					
					
					if (f[t2][i] < i && f[t3][i] < i) continue;
					if (f[t2][i] == len || f[t3][i] == len) {
						f[Cur][i] = len;
						continue;
					}
					if(f[t2][i] < i) {
						f[Cur][i] = f[t3][i];
					} else {
						f[Cur][i] = f[t3][f[t2][i] + 1];
					}
				}
			}
			
			
		}
		
		
		int id = Q[string(First + 1)];
	
		
		if (f[id][1] == len) puts("YES");
		else puts("NO");
		
		for (int i = 1; i <= n; i++)
			G[i].clear();
		Q.clear();
	}
	
	return 0;
}
