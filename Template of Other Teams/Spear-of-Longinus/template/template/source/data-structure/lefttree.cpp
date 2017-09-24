int Merge(int x, int y){
  if (x == 0 || y == 0) return x + y;
  if (Heap[x].Key < Heap[y].Key) swap(x, y);
  Heap[x].Ri = Merge(Heap[x].Ri, y);
  if (Heap[Heap[x].Le].Dis < Heap[Heap[x].Ri].Dis) swap(Heap[x].Le, Heap[x].Ri);
  if (Heap[x].Ri == 0) Heap[x].Dis = 0;
  else Heap[x].Dis = Heap[Heap[x].Ri].Dis + 1;
  return x;
}

for (int i = 0; i <= n; i++){
	Heap[i].Le = Heap[i].Ri = 0;
	Heap[i].Dis = 0;
	Heap[i].Key = Cost[i];
}
Heap[0].Dis = -1;
