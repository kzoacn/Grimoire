#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

int n, m;

int main() {
	srand(time(0) ^ getpid());
	
	int T = 2;
	
	cout << T << endl;
	for (int kase = 1; kase <= T; ++kase) {
		n = 200, m = 100;
		
		cout << n << " " << m << endl;
		
		for (int i = 1; i <= n; ++i) {
			int len = rand() % 10 + 1;
			while (len--) putchar(rand() % 4 / 3 + 'a');
			cout << endl;
		}
		
		for (int i = 1; i <= m; ++i) {
			int len = 3;
			while (len--) putchar(rand() % 4 / 3 + 'a');
			cout << " ";
			
			len = 4;
			while (len--) putchar(rand() % 4 / 3 + 'a');
			cout << endl;
		}
	}
	
	return 0;
}
