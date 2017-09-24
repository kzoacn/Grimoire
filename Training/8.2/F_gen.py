import sys
import random

sys.stdout = open('F.in', 'w')

n, k = 59999, 60000

print(n, k)
for i in range(n):
	print(random.randint(1, 10 ** 7), end = ' ')
print()
for i in range(k):
	l = random.randint(1, n)
	r = random.randint(l, n)
	print(l, r)
print(0, 0)
