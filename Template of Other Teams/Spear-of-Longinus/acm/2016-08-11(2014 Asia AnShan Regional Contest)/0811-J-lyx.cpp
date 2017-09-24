//0813 liuyuxi 16:15 -- 16:58
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 15;
const int S = 120005;
const int Mo = 1000000007;

int n, Total, Up;
int Broken[N];
int Ans[N];
int Pow[N];
char s[N];
int f[N][S];
int flag[N];

void Clear(int x){
    for (int i = 0; i < Pow[Up]; i++)
        f[x][i] = 0;
}

void Work(int Size){
    
    Up = n - Size + 1;
    
    Pow[0] = 1;
    for (int i = 1; i <= Up; i++)
        Pow[i] = Pow[i - 1] * Size;
    
    
    Clear(0);
    f[0][0] = 1;
    
    for (int i = 1; i <= n; i++){
        Clear(i);
        for (int Cur = 0; Cur < (1 << n); Cur++){
            if (Cur & Broken[i]) continue;
            
            for (int j = 1; j <= Up; j++)
                flag[j] = 0;
            
            for (int k = 1; k <= n; k++){
                if (Cur & (1 << (k - 1))) continue;
                
                for (int j = 1; j <= Up; j++)
                    if (k >= j && k < j + Size) flag[j] = 1;
                
            }
            
            for (int Sta = 0; Sta < Pow[Up]; Sta++){
                if (f[i - 1][Sta] == 0) continue;
                
                int Nsta = 0;
                for (int j = 1; j <= Up; j++){
                    int x = Sta / Pow[j - 1] % Size;
                    
                    if (flag[j]) x = 0;
                    else if (x != Size - 1) x++;
                    else {
                        Nsta = -1;
                        break;
                    }
                    Nsta += x * Pow[j - 1];
                }
                
                if (Nsta == -1) continue;
                f[i][Nsta] = (f[i][Nsta] + f[i - 1][Sta]) % Mo;
            }
            
            
        }
        
    }
    Ans[Size] = 0;
    for (int Sta = 0; Sta < Pow[Up]; Sta++)
        Ans[Size] = (Ans[Size] + f[n][Sta]) % Mo;

    
    Ans[Size] = (Total - Ans[Size] + Mo) % Mo;
    Ans[Size - 1] = (Ans[Size - 1] - Ans[Size] + Mo) % Mo;
}

int main(){
    int Case;
    scanf("%d", &Case);
    
    while (Case --){
        scanf("%d", &n);
        
        for (int i = 1; i <= n; i++) Broken[i] = 0;
        
        Total = 1;
        for (int i = 1; i <= n; i++){
            scanf("%s", s + 1);
            
            
            for (int j = 1; j <= n; j++)
                if (s[j] == 'o')
                    Total = (Total + Total) % Mo;
                else
                    Broken[i] += (1 << (j - 1));
            
        }
        
        Ans[0] = 1;
        Ans[1] = (Total - 1 + Mo) % Mo;
        
        for (int Size = 2; Size <= n; Size++){
            Work(Size);
        }
        
        for (int Size = 0; Size <= n; Size++)
            printf("%d\n", Ans[Size] % Mo);
    }
    
    return 0;
}


