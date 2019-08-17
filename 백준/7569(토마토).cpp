#include <iostream>
#include <queue>

using namespace std;

int map[101][101][101] = {0};
int visited[101][101][101] = {0};

int main(int argc, char** argv)
{
	int M, N, H;
	scanf("%d %d %d",&M,&N,&H);

	int flag = 1; //모든 토마토가 익어있는 상태면 1이 된다.
	queue<pair<int,pair<int,int> > > young_tomato;
	queue<pair<int,pair<int,int> > > tomato;
	for(int h=0 ; h<H ; h++)
	{
		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<M ; k++)
			{
				scanf("%d",&map[h][i][k]);
				if(map[h][i][k] == 0) //익지 않은 토마토가 있음
				{
					flag = 0;
					young_tomato.push(pair<int,pair<int,int> >(h,pair<int,int>(i,k)));
				}
				else if(map[h][i][k] == 1)
				{
					tomato.push(pair<int,pair<int,int> >(h,pair<int,int>(i,k)));
					visited[h][i][k] = 1;
				}
			}
		}
	}

	if(flag) //모든 토마토가 익어있음 => 0출력
	{
		printf("0\n");
		return 0;
	}

	//토마토가 모두 익지는 못하는 상황(주변에 익은 토마토:1/익지않은 토마토:0가 없음) => -1출력
	int dx[6] = {0,0,1,-1,0,0};
	int dy[6] = {1,-1,0,0,0,0};
	int dh[6] = {0,0,0,0,1,-1};
	//flag = 0; //모두 익지 못하는 상황이면 0으로
	while(!young_tomato.empty())
	{
		flag = 0; //모두 익지 못하는 상황이면 0으로
		int x = young_tomato.front().second.first;
		int y = young_tomato.front().second.second;
		int h = young_tomato.front().first;
		young_tomato.pop();
		for(int dir=0 ; dir<6 ; dir++)
		{
			int tx = x + dx[dir];
			int ty = y + dy[dir];
			int th = h + dh[dir];

			if(tx<0 || ty<0 || th<0 || tx>=N || ty>=M || th>=H)
				continue;

			if(map[th][tx][ty] == 1 || map[th][tx][ty] == 0)
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0) //모두 익지 못하는 상황 => -1출력
		{
			printf("-1\n");
			return 0;
		}
	}

	//BFS시작
	int cnt = -1;
	while(!tomato.empty())
	{
		cnt++;
		int size = tomato.size();
		for(int s=0 ; s<size ; s++)
		{
			int x = tomato.front().second.first;
			int y = tomato.front().second.second;
			int h = tomato.front().first;
			tomato.pop();
			for(int dir=0 ; dir<6 ; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];
				int th = h + dh[dir];

				if(tx<0 || ty<0 || th<0 || tx>=N || ty>=M || th>=H)
					continue;

				if(map[th][tx][ty] == 0 && visited[th][tx][ty] == 0)
				{
					visited[th][tx][ty] = 1;
					map[th][tx][ty] = 1;
					tomato.push(pair<int,pair<int,int> >(th,pair<int,int>(tx,ty)));
				}
			}
		}
	}

	printf("%d\n",cnt);

	return 0;//Your program should return 0 on normal termination.
}

/*
7576(토마토).cpp 랑 차수만 달라진 문제이다.
기존 2차원배열을 3차원배열로만 바꾸면 된다.
이 때, 3차원배열을 구성하기 위해, 큐를 사용할 때,
queue<pair<int,pair<int,int> > > tomato;

tomato.push(pair<int,pair<int,int> >(h,pair<int,int>(i,k)));

int x = young_tomato.front().second.first;
int y = young_tomato.front().second.second;
int h = young_tomato.front().first;
위와 같은 문법을 사용하였다. 
queue<tuple<int,int,int> >와 같은 형식을 사용할 수도 있다.

이슈사항) 틀렸습니다 이유 : flag 설정할 때 위치 생각하기
토마토가 모두 익지 못하는 상황을 판단할 때, 각각의 익지 않은 토마토에 대해서 판별해야 한다. 
따라서, while문 안에 flag = 0을 설정해야 한다.
*/
