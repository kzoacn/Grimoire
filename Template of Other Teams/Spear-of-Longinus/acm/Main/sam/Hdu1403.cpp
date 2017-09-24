#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>

using namespace std;

const int N = 300005;

struct node{
	int len, fail;
	int To[27];
}T[N];

char a[N], b[N];
int Lst, Root, tot;

void add(int x, int l){
	int Nt = ++tot, p = Lst;
	T[Nt].len = l;
	for (;p && !T[p].To[x]; p = T[p].fail) T[p].To[x] = Nt;
	if (!p) T[Nt].fail = Root;
	else
	if (T[T[p].To[x]].len == T[p].len + 1) T[Nt].fail = T[p].To[x];
	else{
		int q = ++tot, qt = T[p].To[x];
		T[q] = T[qt];
		T[q].len  = T[p].len + 1;
		T[qt].fail = T[Nt].fail = q;
		for (;p && T[p].To[x] == qt; p = T[p].fail) T[p].To[x] = q;
	}
	Lst = Nt;
}

int main(){
	
	while (scanf("%s%s", a + 1, b + 1) == 2){
		int n = strlen(a + 1);
		
		Lst = Root = tot = 1;
		for (int i = 1; i <= n; i++)
			add(a[i] - 'a' + 1, i);
		
		int m = strlen(b + 1);
		int p = Root, len = 0;
		int Ans = 0;
		
		for (int i = 1; i <= m; i++){
			int x = b[i] - 'a' + 1;
			if (T[p].To[x]) len++, p = T[p].To[x];
			else {
				while (p && !T[p].To[x]) p = T[p].fail;
				if (!p) p = Root, len = 0;
				else len = T[p].len + 1, p = T[p].To[x];
			}
			if (len > Ans) Ans = len;
		}
		
		printf("%d\n", Ans);
		
		for (int i = 1; i <= tot; i++){
			T[i].len = T[i].fail = 0;
			for (int j = 1; j <= 26; j++)
				T[i].To[j] = 0;
		}
		
	}
	
	return 0;
}


