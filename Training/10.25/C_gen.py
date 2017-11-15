import sys
import random

sys.stdout = open('C.in', 'w')

n = 5000

print(n)

for i in range(n):
	print(random.randint(1, n), end = ' ')
print()
