import random

s = 'qwertyuiopasdfghjklzxcvbnm'

T = 20

print(T)
for kase in range(T):
	n = 50000
	
	print(n)
	for i in range(n):
		length = random.randint(1, 10)
		for j in range(length):
			print(s[random.randint(0, 25)], end = '')
		print()

