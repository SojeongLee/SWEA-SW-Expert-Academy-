#include <iostream>
#include <queue>
#include <vector>
#include <math.h>

using namespace std;


int main(int argc, char** argv)
{ 
	int N, L, R;
	scanf("%d %d %d",&N,&L,&R);

	int map[50][50];
	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<N ; k++)
			scanf("%d",&map[i][k]);
	}

	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};

	int CNT = 0;
	while(1)
	{
		int flag2 = 0;	

		int visited[50][50] = {0};
		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<N ; k++)
			{
				int flag = 0;
				if(visited[i][k] == 0)
				{
					visited[i][k] = 1;
					queue<pair<int,int> > q;
					q.push(pair<int,int>(i,k));

					vector<pair<int,int> > t;
					t.push_back(pair<int,int>(i,k));
					//연합 찾기
					while(!q.empty())
					{
						int x = q.front().first;
						int y = q.front().second;
						q.pop();
						for(int dir=0 ; dir<4 ; dir++)
						{
							int tx = x + dx[dir];
							int ty = y + dy[dir];
							if(tx<0 || ty<0 || tx>=N || ty>=N)
								continue;
							if(visited[tx][ty])
								continue;

							int diff = abs(map[x][y] - map[tx][ty]);
							if(diff>=L && diff<=R)
							{
								flag = 1;
								flag2 = 1;

								visited[tx][ty] = 1;
								q.push(pair<int,int>(tx,ty));
								t.push_back(pair<int,int>(tx,ty));
							}
						}
					}
					if(flag)
					{
						//인구이동
						int sum = 0;
						int size = t.size();
						for(int i=0 ; i<size ; i++)
							sum += map[t[i].first][t[i].second];

						int result = sum / size;
						for(int i=0 ; i<size ; i++)
							map[t[i].first][t[i].second] = result;
					}
				}
			}
		}
		if(flag2) CNT++; 
		else break;
	}

	printf("%d\n",CNT);


	return 0;
}

/*
크게 3단계로 풀었다.
1. 인구이동이 일어날 연합을 찾는다.
2. 그 연합에 대해서 인구이동을 실시한다.
3. 만약 1)에서 인구이동이 일어날 연합을 찾지 못했다면, 종료한다.

1)에서 연합을 찾을 때, BFS를 사용했다. 
하지만 BFS는 큐가 empty가 되면 종료하게 되므로, 
해당 연합에 속하는 좌표들을 따로 저장해 놓을 템프 벡터 t를 사용하였다. 
*/
