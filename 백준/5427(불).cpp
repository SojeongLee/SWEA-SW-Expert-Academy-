#include <iostream>
#include <queue>
#include <string>
#include <string.h>

using namespace std;

int visited_fire[1000][1000];
int visited_sang[1000][1000];

int main(int argc, char** argv)
{
	int T;
	scanf("%d", &T);

	for (int test_case = 0; test_case < T; test_case++)
	{
		int W, H;
		scanf("%d %d", &W, &H);

		queue<pair<int, int> > fire;
		queue<pair<int, int> > sang;
		memset(visited_fire, 0, sizeof(int) * 1000 * 1000);
		memset(visited_sang, 0, sizeof(int) * 1000 * 1000);
		string* map = new string[H];
		for (int i = 0; i < H; i++)
		{
			cin >> map[i];
			for (int k = 0; k < W; k++)
			{
				if (map[i][k] == '*') //불이면 큐에 저장
				{
					fire.push(pair<int, int>(i, k));
					visited_fire[i][k] = 1;
				}
				else if (map[i][k] == '@')
				{
					map[i][k] = '.';
					sang.push(pair<int, int>(i, k));
					visited_sang[i][k] = 1;
				}
			}
		}

		int dx[4] = { 0,0,1,-1 };
		int dy[4] = { 1,-1,0,0 };
		int cnt = 0;
		while(!sang.empty()) //!fire.empty()가 아니라,,
		{
			//불이 먼저 번진다.
			int size = fire.size();
			for (int i = 0; i < size; i++)
			{
				int x = fire.front().first;
				int y = fire.front().second;
				fire.pop();
				for (int dir = 0; dir < 4; dir++)
				{
					int tx = x + dx[dir];
					int ty = y + dy[dir];

					if (tx < 0 || ty < 0 || tx >= H || ty >= W)
						continue;

					if (visited_fire[tx][ty] == 0 && map[tx][ty] == '.') //빈칸이면 불이 옮겨갈 수 있다
					{
						visited_fire[tx][ty] = 1;
						map[tx][ty] = '*';
						fire.push(pair<int, int>(tx, ty));
					}
				}
			}

			//상근이가 이동한다.
			size = sang.size();
			cnt++;
			for (int i = 0; i < size; i++)
			{
				int x = sang.front().first;
				int y = sang.front().second;
				sang.pop();
				for (int dir = 0; dir < 4; dir++)
				{
					int tx = x + dx[dir];
					int ty = y + dy[dir];

					if (tx < 0 || ty < 0 || tx >= H || ty >= W) //상근이가 탈출하면 끝난다. (상근이의 위치가 map을 벗어남)
					{
						printf("%d\n", cnt);
						goto A;
					}

					if (visited_sang[tx][ty] == 0 && map[tx][ty] == '.') //빈칸이면 상근이가 이동할 수 있다
					{
						visited_sang[tx][ty] = 1;
						sang.push(pair<int, int>(tx, ty));
					}
				}
			}
		}

		printf("IMPOSSIBLE\n"); //불이 다 번질 때까지 탈출하지 못함 || 불에 둘러싸여 더이상 이동하지 못함

	A: printf("");
	}

	return 0;//Your program should return 0 on normal termination.
}

/*
이전에 풀었던 3055(탈출)랑 거의 유사한 문제이다.
탈출 문제는 목적지가 하나로 정해져 있다면, 이번 불 문제는 목적지가 map을 벗어나는 것이 다른 점이다.
크게 3단계로 생각했다.
1) 불이 번진다. (BFS)
2) 상근이가 이동한다. (BFS)
3) 상근이가 탈출했으면 끝난다.

이슈사항1) test_case가 여러 개!
방문배열을 초기화 해줘야 한다. 방문 배열이 예를 들어, int visited[100][100] 라고 한다면, 
초기화는 #include <string.h>에 있는 memset(visited, 0, sizeof(int)*100*100); 과 같이 할 수 있다.

이슈사항2) while문의 종료조건!
위의 3단계를 계속 반복하게 되는데, 상근이가 map을 결국 벗어나지 못한다면, IMPOSSIBLE을 출력해야 한다. 
따라서, while문의 종료조건은, 상근이의 좌표를 저장하고 있는 큐가 empty가 되면 종료하는 것이다. 
처음에는 불의 좌표를 저장하는 큐가 empty가 되면 종료하게 조건을 주었더니, 
불이 애초에 없거나 더 이상 번지지 않는 경우, 상근이가 탈출할 가능성이 있음에도 종료해버려서 오답이 되었다. 
*/
