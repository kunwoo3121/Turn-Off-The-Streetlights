# Turn-Off-The-Streetlights

https://www.acmicpc.net/problem/2315

# 구현 방법
```
 i)   두개의 2차원 배열이 필요하다. EE1, EE2 두 개의 이차원 배열을 생성한다.
      EE1[L,R] = 초기 상태에서 L ~ R 까지 다 끄고 현재 L에 있을 때까지의 총 소비전력
      EE2[L,R] = 초기 상태에서 L ~ R 까지 다 끄고 현재 R에 있을 때까지의 총 소비전력
 
 ii)  EE1[L,R] = min( EE1[L+1,R] + (D[L+1] - D[L]) * {WS[N] - (WS[R] -WS[L])} , EE2[L+1,R] + (D[R] - D[L]) * {WS[N] - (WS[R] -WS[L])} )
      EE2[L,R] = min( EE1[L,R-1] + (D[R] - D[L]) * {WS[N] - (WS[R-1] -WS[L-1])} , EE2[L,R-1] + (D[R] - D[R-1]) * {WS[N] - (WS[R-1] -WS[L-1])} ) 
      
      * D[i] = i번째 가로등의 위치
        W[i] = i번째 가로등의 1초당 전력 소비량
        WS[i] = W[1] + W[2] + ... + W[i]
        
      위와 같은 식으로 EE1과 EE2의 값을 저장해나간다.
 
 iii) EE1[1,N] 과 EE2[1,N] 둘 중 더 작은 값이 낭비되는 전력의 최솟값이 된다.
```

# 구현 코드
```c
#include<stdio.h>
#include<limits.h>
int main()
{
	int i, j, d[1001], w[1001], n, sp, EE1[1001][1001], EE2[1001][1001], ws[1001] = { 0 }, v1, v2;

	scanf("%d", &n);
	scanf("%d", &sp);
	for (i = 1; i <= n; i++)
	{
		scanf("%d %d", &d[i], &w[i]);
		ws[i] = ws[i - 1] + w[i];
	}

	for (i = 1; i <= n; i++)
	{
		if (i != sp)
		{
			EE1[i][i] = INT_MAX;
			EE2[i][i] = INT_MAX;
		}
		else
		{
			EE1[i][i] = 0;
			EE2[i][i] = 0;
		}
	}

	for (i = 1; i < n; i++)
	{
		for (j = 1; j <= n-i; j++)
		{
			if (EE1[j + 1][j + i] == INT_MAX) v1 = INT_MAX;
			else v1 = EE1[j + 1][j + i] + ((d[j + 1] - d[j]) * ((ws[n] - ws[j + i]) + ws[j]));
			if (EE2[j + 1][j + i] == INT_MAX) v2 = INT_MAX;
			else v2 = EE2[j + 1][j + i] + ((d[j + i] - d[j]) * ((ws[n] - ws[j + i]) + ws[j]));
			if (v1 < v2)
			{
				EE1[j][j + i] = v1;
			}
			else
			{
				EE1[j][j + i] = v2;
			}

			if (EE1[j][j + i - 1] == INT_MAX) v1 = INT_MAX;
			else v1 = EE1[j][j + i - 1] + ((d[j + i] - d[j]) * ((ws[n] - ws[j + i - 1]) + ws[j - 1]));
			if (EE2[j][j + i - 1] == INT_MAX) v2 = INT_MAX;
			else v2 = EE2[j][j + i - 1] + ((d[j + i] - d[j + i - 1]) * ((ws[n] - ws[j + i - 1]) + ws[j - 1]));
			if (v1 < v2)
			{
				EE2[j][j + i] = v1;
			}
			else
			{
				EE2[j][j + i] = v2;
			}
		}
	}

	if (EE1[1][n] < EE2[1][n])
		printf("%d", EE1[1][n]);
	else
		printf("%d", EE2[1][n]);

	return 0;
}
```
