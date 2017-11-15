from math import sqrt

def Halen(a, b, c):
	p = (a + b + c) / 2
	return sqrt(p * (p - a) * (p - b) * (p - c))

caseCnt = int(input())
for kase in range(caseCnt):
	n, c = map(int, input().split())
	a = sorted(list(map(int, input().split())))
	
	ans = 1e60
	for i in range(2, n):
		for j in reversed(range(1, i)):
			if a[0] + a[j] <= a[i]:
				break
			ans = min(ans, Halen(a[0], a[j], a[i]))
	print(ans if ans != 1e60 else -1)
