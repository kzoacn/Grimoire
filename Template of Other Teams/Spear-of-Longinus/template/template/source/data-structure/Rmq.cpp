for (int i = 1; i <= n; i++)
	Log[i] = int(log2(i));
	
for (int i = 1; i <= n; i++)
	Rmq[i][0] = i;

for (int k = 1; (1 << k) <= n; k++)
	for (int i = 1; i + (1 << k) - 1 <= n; i++){
		int x = Rmq[i][k - 1], y = Rmq[i + (1 << (k - 1))][k - 1];
		if (a[x] < a[y])
			Rmq[i][k] = x;
		else
			Rmq[i][k] = y;
	}

int Smallest(int l, int r){
	int k = Log[r - l + 1];
	
	int x = Rmq[l][k];
	int y = Rmq[r - (1 << k) + 1][k];
	
	if (a[x] < a[y]) return x;
	else return y;
}