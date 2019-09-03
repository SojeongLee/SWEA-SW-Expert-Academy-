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
				wall_cnt++;
			else if (map[i][k] == 2)
				virus.push_back(pair<int, int>(i, k));
		}
	}

	int virus_size = virus.size();
	vector<int> ind;
	for (int i = 1; i <= K; i++)
		ind.push_back(1);
	for (int i = 1; i <= virus_size - K; i++)
		ind.push_back(2);

	int VIRUS_CNT = N * N - wall_cnt - virus_size; //빈 칸의 개수(앞으로 바이러스가 퍼져야하는 부분)
	int MIN = 2500;
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	int flag = 0;
	do
	{
		int virus_cnt = 0;
		queue < pair<int, int> > q;
		int visited[51][51] = { 0 };
		for (int i = 0; i < virus_size; i++)
		{
			if (ind[i] == 1)
			{
				int x = virus[i].first;
				int y = virus[i].second;
				q.push(pair<int, int>(x, y));
				visited[x][y] = 1;
			}
		}
		//BFS
		int cnt = 0;
		while (!q.empty())
		{
			if (virus_cnt == VIRUS_CNT)
			{
				flag = 1;
				if (MIN > cnt)
					MIN = cnt;
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
					if (map[tx][ty] == 1)
						continue;

					if (visited[tx][ty] == 0)
					{
						visited[tx][ty] = 1;
						q.push(pair<int, int>(tx, ty));
						if (map[tx][ty] == 0)
							virus_cnt++;
					}
				}
			}

		}

	} while (next_permutation(ind.begin(), ind.end()));


	if (flag)	printf("%d\n", MIN);
	else        printf("-1\n");


	return 0;
}

/*
연구소2와 거의 유사한 문제이다.
마찬가지로, 바이러스가 퍼져야 하는 칸의 수를 미리 구해놓았다.
바이러스 중 활성화 시킬 것을 넥스트퍼뮤테이션 함수를 사용하여 조합을 구했다.

이슈사항) 연구소2와 사실 같은 문제?
연구소2는 바이러스를 놓을 수 있는 곳 중 M개를 고르는 것이고,
연구소3은 바이러스들 중 M개를 활성화 시키는 것이다.
문제에, ‘활성 바이러스가 비활성 바이러스가 있는 칸으로 가면 비활성 바이러스가 활성으로 변한다.’라는 말이 있지만, 사실상 아무 의미가 없는 말이다.
어짜피 비활성 바이러스는 빈칸이나 다름없기 때문이다. 따라서 사실상 둘은 같은 문제이다.
*/
