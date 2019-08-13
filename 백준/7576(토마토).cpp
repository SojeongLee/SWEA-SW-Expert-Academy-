#include <iostream>
#include <queue>

using namespace std;

int map[1001][1001] = {0};
int visited[1001][1001] = {0};

int main(int argc, char** argv)
{
	int M,N;
	scanf("%d %d",&M,&N);

	queue<pair<int,int> > tomato; //익은 토마토
	int flag = 0; //익지 않은 토마토가 있으면 1로

	//입력부분
	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<M ; k++)
		{
			scanf("%d",&map[i][k]);
			if(map[i][k] == 1)
			{
				tomato.push(pair<int,int>(i,k));
				visited[i][k] = 1;
			}
			else if(map[i][k] == 0)
			{
				flag = 1;
			}
		}
	}

	if(flag == 0) //익지 않은 토마토가 없음 => 0 출력
	{
		printf("0\n");
		return 0;
	}

	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	flag = 0; //주위에 0이나 1이 있으면 1로,, 다 -1이면 0이 됨,,
	//인접칸이 다 -1이면 익을 가능성이 없다. => -1 출력
	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<M ; k++)
		{
			if(map[i][k] == 0) //안익은 토마토 주위 검사
			{
				for(int dir=0 ; dir<4 ; dir++)
				{
					int tx = i + dx[dir];
					int ty = k + dy[dir];

					if(tx<0 || tx>=N || ty<0 || ty>=M)
						continue;

					if(map[tx][ty] == 0 || map[tx][ty] == 1)
						flag = 1;
				}
				if(flag == 0) //익을 가능성이 없음
				{
					printf("-1\n");
					return 0;
				}
			}
		}
	}

	//익을 때까지의 최소 날짜 구하기 (BFS)
	int cnt = -1;
	while(!tomato.empty())
	{
		int size = tomato.size();
		cnt++;

		for(int i=0 ; i<size ; i++)
		{
			int x = tomato.front().first;
			int y = tomato.front().second;
			tomato.pop();

			for(int dir=0 ; dir<4 ; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];

				if(tx<0 || tx>=N || ty<0 || ty>=M)
					continue;

				if(map[tx][ty] == 0 && visited[tx][ty] == 0)
				{
					visited[tx][ty] = 1;
					map[tx][ty] = 1;
					tomato.push(pair<int,int>(tx,ty));
				}
			}
		}
	}

	printf("%d\n",cnt);


	return 0;//Your program should return 0 on normal termination.
}

/*
우선 출력해야 하는 값을 확인했다. 크게 3가지로
1) 토마토가 모두 익을 때까지의 최소 날짜
2) 만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력
3) 토마토가 모두 익지는 못하는 상황이면 -1을 출력

이 때 2) 3)을 예외상황으로 보고 먼저 처리한 후 1)에 대해서 BFS를 수행하였다.
2)에 대한 예외사항 처리는, 입력을 받을 때, 익지 않은 토마토(0)가 있는지 여부를 flag를 설정해서 처리하였다.
3)에 대한 예외사항 처리는, 익지 않은 토마토(0)에 대해서, 주변(4방향)을 검사하였다. 
주변이 모두 비었다면(-1), 익지 않은 토마토가 익을 가능성이 없으므로, -1을 출력하였다.
1)은 최소 날짜를 구하는 전형적인 BFS로 해결하였다.
*/
