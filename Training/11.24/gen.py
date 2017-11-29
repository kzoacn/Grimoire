def main():
	n = int(input())
	m = n * (n - 1) // 2
	
	print(1)
	print(n, m)
	for i in range(1, n + 1):
		for j in range(i + 1, n + 1):
			print(i, j)

if __name__ == '__main__':
	main()
