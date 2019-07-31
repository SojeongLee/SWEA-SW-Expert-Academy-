#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
	int M, N;
	scanf("%d %d", &M, &N);

	int map[110][110] = { 0 };
	for (int i = 0; i < M; i++)
	{
		for (int k = 0; k < N; k++)
		{
			map[i][k] = 1; //1로 초기화한다,,
		}
	}

	map[0][0] = 0; //왼쪽 위 칸에서 시작
	int x = 0, y = 0;
	int cnt = 0; //선을 꺾은 횟수(== 방향을 바꾼 횟수)
	int dir = 0; //0:오른쪽 -> 1:아래 -> 2:왼쪽 -> 3:위 -> 0
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};

	while (1)
	{
		int tx = x + dx[dir];
		int ty = y + dy[dir];

		if (map[ty][tx] == 1) //1이면 한칸 이동
		{
			x = tx, y = ty;
			map[y][x] = 0;
			//printf("이동 : %d, %d\n", y, x);
		}
		else //이동할 수 없으면 방향을 바꾼다.
		{
			dir = (dir + 1) % 4;
			//바꾼곳으로 갈 수 없으면 break;
			tx = x + dx[dir];
			ty = y + dy[dir];
			if (map[ty][tx] == 0)
			{
				//printf("멈춤 : %d, %d\n", y, x);
				break;
			}
			//printf("꺾음 : %d, %d\n", y, x);
			cnt++;
		}

	}

	printf("%d\n", cnt);


	return 0;//Your program should return 0 on normal termination.
}

/*
뭔가 수학적으로 할 수 있을 것 같기도 하지만, 시뮬레이션 카테고리인만큼 시뮬레이션으로 풀었다.
int dir = 0; //0:오른쪽 -> 1:아래 -> 2:왼쪽 -> 3:위 -> 0
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
시계방향으로 도는 것이므로, dx[4]와 dy[4]를 선언하여, x,y좌표에 각각을 더해갈 수 있도록 하였다. 
이때 dir변수로 해당 방향으로 쭉 이동하다가, 벽이거나 이미 방문해서 이동할 수 없는 경우일 경우, 
방향을 전환하도록 하였다.
*/
