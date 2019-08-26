#include <iostream>
#include <queue>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{
	int N;
	scanf("%d", &N);

	int map[21][21];
	int sx, sy;
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < N; k++)
		{
			scanf("%d", &map[i][k]);
			if (map[i][k] == 9) //아기상어
			{
				sx = i;
				sy = k;
				map[i][k] = 0;
			}
		}
	}

	int dx[4] = {-1,0,0,1}; //위, 왼쪽, 오른쪽, 아래
	int dy[4] = {0,-1,1,0};
	int SIZE = 2; //현재 아기상어 크기
	int cnt = 0; //현재 잡아먹은 물고기 개수
	int sum = 0; //정답

A:
	queue<pair<int, int> > q;
	q.push(pair<int, int>(sx, sy));
	int visited[21][21] = { 0 };
	visited[sx][sy] = 1;
	int sec = 0; //초

	vector<pair<int, int> > v; //priority_queue 구현,,
	int flag = 0;

	while (!q.empty())
	{
		sec++;
		int size = q.size();
		for (int s = 0; s < size; s++)
		{
			int x = q.front().first;
			int y = q.front().second;
			//printf("sec : %d, x,y : %d, %d\n",sec, x, y);
			q.pop();
			for (int dir = 0; dir < 4; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];
				if (tx < 0 || ty < 0 || tx >= N || ty >= N)
					continue;
				if (map[tx][ty] > SIZE) //자신의 크기보다 더 큰 칸은 지나갈 수 없음
					continue;
				if (visited[tx][ty] == 0) //크기가 같거나 작은데 방문 안한 곳
				{
					//printf(" %d, %d\n", tx, ty);
					visited[tx][ty] = 1;
					q.push(pair<int, int>(tx, ty));

					if (map[tx][ty] < SIZE && map[tx][ty] != 0) //잡아먹음 (0은 아님!)
					{
						v.push_back(pair<int, int>(tx, ty));
						flag = 1;
					}
				}
			}
		}
		if (flag) //가장 우선순위가 높은 물고기를 잡아먹는다
		{
			int ud = v[0].first;
			int lr = v[0].second;
			int idx = 0;
			for (int p = 1; p < v.size(); p++)
			{
				//printf("	%d, %d\n",v[p].first, v[p].second);
				if (ud > v[p].first)
				{
					ud = v[p].first;
					idx = p;
				}
				else if (ud == v[p].first)
				{
					if (lr > v[p].second)
					{
						lr = v[p].second;
						idx = p;
					}
				}
			}

			int tx = v[idx].first;
			int ty = v[idx].second;

			map[tx][ty] = 0;
			cnt++;
			sum += sec;
			//printf("sec : %d, sum : %d,, 잡아먹는다,, %d, %d\n", sec, sum, tx, ty);

			sec = 0;
			sx = tx;
			sy = ty;

			if (cnt == SIZE)
			{
				SIZE++;
				cnt = 0;
			}

			goto A;
		}
	}

	printf("%d\n", sum);


	return 0;//Your program should return 0 on normal termination.
}

/*
가장 가까운 곳에 있는 물고기를 잡아먹어 나가는 형식이므로, BFS 문제이다.
BFS로 해당 칸들을 조사해 나갈 때 크게 3가지의 조건을 두어야 한다.

1) 아기상어 자신보다 크기가 큰 물고기가 있는 경우 => 지나가지 못한다.
2) 자신과 같은 크기의 물고기가 있는 경우 => 지나갈 수는 있다. (먹진 못함)
3) 자신보다 작은 크기의 물고기가 있는 경우 => 먹을 수 있다.

따라서 1)의 경우 continue; 를 사용하여 건너뛰게 하였으며, 2)3)일 경우 지나갈 수 있으므로, 큐에 push 하였다. 

이슈사항) 예제4번이 56이 나오는 이유 => 우선순위 큐를 사용해야 한다! 
거리가 가까운 물고기가 많다면, 가장 위에 있는 물고기, 그러한 물고기가 여러마리라면, 가장 왼쪽에 있는 물고기를 먹는다.
라는 문제 조건이 있다.
따라서, 자신보다 크기가 작은 물고기를 BFS 과정에서 만났다고, 바로 그 물고기를 먹으면 틀린 값이 나오게 된다.
왜냐하면 같은 거리에 있고, 자신보다 크기가 작은 물고기가 여러 마리 일 수도 있기 때문이다.
따라서 우선순위 큐를 사용하여야 한다. 

하지만 이 문제와 같은 경우에는, 같은 거리에 있고 잡아먹을 수 있는 물고기의 개수가 그리 많지 않으므로,
vector를 이용하여, 직접 우선순위가 가장 높은 index를 구했다. 
큐가 아닌 벡터를 이용한 이유는, 1) 몇 마리일 지 정확히 모르므로 배열은 사용하지 않았다. 2) 인덱스([0], [1],,,)로 접근하고 싶어서 이다.
가장 위쪽에 있는 물고기(행의 값이 최소)를 구하려 했고, 만약 이 과정에서 행의 값이 같다면, 
가장 왼쪽에 있는 물고기(열의 값이 최소)인 물고기를 선택했다. 
*/
