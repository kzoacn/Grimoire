#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define rank RANK

using namespace std;

struct node{
	char rank, suit;
};

struct node1{
	int rank;
	int size;
};

char suit[20];
char rank[20];

node a[20], b[20], A[20], B[20], Cur[20], Now[20], AnsA[20], AnsB[20];
node com[20], river[20], turn[20];

int id;

node1 sa[20], sb[20];
int Aid, Bid;
int AA, BB;

int Trans[300];

char s[20];

bool same(node a, node b){
	if (a.rank != b.rank) return 0;
	if (a.suit != b.suit) return 0;
	return 1;
}

bool cmp(node a, node b){
	return Trans[a.rank] > Trans[b.rank];
}

bool cmp1(node1 a, node1 b){
	if (a.size > b.size) return 1;
	if (a.size < b.size) return 0;
	if (a.rank > b.rank) return 1;
	if (a.rank < b.rank) return 0;
	return 0;
}

bool Col(int l, int r){
	for (int i = l + 1; i <= r; i++)
		if (Now[i].suit != Now[i - 1].suit) return 0;
	return 1;
}

bool Num(int l, int r){
	for (int i = l + 1; i <= r; i++)
		if (Now[i].rank != Now[i - 1].rank) return 0;
	return 1;
}

bool Rank(int l, int r, int L){
	for (int i = l; i <= r; i++)
		if (Trans[Now[i].rank] != L - (i - l)) return 0;
	return 1;
}


int Get(){
	//1
	if (Col(1, 5) && Rank(1, 5, 14)){
		return 1;
	}
	//2
	if (Col(1, 5)){
		if (Rank(1, 5, Trans[Now[1].rank])){
			return 2;
		}
		if (Now[1].rank == 'A' && Now[5].rank == '2' && Rank(2, 4, 5)){
			return 2;
		}
	}
	//3
	if (Num(1, 4) || Num(2, 5)){
		return 3;
	}
	//4
	if ((Num(1, 3) && Num(4, 5)) || (Num(1, 2) && Num(3, 5))){
		return 4;
	}
	//5
	if (Col(1, 5)){
		return 5;
	}
	//6
	if (Rank(1, 5, Trans[Now[1].rank])){
		return 6;
	}
	if (Now[1].rank == 'A' && Now[5].rank == '2' && Rank(2, 4, 5)){
		return 6;
	}
	//7
	if (Num(1, 3) || Num(2, 4) || Num(3, 5)){
		return 7;
	}
	//8
	if ((Num(1, 2) && Num(3, 4)) || (Num(1, 2) && Num(4, 5)) || (Num(2, 3) && Num(4, 5))){
		return 8;
	}
	//9
	if (Num(1, 2) || Num(2, 3) || Num(3, 4) || Num(4, 5)){
		return 9;
	}
	//10
	return 10;
}

bool best(){
	if (AA < BB) return 1;
	if (AA > BB) return 0;
	
	int cntA = 1;
	sa[1].rank = Trans[A[1].rank];
	sa[1].size = 1;
	
	for (int i = 2; i <= 5; i++){
		if (A[i].rank != A[i - 1].rank){
			++cntA;
			sa[cntA].rank = Trans[A[i].rank];
			sa[cntA].size = 1;
		} else
			sa[cntA].size++;
	}
	
	int cntB = 1;
	sb[1].rank = Trans[B[1].rank];
	sb[1].size = 1;
	
	for (int i = 2; i <= 5; i++){
		if (B[i].rank != B[i - 1].rank){
			++cntB;
			sb[cntB].rank = Trans[B[i].rank];
			sb[cntB].size = 1;
		} else
			sb[cntB].size++;
	}
	
	sort(sa + 1, sa + 1 + cntA, cmp1);
	sort(sb + 1, sb + 1 + cntB, cmp1);
	
	if (AA == 1){
		return 0;
	}
	if (AA == 2 || AA == 6){
		if (sa[1].rank == 14 && sa[2].rank == 5){
			sa[1].rank = 1;
			sort(sa + 1, sa + 1 + cntA, cmp1);
		}
		if (sb[1].rank == 14 && sb[2].rank == 5){
			sb[1].rank = 1;
			sort(sb + 1, sb + 1 + cntB, cmp1);
		}
		
		if (sa[1].rank > sb[1].rank) return 1;
		return 0;
	}
	
	for (int i = 1; i <= cntA; i++){
		if (sa[i].rank > sb[i].rank) return 1;
		if (sa[i].rank < sb[i].rank) return 0;
	}
	return 0;
}

void Find_a(){
	
	for (int i = 1; i <= 2; i++)
		Cur[i] = a[i];
	for (int i = 1; i <= 3; i++)
		Cur[2 + i] = com[i];
	Cur[6] = turn[1];
	Cur[7] = river[1];
	
	sort(Cur + 1, Cur + 1 + 7, cmp);
	
	Aid = 9999;
	for (int d0 = 1; d0 <= 7; d0++)
		for (int d1 = d0 + 1; d1 <= 7; d1++){
			
			int cnt = 0;
		
			for (int i = 1; i <= 7; i++)
				if (i != d0 && i != d1){
					Now[++cnt] = Cur[i];	
				}
				
			id = Get();				
			
			AA = id;
			for (int i = 1; i <= 5; i++)
				A[i] = Now[i];
			BB = Aid;
			for (int i = 1; i <= 5; i++)
				B[i] = AnsA[i];
			
			if (best()){
				Aid = id;
				for (int i = 1; i <= 5; i++)
					AnsA[i] = Now[i];
			}
			
		}
	
}

void Find_b(){
	
	for (int i = 1; i <= 2; i++)
		Cur[i] = b[i];
	for (int i = 1; i <= 3; i++)
		Cur[2 + i] = com[i];
	Cur[6] = turn[1];
	Cur[7] = river[1];
	
	sort(Cur + 1, Cur + 1 + 7, cmp);
	
	Bid = 9999;
	for (int d0 = 1; d0 <= 7; d0++)
		for (int d1 = d0 + 1; d1 <= 7; d1++){
			
			int cnt = 0;
		
			for (int i = 1; i <= 7; i++)
				if (i != d0 && i != d1){
					Now[++cnt] = Cur[i];	
				}
				
			id = Get();				
			
			AA = id;
			for (int i = 1; i <= 5; i++)
				A[i] = Now[i];
			BB = Bid;
			for (int i = 1; i <= 5; i++)
				B[i] = AnsB[i];
			
			if (best()){
				Bid = id;
				for (int i = 1; i <= 5; i++)
					AnsB[i] = Now[i];
			}
			
		}
	
}

bool Check(){

	Find_a();
	Find_b();
	
	AA = Aid;
	BB = Bid;
	for (int i = 1; i <= 5; i++){
		A[i] = AnsA[i];
		B[i] = AnsB[i];
	}
	
	if (best()) return 1;
	return 0; 

}

int main(){
	
	suit[1] = 'S'; suit[2] = 'H'; suit[3] = 'D'; suit[4] = 'C';
	rank[1] = 'A';
	for (int i = 2; i <= 9; i++)
		rank[i] = '0' + i;
	rank[10] = 'T';
	rank[11] = 'J';
	rank[12] = 'Q';
	rank[13] = 'K';
	rank[14] = 'A'; 
	
	//rank
	for (char ch = '2'; ch <= '9'; ch++)
		Trans[ch] = ch - '0';
	
	Trans['T'] = 10;
	Trans['J'] = 11;
	Trans['Q'] = 12;
	Trans['K'] = 13;
	Trans['A'] = 14;
	//suit
	Trans['S'] = 4;
	Trans['D'] = 3;
	Trans['H'] = 2;
	Trans['C'] = 1;
	
	while (1){
		///A
		scanf("%s", s + 1);
		if (s[1] == '#') break;
		
		a[1].suit = s[1];
		a[1].rank = s[2];
		
		scanf("%s", s + 1);
		
		a[2].suit = s[1];
		a[2].rank = s[2];
		
		///B
		scanf("%s", s + 1);
		
		b[1].suit = s[1];
		b[1].rank = s[2];
		
		scanf("%s", s + 1);
		
		b[2].suit = s[1];
		b[2].rank = s[2];
		
		///COM
		scanf("%s", s + 1);
		
		com[1].suit = s[1];
		com[1].rank = s[2];
		
		scanf("%s", s + 1);
		
		com[2].suit = s[1];
		com[2].rank = s[2];
		
		scanf("%s", s + 1);
		
		com[3].suit = s[1];
		com[3].rank = s[2];
		
		///turn
		
		int Cnt = 0;
		int Ans = 0;
		for (int i = 1; i <= 4; i++){
			turn[1].suit = suit[i];
			for (int j = 1; j <= 13; j++){
				turn[1].rank = rank[j];
				for (int k = 1; k <= 4; k++){
					river[1].suit = suit[k];
					for (int l = 1; l <= 13; l++){
						river[1].rank = rank[l];
						
						bool flag = 1;
						//Check same(a, r, t)
						for (int i = 1; i <= 2; i++)
							Cur[i] = a[i];
						for (int i = 1; i <= 3; i++)
							Cur[2 + i] = com[i];
						Cur[6] = turn[1];
						Cur[7] = river[1];
						
						for (int i = 1; i <= 7; i++){
							for (int j = i + 1; j <= 7; j++)
								if (same(Cur[i], Cur[j])){
									flag = 0;
									break;
								}
							if (!flag) break;
						}
						//Check same(b, r, t)
						for (int i = 1; i <= 2; i++)
							Cur[i] = b[i];
						for (int i = 1; i <= 3; i++)
							Cur[2 + i] = com[i];
						Cur[6] = turn[1];
						Cur[7] = river[1];
						
						for (int i = 1; i <= 7; i++){
							for (int j = i + 1; j <= 7; j++)
								if (same(Cur[i], Cur[j])){
									flag = 0;
									break;
								}
							if (!flag) break;
						}
						////
						
						if (!flag) continue;
						
						++Cnt;
						
						if (Check()){
							++Ans;
						}
						
					}
				}
			}
		}
		
		printf("%.10f\n", 1.0 * Ans / Cnt);
	}
	
	return 0;
}


