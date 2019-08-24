#include <iostream>

using namespace std;


int main(int argc, char** argv)
{

	int R, C, T;
	scanf("%d %d %d", &R, &C, &T);

	int map[51][51] = { 0 };
	int A, B; //공기청정기의 행 번호
	for (int i = 0; i < R; i++)
	{
		for (int k = 0; k < C; k++)
		{
			scanf("%d", &map[i][k]);
		}
	}

	//공기청정기 위치 찾기
	for (int i = 0; i < R; i++)
	{
		if (map[i][0] == -1)
		{
			A = i;
			break;
		}
	}
	B = A + 1;

	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };

	for (int t = 0; t < T; t++)
	{
		//미세먼지 확산
		int temp[51][51] = { 0 };
		for (int i = 0; i < R; i++)
		{
			for (int k = 0; k < C; k++)
			{
				if (map[i][k] >= 5) //5이상이어야 퍼져나갈 먼지가 있는 것
				{
					int dust = map[i][k] / 5; //확산 될 미세먼지 양
					int cnt = 0; //확산 될 방향 수
					for (int dir = 0; dir < 4; dir++)
					{
						int tx = i + dx[dir];
						int ty = k + dy[dir];
						if (tx < 0 || ty < 0 || tx >= R || ty >= C)
							continue;
						if (map[tx][ty] != -1) //공기청정기가 아닌 곳으로 확산 됨
						{
							cnt++;
							temp[tx][ty] += dust;
						}
					}
					map[i][k] -= (dust * cnt); //확산된 양만큼 빼줌
				}
			}
		}

		for (int i = 0; i < R; i++)
		{
			for (int k = 0; k < C; k++)
				map[i][k] += temp[i][k];
		}

		//공기청정기 가동
		//1. 반시계 방향
		for (int i = A - 2; i >= 0; i--) map[i + 1][0] = map[i][0];
		for (int k = 1; k < C; k++) 	map[0][k - 1] = map[0][k];
		for (int i = 1; i <= A; i++)	map[i - 1][C - 1] = map[i][C - 1];
		for (int k = C - 2; k >= 1; k--) map[A][k + 1] = map[A][k];
		map[A][1] = 0;

		//2. 시계 방향
		for (int i = B + 2; i < R; i++)  map[i - 1][0] = map[i][0];
		for (int k = 1; k < C; k++)    map[R - 1][k - 1] = map[R - 1][k];
		for (int i = R - 2; i >= B; i--) map[i + 1][C - 1] = map[i][C - 1];
		for (int k = C - 2; k >= 1; k--) map[B][k + 1] = map[B][k];
		map[B][1] = 0;
	}

	int sum = 0;
	for (int i = 0; i < R; i++)
	{
		for (int k = 0; k < C; k++)
		{
			if (map[i][k] > 0)
				sum += map[i][k];
		}
	}

	printf("%d\n", sum);

	return 0;//Your program should return 0 on normal termination.
}

/*
당시 시험에서는 미세먼지 확산 부분을 queue에 넣어서 풀었었는데, 
이번에는 temp[][] 배열에 각 지점에 더해질 미세먼지 값을 구하고, 원래의 map[][]에 temp[][]를 더해주는 형식으로 풀었다.

이슈사항) 공기청정기 행의 번호 A,B (A < B)
처음에는
if(map[i][k] == -1)
	A = i; 

B = A + 1;
로 해서 틀렸다. 미세먼지가 확산되는 것 까지는 문제가 없었지만, 
나중에 공기청정기가 가동되어 배열 원소의 값을 돌릴 때 이상해서 보니, 이 부분이 문제가 있는 것이었다.
해당 if문은 -1일 때 작동하므로, 총 2번 동작하게 되고, 따라서 A가 아닌 B의 값이 저장되는 것이다. 이에,
//공기청정기 위치 찾기
for (int i = 0; i < R; i++)
{
	if (map[i][0] == -1)
	{
		A = i;
		break; //이 부분 추가
  }
}
B = A + 1;
로 하여, 공기청정기 행의 번호 A,B를 구하였다.
*/
