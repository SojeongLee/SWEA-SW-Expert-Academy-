#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
	int	N;
	scanf("%d",&N);

	string *map = new string[N];
	for(int i=0 ; i<N ; i++)
	{
		cin >> map[i];
	}

	//단지 개수 확인
	int visited[25][25] = {0};
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	
	int cnt[30] = {0};
	int dangi_cnt = 0; 
	int house_cnt = 0;

	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<N ; k++)
		{
			if(map[i][k] == '1' && visited[i][k] == 0) //BFS 시작
			{
				queue<pair<int,int> > house;
				dangi_cnt++;
				house_cnt = 1;

				house.push(pair<int,int>(i,k));
				visited[i][k] = 1;

				while(!house.empty())
				{
					int x = house.front().first;
					int y = house.front().second;
					house.pop();

					for(int dir=0 ; dir<4 ; dir++)
					{
						int tx = x + dx[dir];
						int ty = y + dy[dir];

						if(tx<0 || tx>=N || ty<0 || ty>=N)
							continue;

						if(map[tx][ty] == '1' && visited[tx][ty] == 0)
						{
							house_cnt++;
							visited[tx][ty] = 1;
							house.push(pair<int,int>(tx,ty));
						}
					}
				}
				cnt[dangi_cnt] = house_cnt;
				//printf("cnt[%d] = %d\n",dangi_cnt,house_cnt);
			}
		}
	}

	printf("%d\n",dangi_cnt);
	sort(cnt+1,cnt+1+dangi_cnt);
	for(int i=1 ; i<=dangi_cnt ; i++)
	{
		printf("%d\n",cnt[i]);
	}


	return 0;//Your program should return 0 on normal termination.
}

/*
각 단지에 속하는 집의 수를 오름차순으로 정렬하기 위해,
#include <algorithm>
를 사용하였다.
sort(cnt+1,cnt+1+dangi_cnt);
cnt배열의 1번부터 dangi_cnt번까지 정렬하기 위해서는, 
sort함수의 첫 번째 인자로는 cnt+1을, 두 번째 인자로는 cnt+1+dangi_cnt를 주면 된다. 
*/
