#include <iostream>
#include <queue>
#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;

int H, W;
char map[110][110];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int dist[3][110][110];

void bfs(int idx, int start_x, int start_y)
{
	queue < pair<int, int> > q;
	q.push(pair<int, int>(start_x, start_y));
	dist[idx][start_x][start_y] = 0;
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		//printf("%d,%d\n", x, y);

		int d = dist[idx][x][y];
		for (int dir = 0; dir < 4; dir++)
		{
			int tx = x + dx[dir];
			int ty = y + dy[dir];
			if (tx < 0 || ty < 0 || tx >= H + 2 || ty >= W + 2)
				continue;
			int td = dist[idx][tx][ty];
			if (map[tx][ty] == '.' && td > d)
			{
				dist[idx][tx][ty] = d;
				q.push(pair<int, int>(tx, ty));
			}
			if (map[tx][ty] == '#' && td > d + 1)
			{
				dist[idx][tx][ty] = d + 1;
				q.push(pair<int, int>(tx, ty));
			}
		}
	}
	/*for (int i = 0; i < H + 2; i++)
	{
		for (int k = 0; k < W + 2; k++)
			printf("%8d", dist[idx][i][k]);
		printf("\n");
	}*/
}

int main(int argc, char** argv)
{
	int T;
	scanf("%d", &T);
	for (int test_case = 0; test_case < T; test_case++)
	{
		scanf("%d %d", &H, &W);
		int cnt = 0;
		int px[2], py[2];

		memset(map, '.', sizeof(char) * 110 * 110);
		string temp[110];
		for (int i = 0; i < H; i++)
		{
			cin >> temp[i];
		}

		for (int i = 0; i < H; i++)
		{
			for (int k = 0; k < W; k++)
			{
				map[i + 1][k + 1] = temp[i][k];
				if (map[i + 1][k + 1] == '$')
				{
					map[i + 1][k + 1] = '.';
					px[cnt] = i + 1;
					py[cnt] = k + 1;
					cnt++;
				}
			}
		}

		//상근이, 죄수1, 죄수2 => 3명 각각 BFS로 DIST[][] 구하기
		for (int idx = 0; idx < 3; idx++)
		{
			for (int i = 0; i < 110; i++)
			{
				for (int k = 0; k < 110; k++)
					dist[idx][i][k] = 10000;
			}
		}

		bfs(0, 0, 0);
		bfs(1, px[0], py[0]);
		bfs(2, px[1], py[1]);

		int dist_sum[110][110] = { 0 };
		int min = 10000;
		for (int i = 0; i < H + 2; i++)
		{
			for (int k = 0; k < W + 2; k++)
			{
				for (int idx = 0; idx < 3; idx++)
				{
					dist_sum[i][k] += dist[idx][i][k];
				}
				if (map[i][k] == '#')
					dist_sum[i][k] -= 2;
				if (min > dist_sum[i][k])
					min = dist_sum[i][k];
			}
		}

		printf("%d\n", min);
	}

	return 0;//Your program should return 0 on normal termination.
}

/*
일단 정말 온전히 자신이 생각을 해내서 풀 수는 없는 문제라고 생각한다..
https://stack07142.tistory.com/145에 풀이를 보고,, 풀었다.
일단 아이디어만 이해한다면, 구현할 때의 이슈사항은 크게 없는 것 같다.

이슈사항) 우선순위 큐를 써야 할까?
우선 처음에는 우선순위 큐를 써야만 할 것이라고 생각했지만,, 쓰지 않고 푼 사람이 있어 아이디어를 구했다. 
BFS로 인접한 4방향으로 퍼져나갈 때, 원래라면 방문여부를 체크하고, 방문을 안 했으면 그 지점을 방문하고 큐에 넣는 형식이었다.
하지만 이 문제는, 방문 여부가 중요한 것이 아니라, 
그 지점에 얼만큼의 열쇠를 ‘최소’로 사용하여 갈 수 있는지가 중요한 것이므로, BFS로 퍼져나갈 때, 
int d = dist[idx][x][y];

int td = dist[idx][tx][ty];

if (map[tx][ty] == '.' && td > d)
{
	dist[idx][tx][ty] = d;
	q.push(pair<int, int>(tx, ty));
}
if (map[tx][ty] == '#' && td > d + 1)
{
	dist[idx][tx][ty] = d + 1;
	q.push(pair<int, int>(tx, ty));
}
d와 td변수를 사용하여, 더 적은 열쇠를 사용해서 해당 지점에 이동할 경우에만, dist[][]배열을 업데이트 해주고, 큐에 push 하도록 하였다. 
이 때 열쇠가 있는 지점은 현재+1보다 큰지/작은지를 비교하면 된다.
*/
