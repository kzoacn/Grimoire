#include <bits/stdc++.h>
#include <unistd.h>
#define y1 Y12312312
using namespace std;

const int R = 30;
int cnt, x1[1111111], y1[1111111], x2[1111111], y2[1111111], r[1111111];

inline int get_num(int r) {
	return rand() % (2 * r + 1) - r;
}

inline int dis2(int x, int y) {
	return x * x + y * y;
}

int main() {
	/*srand(time(0) ^ getpid());
	int cs = 1000;
	cout << cs << endl;
	for (; cs; --cs) {
		int r = rand() % 5 + 2;
		cout << r << endl;
		int x1 = get_num(r), y1 = get_num(r), x2 = get_num(r), y2 = get_num(r);
		while (x1 * x1 + y1 * y1 != x2 * x2 + y2 * y2 || x2 * x2 + y2 * y2 > r * r) {
			x1 = get_num(r);
			y1 = get_num(sqrt(r * r - x1 * x1));
			x2 = get_num((int)sqrt(x1 * x1 + y1 * y1));
			y2 = sqrt(x1 * x1 + y1 * y1 - x2 * x2);
			//cout << r << " ----- " << x1 << endl;
		}
		cout << x1 << " " << y1 << endl;
		cout << x2 << " " << y2 << endl;
	}*/
	cnt = 0;
	for (int _r = 56; _r <= 60; ++_r) {
		for (int _x1 = -_r; _x1 <= _r; ++_x1) {
			for (int _y1 = -_r; _y1 <= _r; ++_y1) {
				if (dis2(_x1, _y1) > _r * _r) {
					continue;
				}
				for (int _x2 = -_r; _x2 <= _r; ++_x2) {
					for (int _y2 = -_r; _y2 <= _r; ++_y2) {
						if (dis2(_x2, _y2) != dis2(_x1, _y1)) {
							continue;
						}
						r[++cnt] = _r;
						x1[cnt] = _x1;
						y1[cnt] = _y1;
						x2[cnt] = _x2;
						y2[cnt] = _y2;
					}
				}
			}
		}
	}
	
	cout << cnt << endl;
	for (int i = 1; i <= cnt; ++i) {
		cout << r[i] << endl;
		cout << x1[i] << " " << y1[i] << endl;
		cout << x2[i] << " " << y2[i] << endl;
		cout << endl;
	}
}
