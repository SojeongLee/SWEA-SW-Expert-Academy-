#include <iostream>
#include <queue>

using namespace std;


int main(int argc, char** argv)
{
	int T;
	scanf("%d",&T);
	for(int test_case = 0 ; test_case < T ; test_case++)
	{
		int M, N, K; //가로, 세로, 개수
		scanf("%d %d %d",&M,&N,&K);

		int map[50][50] = {0}; //배추밭 (1:배추가 심어져있음)
		int X, Y;
		queue<pair<int,int> > baechu;
		for(int i=0 ; i<K ; i++)
		{
			scanf("%d %d",&X,&Y);
			map[Y][X] = 1;
			baechu.push(pair<int,int>(Y,X));
		}

		//BFS 시작
		int visited[50][50] = {0};
		int dx[4] = {0,0,1,-1};
		int dy[4] = {1,-1,0,0};
		int cnt = 0;
		while(!baechu.empty())
		{
			int y= baechu.front().first;
			int x = baechu.front().second;

			if(visited[y][x]) //이미 방문 했으면 넘어간다.
			{
				baechu.pop();
				continue;
			}

			cnt++;
			queue<pair<int,int> > temp;
			visited[y][x] = 1;
			temp.push(pair<int,int>(y,x));
			while(!temp.empty())
			{
				y = temp.front().first;
				x = temp.front().second;
				temp.pop();

				for(int dir=0 ; dir<4 ; dir++)
				{
					int ty = y + dy[dir];
					int tx = x + dx[dir];

					if(ty<0 || ty>=N || tx<0 || tx>=M)
						continue;

					if(map[ty][tx] == 1 && visited[ty][tx] == 0)
					{
						visited[ty][tx] = 1;
						temp.push(pair<int,int>(ty,tx));
					}
				}
			}
		}

		printf("%d\n",cnt);
	}


	return 0;//Your program should return 0 on normal termination.
}

/*
영역의 개수를 구하는 전형적인 BFS 문제이다.
우선 map정보를 입력 받을 때, 배추가 심어져 있는 곳의 좌표를 큐에 저장하였다. 
그리고 이 좌표들을 하나씩 빼내어, 배추 영역의 개수를 구하였다. 
*/
