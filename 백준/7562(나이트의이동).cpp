#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
	int T;
	scanf("%d",&T);
	for(int test_case=0 ; test_case<T ; test_case++)
	{
		int N;
		scanf("%d",&N);

		int start_x, start_y;
		int end_x, end_y;
		scanf("%d %d",&start_x, &start_y);
		scanf("%d %d",&end_x, &end_y);

		if(start_x == end_x && start_y == end_y) //x끼리 같고, y끼리 같은 것!
		{
			printf("0\n");
			continue;
		}

		queue<pair<int,int> > knight;
		int visited[301][301] = {0};
		knight.push(pair<int,int>(start_x,start_y));
		visited[start_x][start_y] = 1;

		int cnt = 0;
		int dx[8] = {-2,-2,-1,-1,1,1,2,2};
		int dy[8] = {1,-1,2,-2,2,-2,1,-1};
		while(!knight.empty())
		{
			cnt++;

			int size = knight.size();
			for(int s=0 ; s<size ; s++)
			{
				int x = knight.front().first;
			    int y = knight.front().second;
				knight.pop();
				//printf("[%d] %d, %d\n",cnt,x,y);

				for(int dir=0 ; dir<8 ; dir++)
				{
					int tx = x + dx[dir];
					int ty = y + dy[dir];

					if(tx<0 || tx>=N || ty<0 || ty>=N)
						continue;

					if(tx == end_x && ty == end_y)
						goto A;
					if(visited[tx][ty] == 0)
					{
						visited[tx][ty] = 1;
						knight.push(pair<int,int>(tx,ty));
						//printf("%d, %d\n",tx,ty);
					}
				}
			}
		}
		A:
		printf("%d\n",cnt);

	}

	return 0;//Your program should return 0 on normal termination.
}

/*
전형적인 BFS 문제이다.
이슈사항) 틀린 이유? 예외사항 처리도 다시 보자!
틀린 이유를 아무리 봐도 모르겠어서, 예외사항 부분을 보니 실수한 부분이 있었다.

나이트가 현재 있는 칸과 나이트가 이동하려고 하는 칸이 같다면, 이동할 필요가 없으므로 0을 출력하면 된다. 이 부분을 처음에
if(start_x == start_y && end_x == end_y)
로 잘못 썼었다. 하지만 문제에서 제시한 테스트케이스는 (1,1) (1,1)이어서 통과되어 오류를 발견하지 못했던 것이다. 이 부분을

if(start_x == end_x && start_y == end_y) //x끼리 같고, y끼리 같은 것!
로 바꾸어 오류를 해결할 수 있었다.
*/
