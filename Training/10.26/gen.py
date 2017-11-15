import sys
import random

sys.stdout = open('D.in', 'w')

n, m = 500, 10000

for T in range(10):
	print(n, m)
	for e in range(m):
		u, v = 0, 0
		while u == v:
			u, v = random.randint(1, 30), random.randint(1, n)
		print(u, v)

