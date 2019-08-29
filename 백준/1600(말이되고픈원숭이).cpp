#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool map[200][200];
bool visited[200][200][31];

int main(int argc, char** argv)
{ 
	int K;
	scanf("%d", &K);

	int W, H; //가로, 세로
	scanf("%d %d", &W, &H);

	for (int i = 0; i < H; i++)
	{
		for (int k = 0; k < W; k++)
			scanf("%d", &map[i][k]);
	}

	//원숭이의 원래 움직임
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	//말의 움직임
	int hx[8] = {-2,-1,1,2,-2,-1,1,2};
	int hy[8] = {1,2,2,1,-1,-2,-2,-1};

	int cnt = 0;
	queue<pair<pair<int,int>,int> > q;
	q.push(pair<pair<int,int>,int>(pair<int,int>(0,0),0));
	visited[0][0][0] = 1;

	while(!q.empty())
	{
		//printf("cnt : %d\n",cnt);

		int size = q.size();
		for(int s=0 ; s<size ; s++)
		{
			int x = q.front().first.first;
			int y = q.front().first.second; 
			int c = q.front().second; //printf("%d, %d (%d번 사용)\n",x,y,c);
			q.pop();

			if(x == H-1 && y == W-1)
			{
				printf("%d\n",cnt);
				return 0;
			}

			//원숭이 움직임으로 이동
			for(int dir=0 ; dir<4 ; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];
				if(tx<0 || ty<0 || tx>=H || ty>=W)
					continue;
				if(map[tx][ty] == 1)
					continue;

				if(visited[tx][ty][c] == 0)
				{
					visited[tx][ty][c] = 1; //printf("	원숭이 : %d, %d\n",tx,ty);
					q.push(pair<pair<int,int>,int>(pair<int,int>(tx,ty),c));
				}
			}

			//말 움직임으로 이동
			if(c >= K) //움직이는 횟수 제한이 끝남
				continue;

			for(int dir=0 ; dir<8 ; dir++)
			{
				int tx = x + hx[dir];
				int ty = y + hy[dir];
				if(tx<0 || ty<0 || tx>=H || ty>=W)
					continue;
				if(map[tx][ty] == 1)
					continue;

				if(visited[tx][ty][c+1] == 0)
				{
					visited[tx][ty][c+1] = 1; //printf("	말 : %d, %d\n",tx,ty);
					q.push(pair<pair<int,int>,int>(pair<int,int>(tx,ty),c+1));
				}
			}
		}
		cnt++;
	}

	printf("-1\n");

	return 0;
}

/*
우선 2206(벽부수고이동하기).cpp 와 비슷하게 접근해야겠다는 생각이 들었다.
여러 시행착오가 있었지만,, 결론은 visited[x][y][말의 움직임으로 이동한 횟수] 즉, 3차원 visited 배열을 사용하는 것이었다.
visited 를 3차원으로 체크하겠다는 것은, queue 또한 3차원이어야 완전탐색을 할 수 있는 것임이 포인트이다. 
코드 상에서 말의 움직임 관련 부분만 떼어서 보면,
bool visited[200][200][31];

queue<pair<pair<int,int>,int> > q;

int c = q.front().second;

//말 움직임으로 이동
if(c >= K) //움직이는 횟수 제한이 끝남
	continue;

if(visited[tx][ty][c+1] == 0)
{
	visited[tx][ty][c+1] = 1; //printf("	말 : %d, %d\n",tx,ty);
	q.push(pair<pair<int,int>,int>(pair<int,int>(tx,ty),c+1));
}
말로 움직일 수 있는 횟수가 남아있다면, + 아직 그 횟수로 해당 칸은 방문하지 않았다면, 
방문처리하고 큐에 넣어주어, 완전탐색이 이루어질 수 있도록 하였다.

이슈사항) 메모리 초과가 발생하는 이유
큐를 사용할 때, 메모리 초과가 발생하는 이유는, 큐에 너무 많은 원소들이 push될 때이다. 
이 문제에서 visited 배열을 2차원으로 사용하여, 큐에 2차원 원소를 저장할 때, 중복되는 원소들이 push되어, 메모리 초과가 발생하였다.
이러한 문제는 visited배열 자체를 3차원으로 두어, 큐에 3차원 원소를 저장하여, 중복되는 원소가 push될 수 없도록 할 수 있다.
*/
