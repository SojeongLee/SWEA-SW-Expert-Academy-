#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	int R, C;
	scanf("%d %d", &R, &C);

	int map[110][110] = { 0 };
	int visited_dir[110][110][5] = { 0 };
	for (int i = 1; i <= R; i++)
	{
		for (int k = 1; k <= C; k++)
		{
			scanf("%d", &map[i][k]);
		}
	}
	
	int sx, sy, sd;
	int ex, ey, ed;
	scanf("%d %d %d", &sx, &sy, &sd);
	scanf("%d %d %d", &ex, &ey, &ed);
	
	int dx[5] = {0,0,0,1,-1}; //0,1:동,2:서,3:남,4:북
	int dy[5] = {0,1,-1,0,0}; 
	queue<pair<int, pair<int, int> > > q;
	q.push(pair<int, pair<int, int> >(sd, pair<int, int>(sx, sy)));
	visited_dir[sx][sy][sd] = 1;

	int cnt = -1;
	while (!q.empty())
	{
		cnt++; 
		int size = q.size(); 
		//printf("cnt : %d, size : %d\n", cnt, size);
		for (int s = 0; s < size; s++)
		{
			int x = q.front().second.first;
			int y = q.front().second.second;
			int d = q.front().first;
			//printf("%d, %d, dir = %d\n", x, y, d);
			q.pop();

			if (x == ex && y == ey && d == ed)
			{
				printf("%d\n", cnt);
				return 0;
			}

			int tx, ty, td;
			//Go K(K = 1, 2, 3)
			for (int k = 1; k <= 3; k++)
			{
				tx = x + dx[d] * k;
				ty = y + dy[d] * k;
				if (tx<1 || ty<1 || tx>R || ty>C)
					continue;

				if (map[tx][ty] == 1) //벽이면 이동 못함(k=1일 때 벽이면, k=2,3도 어짜피 이동 못하는 것,, 아니면 jump하게 되어 틀린 결과값을 가져옴)
					break;
				
				if (visited_dir[tx][ty][d] == 0) //아직 방문 안한 곳+방향 방문
				{
					visited_dir[tx][ty][d] = 1;
					q.push(pair<int, pair<int, int> >(d, pair<int, int>(tx, ty)));
				}
			}

			//Turn Left
			switch (d)
			{
			case 1: //동
				td = 4;				break;
			case 2: //서
				td = 3; 			break;
			case 3: //남
				td = 1; 			break;
			case 4: //북
				td = 2; 			break;
			}
			if (visited_dir[x][y][td] == 0)
			{
				visited_dir[x][y][td] = 1;
				q.push(pair<int, pair<int, int> >(td, pair<int, int>(x, y)));
			}

			//Turn Right
			switch (d)
			{
			case 1: //동
				td = 3;				break;
			case 2: //서
				td = 4; 			break;
			case 3: //남
				td = 2; 			break;
			case 4: //북
				td = 1; 			break;
			}
			if (visited_dir[x][y][td] == 0)
			{
				visited_dir[x][y][td] = 1;
				q.push(pair<int, pair<int, int> >(td, pair<int, int>(x, y)));
			}
		}
	}

	return 0;//Your program should return 0 on normal termination.
}

/*
우선, 좌표만 큐에 저장하는 BFS와는 달리, 방향을 가지므로, 
queue<pair<int, pair<int, int> > > q;
3개의 값을 저장할 수 있는 큐를 선언하였다.
또한 방문배열도 좌표만 있었다면 visited[110][110]과 같이 선언했겠지만, 
현재는 해당 칸이 있으면, 동으로 이동해서 해당 칸에 이동한 것과, 서로, 남으로, 북으로 이동해서 해당 칸에 이동한 것은 다 다르다. 따라서
int dx[5] = {0,0,0,1,-1}; //0,1:동,2:서,3:남,4:북
int dy[5] = {0,1,-1,0,0}; 

int visited_dir[110][110][5] = { 0 };
방문배열을 3차원 배열로 선언하여, 동/서/남/북 4 방향에서 이동하는 경로를 모두 체크할 수 있도록 하였다.

이슈사항) 벽을 뚫고 갈 수는 없다!
로봇은 3칸까지 전진할 수 있지만, 벽이 있으면 갈 수 없다. 
처음에는 k=1, 2, 3 일 때 벽이면 못 가고, 벽이 아니면 갈 수 있게 해서 틀린 결과가 나왔다.
k=1일 때 안되면, k=2, 3일 때도 안 되어야 하는 게 맞다.
k=1일 때 벽이어서 못 가는데, k=2 일 때는 벽이 아니어서 이동한다면, 점프하게 되는 효과이기 때문이다. 
그리고 이는 로봇의 주어진 기능이 아니다.
*/
