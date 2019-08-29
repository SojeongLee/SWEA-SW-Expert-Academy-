#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int map[100][100];
int visited[100][100];

int main(int argc, char** argv)
{	
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < N; k++)
		{
			scanf("%d", &map[i][k]);
		}
	}

	//섬 구하기(BFS)
	int island_cnt = 0; //섬 개수
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < N; k++)
		{
			if (map[i][k] == 1 && visited[i][k] == 0)
			{
				island_cnt++; //printf("%d\n", island_cnt);

				queue<pair<int, int> > q;
				q.push(pair<int, int>(i, k));
				map[i][k] = island_cnt;
				visited[i][k] = 1;
				while (!q.empty())
				{
					int x = q.front().first;
					int y = q.front().second; //printf("%d, %d\n", x, y);
					q.pop();
					for (int dir = 0; dir < 4; dir++)
					{
						int tx = x + dx[dir];
						int ty = y + dy[dir];
						if (tx < 0 || ty < 0 || tx >= N || ty >= N)
							continue;

						if (map[tx][ty] == 1 && visited[tx][ty] == 0)
						{
							map[tx][ty] = island_cnt; //printf("	%d, %d\n", tx, ty);
							visited[tx][ty] = 1;
							q.push(pair<int, int>(tx, ty));
						}
					}
				}
			}
		}
	}

	//각 섬에서 BFS로 최단거리 구하기
	int MIN_DIST = N * N;
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < N; k++)
		{
			if (map[i][k] != 0) //섬이면
			{
				int dist = 0;
				int island_num = map[i][k]; //해당 육지의 섬 번호

				for (int a = 0; a < N; a++)
				{
					for (int b = 0; b < N; b++)
						visited[a][b] = 0;
				}

				queue<pair<int, int> > q;
				q.push(pair<int, int>(i, k));
				visited[i][k] = 1;
				while (!q.empty())
				{
					int size = q.size();
					for (int s = 0; s < size; s++)
					{
						int x = q.front().first;
						int y = q.front().second;
						q.pop();
						for (int dir = 0; dir < 4; dir++)
						{
							int tx = x + dx[dir];
							int ty = y + dy[dir];
							if (tx < 0 || ty < 0 || tx >= N || ty >= N)
								continue;
							if (map[tx][ty] == island_num) //같은 섬의 육지로는 이동 안함
								continue;
							else if (map[tx][ty] == 0 && visited[tx][ty] == 0) //바다면
							{
								visited[tx][ty] = 1;
								q.push(pair<int, int>(tx, ty));
							}
							else if (map[tx][ty] > 0) //다른 섬에 도달
							{
								if (MIN_DIST > dist)
									MIN_DIST = dist;
								goto A;
							}
						}
					}
					dist++;
				}
			A:;
			}
		}
	}

	printf("%d\n", MIN_DIST);

	return 0;
}

/*
1. 우선 BFS로 최단거리를 찾기 전에 전처리를 해야 한다.
현재는 바다면 0, 육지면 1로 되어있지만, 섬을 구분할 필요가 있으므로, 
섬을 덩어리로 분류하여, 같은 섬이면 같은 번호를 가지게 전처리하였다.
즉 1번섬에 속하는 육지는 1로, 2번섬에 속하는 육지는 2로,,, map 배열을 업데이트 하였다.

2. 그 다음으로 각 섬(육지)에서 BFS로 최단거리를 구한다. 
이 때, 같은 섬의 육지로는 이동하지 않는데, 즉, 같은 번호를 가진 육지이면 이동하지 않으면 된다.
이중포문으로 map배열을 한번 훑으면서 BFS를 적용해, 최솟값을 찾을 수 있다.
*/
