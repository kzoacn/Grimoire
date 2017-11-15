import random

n, k = 100, 15

m = n - 1

print(n, m, k)

for i in range(n):
	print(random.randint(0, k - 1), end = ' ')
for i in range(n):
	print(random.randint(0, k - 1), end = ' ')
for i in range(2, n + 1):
	print(i, random.randint(1, i - 1))
