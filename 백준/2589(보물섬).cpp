#include <iostream>
#include <queue>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d",&N,&M);

	string* map = new string[N];
	for(int i=0 ; i<N ; i++)
	{
		cin >> map[i];
	}

	//육지(L) BFS 시작
	int max_length = 0;
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<M ; k++)
		{
			if(map[i][k] == 'L')
			{
				int visited[51][51] = {0};
				int cnt = -1;
				queue<pair<int,int> > q;
				q.push(pair<int,int>(i,k));
				visited[i][k] = 1;

				while(!q.empty())
				{
					cnt++;

					int size = q.size();
					for(int s=0 ; s<size ; s++)
					{
						int x = q.front().first;
						int y = q.front().second;
						q.pop();

						for(int dir=0 ; dir<4 ; dir++)
						{
							int tx = x + dx[dir];
							int ty = y + dy[dir];

							if(tx<0 || ty<0 || tx>=N || ty>=M)
								continue;

							if(map[tx][ty] == 'L' && visited[tx][ty] == 0)
							{
								visited[tx][ty] = 1;
								q.push(pair<int,int>(tx,ty));
							}
						}
					}
				}
				//printf("map[%d][%d] cnt : %d\n",i,k,cnt);
				if(max_length < cnt)
					max_length = cnt;
			}
		}
	}

	printf("%d\n",max_length);


	return 0;//Your program should return 0 on normal termination.
}

/*
최단거리를 구한다는 점에서 BFS문제 이다.
문제) 보물은 서로 간에 최단 거리로 이동하는데 있어 가장 긴 시간이 걸리는 육지 두 곳에 나뉘어 묻혀있다. 
따라서 최단거리’들’ 중에서 가장 큰 값을 구하는 문제가 된다.
최단거리’들’을 구하기 위해서는 map에서 ‘L’인 영역은 모두 각각 BFS를 실행해봐야 한다. 
if(map[i][k] == 'L')
{
	int visited[51][51] = {0};
따라서, ‘L’이면 방문여부를 체크하는 배열을 다시 초기화하여 BFS를 진행하여야 한다.
*/
