import random
import sys

sys.stdout = open('E.in', 'w')

n = 100

print(n)
for i in range(n):
	print(random.randint(-10 ** 8, 10 ** 8) / 100, end = ' ')
print()
