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