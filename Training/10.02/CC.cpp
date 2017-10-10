#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;

pair<ll, int> wpmx[10005];

ll wp[10005][4][4], wp2[7][4][4]; // wp2[1 ~ n][0 ~ 3][0 ~ 3]
int id[111][111];

ll ans;

void Random() {
	int T = 100000;
	
	while (T--) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= 4; ++j) {
				id[i][j] = j - 1;
			}
			random_shuffle(id[i] + 1, id[i] + 5);
		}
		
		ll nowans = 0;
		ll mx = 0; //1
		for (int i = 1; i <= n; ++i) {
			mx = max(mx, wp2[i][id[i][1]][id[i][2]]);
			mx = max(mx, wp2[i][id[i][3]][id[i][4]]);
		}
		nowans += mx;
		
		mx = 0; // 2
		for (int i = 1; i <= n; ++i) {
			mx = max(mx, wp2[i][id[i][1]][id[i][3]]);
			mx = max(mx, wp2[i][id[i][2]][id[i][4]]);
		}
		nowans += mx;
		
		mx = 0; // 3
		for (int i = 1; i <= n; ++i) {
			mx = max(mx, wp2[i][id[i][1]][id[i][4]]);
			mx = max(mx, wp2[i][id[i][2]][id[i][3]]);
		}
		nowans += mx;
		
		mx = 0; // 4
		for (int i = 1; i <= n; ++i) {
			mx = max(mx, wp2[i][id[i][2]][id[i][1]]);
			mx = max(mx, wp2[i][id[i][4]][id[i][3]]);
		}
		nowans += mx;
		
		mx = 0; // 5
		for (int i = 1; i <= n; ++i) {
			mx = max(mx, wp2[i][id[i][3]][id[i][1]]);
			mx = max(mx, wp2[i][id[i][4]][id[i][2]]);
		}
		nowans += mx;
		
		mx = 0; // 6
		for (int i = 1; i <= n; ++i) {
			mx = max(mx, wp2[i][id[i][4]][id[i][1]]);
			mx = max(mx, wp2[i][id[i][3]][id[i][2]]);
		}
		nowans += mx;
		ans = max(ans, nowans);
	}
}

int main() {
	srand(time(0));
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			ll tmpmx = 0;
			for (int x = 0; x < 4; ++x)
				for (int y = 0; y < 4; ++y) {
					scanf("%lld", &wp[i][x][y]);
					if (x == y) continue;
					tmpmx = max(tmpmx, wp[i][x][y]);
				}
			wpmx[i] = make_pair(tmpmx, i);
		}
		
		sort(wpmx + 1, wpmx + n + 1, less<pair<ll, int> >());
		
		n = std::min(n, 6);
		
		for (int i = 1; i <= n; ++i)
			memcpy(wp2[i], wp[wpmx[i].second], sizeof wp[wpmx[i].second]);
		
		ans = 0;
		
		Random();
		
		printf("Case #%d: %lld\n", kase, ans);
	}
	
	return 0;
}
