import random

f = open('g.in', 'w')

T = 1

f.write('{}\n'.format(T))

for kase in range(T):
	edges = set()
	n, m = 10 ** 5, 10 ** 5
	f.write('{} {}\n'.format(n, m))
	for i in range(m):
		u, v = random.randint(1, n), random.randint(1, n)
		while u == v or (u, v) in edges:
			u, v = random.randint(1, n), random.randint(1, n)
		edges.add((u, v))
		f.write('{} {}\n'.format(u, v))
