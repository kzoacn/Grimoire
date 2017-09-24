import sys

sys.stdout = open('B.in', 'w')

print(1)

n = 100000

print(n)
for i in range(1, n):
	print(i + 1, 2)

