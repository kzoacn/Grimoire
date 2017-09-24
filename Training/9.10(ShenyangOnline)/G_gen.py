import random

T = 10

print(T)
for tt in range(T):
	n = 10**5 - random.randint(2,1000)
	m = 10**5
	q = 10**5
	
	print(n, m)
	for i in range(2, n + 1):
		print(i, random.randint(1, i - 1))
	for i in range(m - (n - 1)):
		print(random.randint(1, n), random.randint(1, n))
	print(q)
	for i in range(q):
		print(random.randint(1, 2), random.randint(1, n), random.randint(1, n))
