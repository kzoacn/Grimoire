#include <bits/stdc++.h>

using namespace std;

ifstream fin;
ofstream fout, ftle;

string s;

int main() {
	system("make G");
	
//	ftle.open("G_tle.txt");
	int cnt = 0;
	for (int i = 1; i <= 11; ++i)
		for (int j = 1; j <= 11; ++j)
			for (int k = 1; k <= 11; ++k) {
				fout.open("G.in");
				fout << i << " " << j << " " << k << endl;
				fout.close();
				system("./G <G.in >G.out");
				fin.open("G.out");
				fin >> s;
				if (s == "TLE") {
					cout << i << " " << j << " " << k << endl;
				}
				fin.close();
				if (++cnt % 100 == 0) {
					cout << cnt << endl;
				}
			}
//	ftle.close();
	
	return 0;
}
