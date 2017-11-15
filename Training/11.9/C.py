from math import gcd
"""
def gcd(x, y):
	while y > 0:
		if y + y > x:
			x, y = y, x - y
		else:
			x, y = y, x % y
	return x
"""
n, m = map(int, input().split())
a, b = 1, 1
for x in list(map(int, input().split())):
	a *= x
for x in list(map(int, input().split())):
	b *= x
gg = gcd(a, b)
a //= gg
b //= gg


