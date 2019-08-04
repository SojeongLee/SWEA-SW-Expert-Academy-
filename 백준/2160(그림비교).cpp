#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	int N;
	scanf("%d", &N);

	string p[50][5];
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < 5; k++)
			cin >> p[i][k];
	}

	int n1, n2, min = 35;
	//비교 (0-1, 0-2, 0-3 ,,, 1-2, 1-3 , 1-4 ,,, N-2-N-1)
	for (int i = 0; i < N - 1; i++)
	{
		for (int k = i + 1; k < N; k++)
		{
			int cnt = 0;
			for (int a = 0; a < 5; a++)
			{
				for (int b = 0; b < 7; b++)
				{
					if (p[i][a][b] != p[k][a][b])
						cnt++;
				}
			}
			if (min > cnt)
			{
				n1 = i, n2 = k;
				min = cnt;
			}
		}
	}

	printf("%d %d\n", n1 + 1, n2 + 1);


	return 0;//Your program should return 0 on normal termination.
}

/*
그림이 char 이차원배열이고 이 그림들을 비교하는 것이므로 결국 char 3차원 배열이 된다. 
char이차원배열이 싫어서, 그림자체를 string 배열로 구성하여서, string 2차원 배열로 저장하였다.
//비교 (0-1, 0-2, 0-3 ,,, 1-2, 1-3 , 1-4 ,,, N-2-N-1)
그림을 모두 한 번씩 비교하여, 최솟값을 업데이트해가며 정답을 구했다.
*/
