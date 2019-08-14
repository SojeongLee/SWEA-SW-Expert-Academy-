#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
	int N;
	scanf("%d",&N);

	int map[101][101];
	int low = 100;
	int high = 1;
	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<N ; k++)
		{
			scanf("%d",&map[i][k]);
			if(high < map[i][k]) high = map[i][k];
			if(low > map[i][k]) low = map[i][k];
		}
	}

	int MAX = 1; //물에 잠기지 않는 안전한 영역의 최대 개수
	int test_map[101][101];
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	for(int level=low ; level<high ; level++)
	{
		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<N ; k++)
			{
				test_map[i][k] = map[i][k];
				if(map[i][k] <= level) //물에 잠기게 됨 => -1로 설정
					test_map[i][k] = -1;
			}
		}

		//BFS로 안전한 영역의 개수 구하기
		int cnt = 0;
		int visited[101][101] = {0};
		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<N ; k++)
			{
				if(test_map[i][k] != -1 && visited[i][k] == 0)
				{
					queue<pair<int,int> > area;
					area.push(pair<int,int>(i,k));
					visited[i][k] = 1;
					cnt++;

					while(!area.empty())
					{
						int x = area.front().first;
						int y = area.front().second;
						area.pop();

						for(int dir=0 ; dir<4 ; dir++)
						{
							int tx = x + dx[dir];
							int ty = y + dy[dir];

							if(tx<0 || tx>=N || ty<0 || ty>=N)
								continue;

							if(test_map[tx][ty] != -1 && visited[tx][ty] == 0)
							{
								visited[tx][ty] = 1;
								area.push(pair<int,int>(tx,ty));
							}
						}
					}
				}
			}
		}

		if(MAX < cnt)
			MAX = cnt;
	}

	printf("%d\n",MAX);


	return 0;//Your program should return 0 on normal termination.
}

/*
우선 물에 잠길 높이는 입력 받을 때, low와 high 변수로 구하였다.
map[][]을 test_map[][]으로 복사해서 사용했는데, 이 때, 물에 잠길 영역은 -1의 값을 주어 표시했다. 
이렇게 test_map[][]을 만들었으면, BFS로 안전한 영역의 개수를 구했다.

문제의 노트에) 아무 지역도 물에 잠기지 않을 수도 있다.
를 참고하여 초기값을 MAX = 1로 설정하였고, 영역의 개수를 구한 뒤, MAX보다 크면 업데이트해 나갔다.
*/
