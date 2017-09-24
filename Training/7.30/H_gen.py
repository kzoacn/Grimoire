import sys
import random

sys.stdout = open('H.in', 'w')

n = m = 100

print(1)
print(n, m)
for i in range(n):
	for j in range(m):
		print(random.randint(1, 10 ** 3), end = ' ')
	print()

