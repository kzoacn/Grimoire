#include <bits/stdc++.h>
using namespace std;

int a[111];
int cs;

inline bool check() {
	for (int i = 0; i < 24; i += 4) {
		if (a[i] != a[i + 1] || a[i] != a[i + 2] || a[i] != a[i + 3]) {
			return false;
		}
	}
	return true;
}

inline int& get(char x) {
	return a[x - 'a'];
}

inline void go(char x, char y, char z, char w) {
	int t = get(x);
	get(x) = get(y);
	get(y) = get(z);
	get(z) = get(w);
	get(w) = t;
}

inline void turn1() {
	go('r', 'e', 'w', 'p');
	go('t', 'f', 'u', 'o');
}

inline void turn2() {
	go('a', 'e', 'i', 'm');
	go('c', 'g', 'k', 'o');
}

inline void turn3() {
	go('a', 'u', 'l', 'q');
	go('b', 'v', 'k', 'r');
}

int main() {
	cin >> cs;
	for (; cs; --cs) {
		for (int i = 0; i < 24; ++i) {
			scanf("%d", &a[i]);
		}
		
		bool flag = check();
		turn1();
		flag |= check();
		turn1();
		turn1();
		flag |= check();
		turn1();
		
		turn2();
		flag |= check();
		turn2();
		turn2();
/*for (int i = 0; i < 24; i += 4) {
	cout << a[i] << " " << a[i + 1] << " " << a[i + 2] << " " << a[i + 3] << endl;
}
cout << endl;*/
		flag |= check();
		turn2();
		
		turn3();
		flag |= check();
		turn3();
		turn3();
		flag |= check();
		turn3();
		if (flag) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
}
