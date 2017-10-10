import random

n, m = 10 ** 5, 10 ** 5

print(n, m)
for i in range(n):
	print(random.randint(1, 10 ** 9), end = ' ')
print()
for i in range(2, n + 1):
	print(i, random.randint(1, i - 1))
for i in range(m):
	l = random.randint(1, 10 ** 9)
	r = random.randint(l, 10 ** 9)
	print(random.randint(1, n), random.randint(1, n), l, r)

