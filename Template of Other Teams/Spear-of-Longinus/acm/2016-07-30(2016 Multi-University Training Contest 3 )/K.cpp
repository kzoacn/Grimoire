#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<map>

using namespace std;

const int N = 100005;


pair<int, int> tmp[N];

map<int, bool> Q;
map<pair<int, int>, bool> Hash;
void work() {
	int n, r;
	scanf("%d%d", &n, &r);
	Hash.clear();
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &tmp[i].first, &tmp[i].second);
		if(Hash.count(make_pair(tmp[i].first, tmp[i].second))) {
			n--;
		}
		Hash[make_pair(tmp[i].first, tmp[i].second)] = true;
	}
	Q.clear();
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			int t = abs(tmp[i].first - tmp[j].first) + abs(tmp[i].second - tmp[j].second);
			if(Q.count(t)) {
				puts("YES");
				return ;
			} 
			Q[t] = true;
			
		}
	}
	puts("NO");
	return ;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++) {
		work();
	}
	return 0;
}
