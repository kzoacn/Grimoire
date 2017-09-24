#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int N = 505;

queue<char> Q;

int Have[N];
char str[N];
int Case, n, m;

int main(){
	
	scanf("%d", &Case);
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d%d", &n, &m);
		scanf("%s", str);	
		
		for (char ch = 'A'; ch <= 'Z'; ch++) Have[ch] = 0;
		
		while (Q.size()) Q.pop();
		
		int Ans = 0;
		for (int i = 0; i < n; i++){
			//printf("%c\n", str[i]);
			if (Have[str[i]]) Ans++;
			if (Q.size() == m){
				char Cur = Q.front();
				Have[Cur]--;
				Q.pop();
			}
			Q.push(str[i]);
			Have[str[i]]++;
		}
		
		printf("Case %d: %d\n", ii, Ans);
	}
	
	return 0;
}
