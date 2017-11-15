#include <bits/stdc++.h>
using namespace std;

int a[111], b[111][111], p[111], n, ans;

inline bool check(int m) {
	for (int i = 1; i <= n; ++i) {
		p[i] = i;
	}
	bool flag = false;
	do {
		bool nowf = true;
		for (int i = 1, x = 1, y = 1; i <= n; ++i) {
			if (p[i] % 2 == (x + y) % 2) {
				nowf = false;
				break;
			}
			b[x][y] = p[i];
			if (y == a[x]) {
				++x;
				y = 1;
			} else {
				++y;
			}
		}
		if (!nowf) {
			continue;
		}
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= a[i]; ++j) {
				if (j < a[i] && b[i][j] > b[i][j + 1]) {
					nowf = false;
					break;
				}
				if (i < m && a[i + 1] >= j && b[i][j] > b[i + 1][j]) {
					nowf = false;
					break;
				}
			}
			if (!nowf) {
				break;
			}
		}
		if (nowf) {
			flag = true;
			break;
		}
	} while (next_permutation(p + 1, p + n + 1));
	return flag;
	if (flag) {
		++ans;
		//cout << "-----bomb------" << endl;
		//for (int i = 1; i <= m; ++i) cout << a[i] << " ";
		//cout << endl;
	}
}
/*
inline void check(int m) {
	int now = 0;
	for (int i = 1; i <= m; ++i) {
		if (a[i] != 2) {
			for (int j = 1; j <= a[i]; ++j) {
				b[i][j] = ++now;
			}
		} else {
			int x = now + 1, y = x + 1;
			now += 2;
			if (x % 2 == 1) {
				swap(x, y);
			}
			if (i % 2 == 0) {
				b[i][1] = x;
				b[i][2] = y;
			} else {
				b[i][1] = y;
				b[i][2] = x;
			}
		}
	}
	bool flag = true;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= a[i]; ++j) {
			if (j < a[i] && b[i][j] > b[i][j + 1]) {
				flag = false;
				break;
			}
			if (i < m && a[i + 1] >= j && b[i][j] > b[i + 1][j]) {
				flag = false;
				break;
			}
		}
		if (!flag) {
			break;
		}
	}
	if (!flag) {
		++ans;
		cout << "-----bomb------" << endl;
		for (int i = 1; i <= m; ++i) cout << a[i] << " ";
		cout << endl;
	}
}*/

int test_ans;



bool test(int m){
//	static int b[222][222];
	
	// a1 - am: count of each line
	
	static int ideg[55][55];
	static bool yes[55][55];
	
	memset(ideg, 0, sizeof ideg);
	memset(yes, 0, sizeof yes);
	
	static queue<pair<int, int> > odd, even;
	
	while (!odd.empty()) odd.pop();
	while (!even.empty()) even.pop();
	
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= a[i]; ++j) {
			yes[i][j] = 1;
		}
	}
	
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= a[i]; ++j) {
			ideg[i][j] = (int)yes[i + 1][j] + yes[i][j + 1];
			if (!ideg[i][j]) {
				if ((i + j) % 2 == 0) odd.push(make_pair(i, j));
				else even.push(make_pair(i, j));
			}
		}
	}
	
	int drct[2][2] = {{-1, 0}, {0, -1}};
	
	int done = n;
	
	while (done) {
		static pair<int, int> now;
		if (!(done & 1)) { // even
			if (even.empty()) break;
			now = even.front(); even.pop();
		}
		else { // odd
			if (odd.empty()) break;
			now = odd.front(); odd.pop();
		}
		--done;
		for (int t = 0; t < 2; ++t) {
			int x = now.first + drct[t][0], y = now.second + drct[t][1];
			if (!yes[x][y]) continue;
			if (!--ideg[x][y]) {
				if ((x + y) % 2 == 0) odd.push(make_pair(x, y));
				else even.push(make_pair(x, y));
			}
		}
	}
	
	return done == 0;
	
	/*odd=1;even=2;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=a[i];j++){
			if(!((i+j)&1)){
				if(odd>n)return false; 
				b[i][j]=odd;
				odd+=2;
			}else{
				if(even>n)return false;
				b[i][j]=even;
				even+=2;
			}
		}
	}*/
	
	
	/*for(auto p:vec){
		int i=p.second.first;
		int j=p.second.second;
		if(!((i+j)&1)){
			if(odd<1)return false; 
			b[i][j]=odd;
			odd-=2;
		}else{
			if(even<2)return false;
			b[i][j]=even;
			even-=2;
		}
	}*/
	/*for(int i=m;i>=1;i--){
		for(int j=a[i];j>=1;j--){
			if(!((i+j)&1)){
				if(odd<1)return false; 
				b[i][j]=odd;
				odd-=2;
			}else{
				if(even<2)return false;
				b[i][j]=even;
				even-=2;
			}
		}
	}*/
	
	
	for(int i=1;i<=m;i++){
		for(int j=1;j<=a[i];j++){
			if(i&&b[i][j]<b[i-1][j])
				return false;
			if(j&&b[i][j]<b[i][j-1])
				return false;
		}
	}
	return true;
}

inline void dfs(int dep, int last, int left) {
	if (left == 0) {
		if(check(dep - 1))
			ans++;
		int odd = 0, even = 0;
		for (int i = 1; i <= dep - 1; ++i) {
			for (int j = 1; j <= a[i]; ++j) {
				if ((i + j) % 2 == 0) {
					++odd;
				} else {
					++even;
				}
			}
		}

/*for (int i = 1; i <= dep - 1; ++i) cout << a[i] << " ";
cout << endl;
printf("even = %d  odd = %d\n", even, odd);*/
		if (abs(odd - even) > 1) {
			return;
		}
		/*if (!check(dep - 1)) {
for (int i = 1; i <= dep - 1; ++i) cout << a[i] << " ";
cout << endl;
		}*/
		
		
		if(test(dep-1))
			test_ans++;
		
		
		return;
	}
	for (int i = 1; i <= left && i <= last; ++i) {
		a[dep] = i;
		dfs(dep + 1, i, left - i);
	}
}

int main() {
//	cin >> n;
	
	for(n=1;n<=10;n++){
		ans=0;
		test_ans=0;
		dfs(1, n, n);
		
		cout <<n<<" "<< ans << " "<<test_ans<<endl;
	}
}

