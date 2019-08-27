#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d", &N, &M);

	int map[8][8];
	vector<pair<int, int> > e; //빈칸 좌표 저장
	vector<pair<int, int> > v; //바이러스 좌표 저장
	//입력
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < M; k++)
		{
			scanf("%d", &map[i][k]);
			if (map[i][k] == 0)//빈칸
				e.push_back(pair<int, int>(i, k));

			else if (map[i][k] ==2) //바이러스
				v.push_back(pair<int, int>(i, k));
		}
	}

	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	int wall_cnt = N * M - e.size() - v.size() + 3;//3개는 추후에 설치할 벽
	int VIRUS_CNT = N * M;

	vector<int> ind;
	for (int i = 1; i <= 3; i++)
		ind.push_back(1);
	for (int i = 1; i <= e.size() - 3; i++)
		ind.push_back(2);

	do
	{
		int temp[8][8];
		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < M; k++)
				temp[i][k] = map[i][k];
		}
		//벽 세우기
		for (int i = 0; i < e.size(); i++)
		{
			if (ind[i] == 1)
				temp[e[i].first][e[i].second] = 1;
		}
		//바이러스 퍼뜨리기(BFS)
		int visited[8][8] = { 0 };
		int virus_cnt = 0;
		for (int i = 0; i < v.size(); i++)
		{
			int x = v[i].first;
			int y = v[i].second;
			if (visited[x][y] == 1)
				continue;

			virus_cnt++;
			visited[x][y] = 1;
			queue<pair<int, int> > q;
			q.push(pair<int, int>(x, y));
			while (!q.empty())
			{
				x = q.front().first;
				y = q.front().second;
				q.pop();
				for (int dir = 0; dir < 4; dir++)
				{
					int tx = x + dx[dir];
					int ty = y + dy[dir];
					if (tx < 0 || ty < 0 || tx >= N || ty >= M)
						continue;
					if (temp[tx][ty] == 0 && visited[tx][ty] == 0)
					{
						virus_cnt++;
						visited[tx][ty] = 1;
						q.push(pair<int, int>(tx, ty));
					}
				}
			}
		}
		if (VIRUS_CNT > virus_cnt)
			VIRUS_CNT = virus_cnt;

	} while (next_permutation(ind.begin(), ind.end()));

	int CNT = N * M - wall_cnt - VIRUS_CNT;
	printf("%d\n", CNT);

	return 0;
}

/*
지도의 크기와 바이러스의 개수를 고려하여, 조합으로 문제를 해결하였다.
안전영역이 최대가 된다는 것은, 바이러스가 최소로 퍼지는 것을 의미하므로, 바이러스의 최솟값을 구하고자 하였다.
next_permutation함수와 vector<int> ind 를 합쳐, 빈칸에 벽 3개를 설치한 후,
BFS로 바이러스를 퍼뜨렸다. 
이 후, 퍼뜨린 바이러스의 수가 최솟값보다 작다면 이를 업데이트 해나가는 방식으로, 바이러스의 최솟값을 구하였다.
*/
