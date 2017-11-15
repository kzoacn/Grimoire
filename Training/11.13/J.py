import random
import math

eps = 1e-8

def sgn(x):
	return -1 if x < -eps else int(x > eps)

def Random(l, r):
	return random.random() * (r - l) + l

n, w, h = 0, 0, 0
p = []

class Vector:
	def __init__(self, x, y):
		self.x = x
		self.y = y
	
	def __add__(self, oth):
		return Vector(self.x + oth.x, self.y + oth.y)
	
	def __sub__(self, oth):
		return Vector(self.x - oth.x, self.y - oth.y)
	
	def __str__(self):
		return '{0} {1}'.format(round(self.x, 9), round(self.y, 9))
	
	def length(self):
		return math.sqrt(self.x ** 2 + self.y ** 2)
	
	def unit(self):
		return Vector(self.x / self.length(), self.y / self.length())
	
	def times(self, t):
		return Vector(self.x * t, self.y * t)
	
	def norm(self, t):
		return Vector(-self.y, self.x).unit().times(t * random.choice([-1, 1]))
	
	def cross(a, b):
		return a.x * b.y - a.y * b.x
	
	def randomVector():
		i = random.randint(0, n - 1)
		j = random.randint(0, 2)
		
		x = 0 if j != 0 else 1
		y = 1 if j == 2 else 2
		
		tmp = Random(0, (p[i][y] - p[i][x]).length())
		rd_p = p[i][x] + (p[i][y] - p[i][x]).unit().times(tmp)
#		x_delta, y_delta = random.random(), random.random()
#		rd_p += Vector(x_delta, y_delta)
		rd_p += rd_p.norm(random.random())
		if 0 <= rd_p.x <= w and 0 <= rd_p.y <= h:
			return rd_p
		return Vector(Random(0, w), Random(0, h))

def main():
	global n, w, h
	n, w, h = map(int, input().split())
	for i in range(n):
		tri = []
		xy = list(map(int, input().split()))
		for j in range(0, 6, 2):
			tri.append(Vector(xy[j], xy[j + 1]))
		p.append(tri)
	f = [0 for i in range(3)]
	for T in range(100):
		rd_p = Vector.randomVector()
		flag = True
		for i in range(n):
			for j in range(3):
				f[j] = sgn(Vector.cross(rd_p - p[i][j], p[i][(j + 1) % 3] - rd_p))
			f.sort()
			if f[0] != -1 or f[2] != 1:
				flag = False
				break
		if flag:
			print(rd_p)
			exit()

if __name__ == '__main__':
	main()
