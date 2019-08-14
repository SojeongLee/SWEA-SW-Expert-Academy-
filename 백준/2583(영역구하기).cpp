#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
	int M, N, K; //가로, 세로, 직사각형 개수
	scanf("%d %d %d",&M,&N,&K);

	int map[101][101] = {0};
	int x1,y1,x2,y2;
	for(int i=0 ; i<K ; i++)
	{
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		for(int a=x1 ; a<x2 ; a++)
		{
			for(int b=y1 ; b<y2 ; b++)
				map[a][b] = 1;
		}

	}

	int visited[101][101] = {0};
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};

	int cnts[10000];
	int cnt = 0;
	//BFS시작
	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<M ; k++)
		{
			if(map[i][k] == 0 && visited[i][k] == 0)
			{
				queue<pair<int,int> > area;
				area.push(pair<int,int>(i,k));
				visited[i][k] = 1;
				cnt++;

				int area_cnt = 1;
				while(!area.empty())
				{
					int x = area.front().first;
					int y = area.front().second;
					area.pop();

					for(int dir=0 ; dir<4 ; dir++)
					{
						int tx = x + dx[dir];
						int ty = y + dy[dir];

						if(tx<0 || tx>=N || ty<0 || ty>=M)
							continue;

						if(map[tx][ty] == 0 && visited[tx][ty] == 0)
						{
							visited[tx][ty] = 1;
							area.push(pair<int,int>(tx,ty));
							area_cnt++;
						}
					}
				}
				cnts[cnt] = area_cnt;
				//printf("cnt : %d, area_cnt : %d\n",cnt,area_cnt);
			}
		}
	}

	printf("%d\n",cnt);
	sort(cnts+1,cnts+1+cnt);
	for(int i=1 ; i<=cnt ; i++)
	{
		printf("%d ",cnts[i]);
	}


	return 0;//Your program should return 0 on normal termination.
}

/*
영역의 개수를 구하는 전형적인 BFS 문제이다.
다만 헷갈릴 수 있는 부분은, 왼쪽 아래 꼭지점이 (0,0)이고, 오른쪽 위 꼭지점이 (N,M)이어서, 배열의 인덱스를 처리하는 부분을 다소 신경 써야 했다.
M, N, K로 입력을 받는데, 행렬을 구성할 때에는 map[N][M]으로 하여 처리했다.
각 영역의 넓이를 오름차순으로 정렬하기 위해
#include <algorithm> 라이브러리의 sort(cnts+1,cnts+1+cnt); 함수를 사용했다.
*/
