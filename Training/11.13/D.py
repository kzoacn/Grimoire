base = 2 ** 7

def Decode(x):
	return -(x + 1) // 2 if x & 1 else x // 2

def main():
	ans = []
	tmp = 0
	bit = 0
	input()
	for i in list(map(int, input().split())):
		if i < 128:
			tmp += i * base ** bit
			ans.append(Decode(tmp))
			tmp, bit = 0, 0
		else:
			tmp += (i - 128) * base ** bit
			bit += 1
	for i in ans:
		print(i)

if __name__ == '__main__':
	main()
