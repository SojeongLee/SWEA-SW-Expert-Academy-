#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	int R, C;
	scanf("%d %d", &R, &C);

	string *map = new string[R];
	for (int i = 0; i < R; i++)
	{
		cin >> map[i];
	}

	//각 영역에서 양(o)과 늑대(v)의 수를 센 다음,, 양이 이기던지, 늑대가 잡아먹던지 한다.
	int visited[255][255] = { 0 };
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	int sheep_cnt = 0;
	int wolf_cnt = 0;
	for (int i = 0; i < R; i++)
	{
		for (int k = 0; k < C; k++)
		{
			if (map[i][k] != '#' && visited[i][k] == 0) //벽이 아니면 영역으로 센다.
			{
				queue<pair<int, int> > q;
				q.push(pair<int, int>(i, k));
				visited[i][k] = 1;

				int sheep = 0;
				int wolf = 0;
				while (!q.empty())
				{
					int size = q.size();
					for (int s = 0; s < size; s++)
					{
						int x = q.front().first;
						int y = q.front().second;
						q.pop();

						if (map[x][y] == 'o') sheep++;
						else if (map[x][y] == 'v') wolf++;

						for (int dir = 0; dir < 4; dir++)
						{
							int tx = x + dx[dir];
							int ty = y + dy[dir];
							if (tx < 0 || ty < 0 || tx >= R || ty >= C)
								continue;

							if (visited[tx][ty] == 0 && map[tx][ty] != '#')
							{
								visited[tx][ty] = 1;
								q.push(pair<int, int>(tx, ty));
							}
						}
					}
				}
				//printf("sheep : %d, wolf : %d\n", sheep, wolf);
				if (sheep > wolf) //양이 이긴다.
				{
					sheep_cnt += sheep;
				}
				else //늑대가 모든 양을 잡아먹는다.
				{
					wolf_cnt += wolf;
				}
			}
		}
	}

	printf("%d %d\n", sheep_cnt, wolf_cnt);

	return 0;//Your program should return 0 on normal termination.
}

/*
영역을 분리해야 하므로 BFS가 사용된다.
각 영역에서 양의 수와, 늑대의 수를 각각 세고, 이를 비교한다.
양이 이기면, 총 양의 수에 더해주고, 늑대가 이기면, 총 늑대 수에 더해줘서, 누적 수를 구한다.
*/
