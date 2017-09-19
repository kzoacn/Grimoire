import random

T = 10

for tt in range(T):
	n = 10 ** 6
	print(n)
	for i in range(n):
		print(random.randint(0, 1000), end = ' ')
	print()
	for i in range(n):
		print(random.randint(1, 1000), end = ' ')
	print()
	
