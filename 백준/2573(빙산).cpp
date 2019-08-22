#include <iostream>
#include <queue>

using namespace std;

int map[301][301];

int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d",&N, &M);

	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<M ; k++)
			scanf("%d",&map[i][k]);
	}

	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	int year = 0;
	while(1)
	{
		year++;
		//빙산 녹이기
		int temp[301][301] = {0};
		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<M ; k++)
			{
				int cnt = 0;
				for(int dir=0 ; dir<4 ; dir++)
				{
					int tx = i + dx[dir];
					int ty = k + dy[dir];
					if(tx<0 || ty<0 || tx>=N || ty>=M)
						continue;
					if(map[tx][ty] == 0)
						cnt++;
				}
				temp[i][k] = cnt;
			}
		}
		
		queue<pair<int,int> > q;
		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<M ; k++)
			{
				map[i][k] -= temp[i][k];
				if(map[i][k] < 0)
					map[i][k] = 0;
				if(map[i][k] > 0) //빙산을 큐에 저장한다.
					q.push(pair<int,int>(i,k));
			}
		}

		//BFS를 실시하여 한 덩어리인지 / 아닌지를 판단한다.
		int size = q.size(); //빙산의 개수
		if(size == 0) //빙산이 다 녹음
		{
			printf("0\n");
			return 0;
		}

		queue<pair<int,int> > t;
		int x = q.front().first;
		int y = q.front().second;
		t.push(pair<int,int>(x, y));
		int visited[301][301] = {0};
		visited[x][y] = 1;
		int cnt = 0;
		while(!t.empty())
		{
			cnt++;
			x = t.front().first;
			y = t.front().second;
			t.pop();
			for(int dir=0 ; dir<4 ; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];
				if(tx<0 || ty<0 || tx>=N || ty>=M)
					continue;
				if(visited[tx][ty] == 0 && map[tx][ty] > 0)
				{
					visited[tx][ty] = 1;
					t.push(pair<int,int>(tx,ty));
				}
			}
		}
		
		if(size != cnt) //빙산이 한 덩어리임
		{
			printf("%d\n",year);
			return 0;
		}
	}


	return 0;//Your program should return 0 on normal termination.
}

/*
크게 3단계로 풀었다.
1) 빙산을 녹인다.
2) 빙산의 총 개수를 구한다.
3) BFS를 한 번 수행하여, 한 번에 방문할 수 있는 빙산의 개수를 구한다. 

=> 빙산의 총 개수 == 한 번 BFS 할 때 방문 개수 이면 빙산이 전체 ‘한 덩어리’라는 의미가 된다. 
따라서 != 일 때, 빙산이 한 덩어리가 아니게 되는(즉, 두 덩어리 이상이 된다.)

만일 빙산이 다 녹을 때까지 분리되지 않으면 0을 출력한다.
라는 조건도 있는데, 이는 2) 빙산의 총 개수를 구하고, 이 개수 == 0 인 것으로 판단할 수 있다.
*/
