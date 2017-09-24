#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int L = 2000005;
const int N = 2000005;

int n, len, m, cnt;
char str[L];
int s[L], heap[L], sa[L], trank[L], rank[L], sec[L], hei[L];
int Len[N], Start[N];
int f[L][25];

void Prepare(){
	for (int i = 1; i <= m; i++) heap[i] = 0;
	for (int i = 1; i <= len; i++) heap[s[i]]++;
	for (int i = 2; i <= m; i++) heap[i] += heap[i - 1];
	for (int i = len; i >= 1; i--){
		sa[heap[s[i]]] = i;
		heap[s[i]]--;
	}
	rank[sa[1]] = 1; cnt = 1;
	for (int i = 1; i <= len; i++){
		if (s[sa[i]] != s[sa[i - 1]]) cnt++;
		rank[sa[i]] = cnt;
	}
	m = cnt;
}

void Sa(){
	int j = 1;
	while (cnt < len){
		cnt = 0;
		for (int i = len - j + 1; i <= len; i++) sec[++cnt] = i;
		for (int i = 1; i <= len; i++)
			if (sa[i] > j)
				sec[++cnt] = sa[i] - j;
		for (int i = 1; i <= len; i++) trank[i] = rank[sec[i]];
		for (int i = 1; i <= m; i++) heap[i] = 0;
		for (int i = 1; i <= len; i++) heap[trank[i]]++;
		for (int i = 2; i <= m; i++) heap[i] += heap[i - 1];
		for (int i = len; i >= 1; i--){
			sa[heap[trank[i]]--] = sec[i];
		}
		trank[sa[1]] = 1; cnt = 1;
		for (int i = 2; i <= len; i++){
			if (rank[sa[i]] != rank[sa[i - 1]] || rank[sa[i] + j] != rank[sa[i - 1] + j]) cnt++;
			trank[sa[i]] = cnt;
		}
		for (int i = 1; i <= len; i++)
			rank[i] = trank[i];
		m = cnt; j += j;
	}
}

void Calc_height(){
	int k = 0;
	for (int i = 1; i <= len; i++){
		if (rank[i] == 1) continue;
		int j = sa[rank[i] - 1];
		while (i + k <= len && j + k <= len && s[i + k] == s[j + k]) k++;
		hei[rank[i]] = k;
		if (k) k--;
	}
}

void Rmq(){
	memset(f, 0X7F, sizeof(f));
	for (int i = 1; i <= len; i++)
		f[i][0] = hei[i];
	
	
	int Lg = floor(log(len) / log(2)) + 1;
	
	//printf("%d\n",Lg);
	for (int j = 1; j <= Lg; j++)
		for (int i = 1; i <= len; i++){
			if (i + (1 << (j - 1)) <= len)
				f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
}

int Lcp(int x,int y){
	
	int Lg = floor(log(y - x + 1) / log(2));
	
	return min(f[x][Lg], f[y - (1 << Lg) + 1][Lg]);
}

int main(){
	//freopen("a.in","r",stdin);
	scanf("%d", &n);
	
	len = 0;
	for (int i = 1; i <= n; i++){
		scanf("%s", str);
		Start[i] = len + 1;
		for (int j = 0; j < strlen(str); j++){
			s[++len] = str[j] - 'a' + 1;
		}
		Len[i] = strlen(str);
		s[++len] = 27;
	}
	
	m = 27;
	
	Prepare();
	Sa();
	Calc_height();
	Rmq();
	
	int Le , Ri, Mid;
	int Ans = 0;
	for (int i = 1; i <= n; i++){
		int Pos = rank[Start[i]];
		Le = 1; Ri = Pos - 1;
		int Le_Ans = Pos;
		while (Le <= Ri){
			Mid = (Le + Ri) >> 1;
			if (Lcp(Mid + 1, Pos) >= Len[i]){
				Le_Ans = Mid;
				Ri = Mid - 1;
			} else Le = Mid + 1;
		}
		Le = Pos + 1; Ri = len;
		int Ri_Ans = Pos;
		while (Le <= Ri){
			Mid = (Le + Ri) >> 1;
			if (Lcp(Pos + 1, Mid) >= Len[i]){
				Ri_Ans = Mid;
				Le = Mid + 1;
			} else Ri = Mid - 1;
		}
		printf("%d\n", Pos - Le_Ans + Ri_Ans - Pos + 1);
	}
	
	return 0;
}