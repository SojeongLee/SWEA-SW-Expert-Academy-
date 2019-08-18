#include <iostream>
#include <queue>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	while (1)
	{
		int H, R, C;
		scanf("%d %d %d", &H, &R, &C);

		if (H == 0 && R == 0 && C == 0)
			break;

		string map[30][30];
		queue < pair<int, pair<int, int> > > q;
		int visited[30][30][30] = { 0 };
		for (int h = 0; h < H; h++)
		{
			for (int i = 0; i < R; i++)
			{
				cin >> map[h][i];
				for (int k = 0; k < C; k++)
				{
					if (map[h][i][k] == 'S')
					{
						visited[h][i][k] = 1;
						q.push(pair<int, pair<int, int> >(h, pair<int, int>(i, k)));
					}
				}
			}
			scanf("%*c");
		}

		//BFS
		int dx[6] = {0,0,1,-1,0,0};
		int dy[6] = {1,-1,0,0,0,0};
		int dh[6] = {0,0,0,0,1,-1};
		int cnt = 0;
		while (!q.empty())
		{
			cnt++;
			int size = q.size();
			for (int s = 0; s < size; s++)
			{
				int x = q.front().second.first;
				int y = q.front().second.second;
				int h = q.front().first;
				q.pop();
				for (int dir = 0; dir < 6; dir++)
				{
					int tx = x + dx[dir];
					int ty = y + dy[dir];
					int th = h + dh[dir];

					if (tx < 0 || ty < 0 || th < 0 || tx >= R || ty >= C || th >= H)
						continue;

					if (map[th][tx][ty] == 'E')
					{
						printf("Escaped in %d minute(s).\n", cnt);
						goto A;
					}
					if (visited[th][tx][ty] == 0 && map[th][tx][ty] == '.')
					{
						visited[th][tx][ty] = 1;
						q.push(pair<int, pair<int, int> >(th, pair<int, int>(tx, ty)));
					}
				}
			}
			
		}
		printf("Trapped!\n");
	A: ;

	}

	return 0;//Your program should return 0 on normal termination.
}

/*
3차원 문제라는 점에서 이전 7569(토마토) 문제와 비슷하다.
전형적인 BFS 문제이며, BFS의 종료 조건은, 상근이의 좌표를 저장하는 큐가 empty가 되면 이다. 
큐가 empty가 되었는데도 탈출하지 못했다면, Trapped!을 출력하면 된다.
*/
