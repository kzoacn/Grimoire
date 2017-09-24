#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 115;

char str[N][3];

int main(){
	
	for (int i = 1; i <= 114; i++){
		scanf("%s", str[i]);
	}
	
	for (int i = 1; i <= 114; i++){
		for (int j = 0; j < strlen(str[i]); j++)
			printf("ans[%d][%d] = \'%c\'; ", i, j, str[i][j]);
		printf("\n");
	}
	
	return 0;
}
