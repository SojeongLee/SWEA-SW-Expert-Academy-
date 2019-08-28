#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

string map[1000];
int visited[1000][1000];

int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
	{
		cin >> map[i];
	}

	//시작점과 도착점이 모두 막혀있는 경우 => 도달 불가능 (-1 출력)
	if (map[0][1] == '1' && map[1][0] == '1')
	{
		if (map[N-1][M-2] == '1' && map[N-2][M-1] == '1')
		{
			printf("-1\n");
			return 0;
		}
	}

	//도달 가능한 경우 (최단 거리 구하기 => BFS + visited[x][y] => 0/ 1,2[벽을 부순적이 없는지/있는지 여부])
	int cnt = 0;
	queue<pair<int, int> > q;
	q.push(pair<int, int>(0, 0));
	visited[0][0] = 1;

	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	while (!q.empty())
	{
		cnt++;
		//printf("cnt : %d\n", cnt);
		int size = q.size();
		for (int s = 0; s < size; s++)
		{
			int x = q.front().first;
			int y = q.front().second; //printf("%d, %d\n", x, y);
			q.pop();

			if (x == N - 1 && y == M - 1)
			{
				printf("%d\n", cnt);
				return 0;
			}				

			for (int dir = 0; dir < 4; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];
				if (tx < 0 || ty < 0 || tx >= N || ty >= M)
					continue;
				//아직 방문 안했거나(0) 벽을 부수고 간 경우(2)를 체크(벽을 안 부수고 갈 수도 있으므로,, 1로 업데이트 되게,,)
				if (map[tx][ty] == '0' && visited[tx][ty] != 1) 
				{
					if (visited[tx][ty] == 2 && visited[x][y] == 2) //2에서 2로는 가면 안된다.(무한루프 원인)
						continue;
					//printf("그냥 이동 [%d,%d] => [%d,%d]\n",x,y, tx, ty);
					visited[tx][ty] = visited[x][y];
					q.push(pair<int, int>(tx, ty));
				}
				else if (map[tx][ty] == '1' && visited[tx][ty] == 0)
				{
					if (visited[x][y] != 2) //이제까지 벽을 부순적이 없다면 부수고 간다.
					{
						//printf("벽부수고 이동 [%d,%d] => [%d,%d]\n", x,y,tx, ty);
						visited[tx][ty] = 2;
						q.push(pair<int, int>(tx, ty));
					}
				}
			}
			/*for (int i = 0; i < N; i++)
			{
				for (int k = 0; k < M; k++)
					printf("%d ", visited[i][k]);
				printf("\n");
			}*/
		}
	}

	printf("-1\n");

	return 0;
}

/*
추후에 이와 비슷한 테크닉의 문제들을 풀어보니, 
visited[x][y][벽을부순적이있는지여부] 로 풀면 더 쉽게 풀 수 있을 것이라는 생각이 들었다.
하지만, 이번에는 visited[][] 로 2차원으로 풀었다. 
이유는, 벽을 부순적이 있는지/없는지 즉, 2가지의 경우이므로, visited[][]의 값을 0,1만이 아니라 2를 추가해서, 2면 부순 것으로 간주했다.

우선 크게 두 가지 상황으로 분류했다.
1. 처음부터 도달이 불가능함을 판단할 수 있는 경우 (시작점, 도착점이 모두 막혀있음)
2. 우선은 도달 가능한 경우 => BFS를 이용하여 최단 거리를 구하였다.
  1) 지도가 0인 경우, 그냥 지나갈 수 있다.
  2) 지도가 1인 경우, 벽이므로 그냥 지나갈 수 없다. 이제까지 벽을 부순 적이 없다면 부수고 간다.   
  
이슈사항) 무한루프의 원인
2-1)에서, 지도가 0인 경우지만, 지나가지 않아야 할 조건이 있음을 빠뜨려서, 무한루프에 걸렸었다.
if (map[tx][ty] == '0' && visited[tx][ty] != 1) 
{
  if (visited[tx][ty] == 2 && visited[x][y] == 2) //2에서 2로는 가면 안된다.(무한루프 원인)
    continue;
다음에 이동할 칸 [tx][ty]가 이미 2로 써있고, 현재 칸 [x][y]도 2로 써있다면 이동하면 안 된다. 
왜냐하면 이미 더 빠른 시간에 도착했던 칸이기 때문이다.
이 부분을 생각하기 싫다면, 처음에 말했던 visited 3차원 배열로 푸는 방법도 있다.
*/
