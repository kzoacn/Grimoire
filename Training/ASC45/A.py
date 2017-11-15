import sys

sys.stdin = open('analogous.in', 'r')
sys.stdout = open('analogous.out', 'w')

while True:
	n = int(input())
	if n == 0:
		exit()
	if n > 2:
		print('No')
	else:
		print('Yes\n1 4\n2 3')
