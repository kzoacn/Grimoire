import random

n, m = 5000, 5000
"""
f1, f2 = 1, 1

while f1 + f2 <= 10 ** 18:
	f1, f2 = f2, f1 + f2
"""
print(n, m)
for i in range(n):
	print(random.randint(10 ** 15, 10 ** 18), end = ' ')
print()
for i in range(m):
	print(random.randint(10 ** 12, 10 ** 15), end = ' ')
print()
