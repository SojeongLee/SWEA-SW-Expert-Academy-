#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{	
	int N, K;
	scanf("%d %d", &N, &K);
	
	int map[51][51];
	int wall_cnt = 0;
	vector<pair<int, int> > virus;
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < N; k++)
		{
			scanf("%d", &map[i][k]);
			if (map[i][k] == 1)
			{
				wall_cnt++;
			}
			else if (map[i][k] == 2)
			{
				virus.push_back(pair<int, int>(i, k));
				map[i][k] = 0;
			}
		}
	}
	
	int VIRUS_CNT = N * N - wall_cnt; //바이러스가 다 퍼지면 이 숫자만큼 되야 함
	int virus_size = virus.size();
	//printf("wall_cnt : %d, VIRUS_CNT : %d, virus_size : %d\n", wall_cnt, VIRUS_CNT, virus_size);

	vector<int> ind;
	for (int i = 1; i <= K; i++)
		ind.push_back(1);
	for (int i = 1; i <= virus_size - K; i++)
		ind.push_back(2);

	int MIN = 2500;
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	int flag = 0;
	do
	{
		queue<pair<int, int> > q;
		int visited[51][51] = { 0 };
		int virus_cnt = 0;
		for (int i = 0; i < virus_size; i++)
		{
			if (ind[i] == 1)
			{
				int x = virus[i].first;
				int y = virus[i].second;
				//printf("[%d, %d] ", x, y);
				virus_cnt++;
				visited[x][y] = 1;
				q.push(pair<int, int>(x, y));
			}
		}//printf("\n");
		//BFS
		int cnt = 0;
		while (!q.empty())
		{
			if (virus_cnt == VIRUS_CNT)
			{
				//printf("바이러스 퍼뜨림 : %d번\n", cnt);
				if (MIN > cnt)
					MIN = cnt;
				flag = 1;
				break;
			}

			cnt++;
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

					if (map[tx][ty] == 0 && visited[tx][ty] == 0)
					{
						virus_cnt++;
						visited[tx][ty] = 1;
						q.push(pair<int, int>(tx, ty));
					}
				}
			}
		}
		
	} while (next_permutation(ind.begin(), ind.end()));
	

	if (flag)	printf("%d\n", MIN);
	else		printf("-1\n");


	return 0;
}

/*
연구소1과 거의 유사한 문제이다.
우선 큰 로직을, 바이러스가 퍼져야 하는 칸의 수를 미리 구해놓고,
바이러스를 퍼뜨리면서 카운트를 ++하여, 구해놓은 수와 같으면 종료하게 했다.

크게 두 가지 알고리즘을 사용하였다.
1) 넥스트퍼뮤테이션 : 바이러스가 있는 곳의 좌표를 벡터에 넣어놓고, 주어진 M개를 고르는 조합을 사용하였다.
2) BFS : 바이러스를 상하좌우로 퍼뜨리고, 최단 거리(시간)을 구하는 문제이므로, BFS를 사용하였다. 
*/
