#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	int N, M;
	int x, y, K;
	scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);

	int map[22][22];
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < M; k++)
		{
			scanf("%d", &map[i][k]);
		}
	}

	int* order = new int[K];
	for (int i = 0; i < K; i++)
	{
		scanf("%d", &order[i]);
	}

	//주사위 굴리기 (order[] => 1:동쪽, 2:서쪽, 3:북쪽, 4:남쪽)
	int row[4] = { 0 }; //row[1]과 col[1]이 같은,, => 윗면
	int col[4] = { 0 }; //row[3]과 col[3]이 같은,, => 바닥면
	int temp;
	for (int i = 0; i < K; i++)
	{
		switch (order[i])
		{
		case 1: //동쪽
			y++;
			if (y >= M)
			{
				y--;
				continue;
			}
			//굴리기
			temp = row[3];
			row[3] = row[2];
			row[2] = row[1];
			row[1] = row[0];
			row[0] = temp;
			col[3] = row[3];
			//바닥 바꾸기
			if (map[x][y] == 0)
			{
				map[x][y] = col[3];
			}
			else
			{
				col[3] = map[x][y];
				row[3] = map[x][y];
				map[x][y] = 0;
			}

			col[1] = row[1];
			printf("%d\n", row[1]);
			break;

		case 2: //서쪽
			y--;
			if (y < 0)
			{
				y++;
				continue;
			}
			//굴리기
			temp = row[0];
			row[0] = row[1];
			row[1] = row[2];
			row[2] = row[3];
			row[3] = temp;
			col[3] = row[3];
			//바닥 바꾸기
			if (map[x][y] == 0)
			{
				map[x][y] = col[3];
			}
			else
			{
				col[3] = map[x][y];
				row[3] = map[x][y];
				map[x][y] = 0;
			}

			col[1] = row[1];
			printf("%d\n", row[1]);
			break;

		case 3: //북쪽
			x--;
			if (x < 0)
			{
				x++;
				continue;
			}
			//굴리기
			temp = col[0];
			col[0] = col[1];
			col[1] = col[2];
			col[2] = col[3];
			col[3] = temp;
			row[3] = col[3];
			//바닥 바꾸기
			if (map[x][y] == 0)
			{
				map[x][y] = col[3];
			}
			else
			{
				col[3] = map[x][y];
				row[3] = map[x][y];
				map[x][y] = 0;
			}

			row[1] = col[1];
			printf("%d\n", row[1]);
			break;

		case 4: //남쪽
			x++;
			if (x >= N)
			{
				x--;
				continue;
			}
			//굴리기
			temp = col[3];
			col[3] = col[2];
			col[2] = col[1];
			col[1] = col[0];
			col[0] = temp;
			row[3] = col[3];
			//바닥 바꾸기
			if (map[x][y] == 0)
			{
				map[x][y] = col[3];
			}
			else
			{
				col[3] = map[x][y];
				row[3] = map[x][y];
				map[x][y] = 0;
			}

			row[1] = col[1];
			printf("%d\n", row[1]);
			break;
		}

	}


	return 0;//Your program should return 0 on normal termination.
}

/*
전개도를 그려서 생각했다.
실제로, 주사위가 동/서/남/북으로 굴러갈 때, 바뀌는 전개도로 값을 이동시켰다.
이슈사항) 전개도는 6칸? => 8칸!
실제로 전개도를 그릴 때 6칸이지만, 행4칸, 열4칸 총 8칸으로 생각하였다.
이때 row[1]과 col[1]을 윗면으로, row[3]과 col[3]을 아랫면으로 (중복)설정하였다.
이렇게 중복으로 설정해놓으면, 동/서로 행에서의 이동, 남/북으로 열에서의 이동 시 바닥면만 신경써서 값을 저장하면 되어 편하다. 
즉, 동으로 이동할 때, 행을 한 칸씩 옆으로 이동시킨 후, row[3]을 col[3]에 덮어씌우면, 이동 후 전개도에 값들로 설정된다.
*/
