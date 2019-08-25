#include <iostream>
#include <queue>
#include <string>

using namespace std;

int bomb[300][300];
int visited[300][300];

int main(int argc, char** argv)
{
	int T;
	scanf("%d",&T);
	for(int test_case = 1 ; test_case <= T ; test_case++)
	{
		int N;
		scanf("%d",&N);

		string* map = new string[N];
		for(int i=0 ; i<N ; i++)
		{
			cin >> map[i];
		}

		//1.주변 지뢰 개수가 0인 곳 check
		int dx[8] = {-1,-1,-1,0,0,1,1,1};
		int dy[8] = {-1,0,1,-1,1,-1,0,1};

		int bomb_cnt = 0; //지뢰 개수
		queue<pair<int,int> > q; //0인 곳을 저장하는 큐 => 2. 에서 사용
		queue<pair<int,int> > q2; //q와 같은데, 복사해 놓는 것 => 3. 에서 사용

		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<N ; k++)
			{
				if(map[i][k] == '*') //지뢰이면 건너뜀
				{
					bomb[i][k] = -1;
					bomb_cnt++;
					continue;
				}
				int cnt = 0;
				for(int dir=0 ; dir<8 ; dir++)
				{
					int tx = i + dx[dir];
					int ty = k + dy[dir];
					if(tx<0 || ty<0 || tx>=N || ty>=N)
						continue;

					if(map[tx][ty] == '*')
					{
						cnt = 1; //1개 이상임을 의미
						break;
					}
				}
				bomb[i][k] = cnt;
				if(cnt == 0)
				{
					q.push(pair<int,int>(i,k));
					q2.push(pair<int,int>(i,k));
				}
			}
		}

		//2. BFS로 0인 부분(덩어리) cnt1
		int cnt1 = 0; //연쇄해서 터지는 0인 곳 개수
		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<N ; k++)
				visited[i][k] = 0;
		}

		while(!q.empty())
		{
			int x = q.front().first;
			int y = q.front().second;
			q.pop(); 
			if(visited[x][y])
				continue;
			visited[x][y] = 1;
			//printf("q : %d, %d\n", x,y);

			queue<pair<int,int> > t;
			t.push(pair<int,int>(x,y));
			while(!t.empty())
			{
				x = t.front().first;
				y = t.front().second;
				t.pop(); //printf("t : %d, %d\n", x,y);
				for(int dir=0 ; dir<8 ; dir++)
				{
					int tx = x + dx[dir];
					int ty = y + dy[dir];
					if(tx<0 || ty<0 || tx>=N || ty>=N)
						continue;

					if(bomb[tx][ty] == 0 && visited[tx][ty] == 0)
					{
						t.push(pair<int,int>(tx,ty));
						cnt1++;
						visited[tx][ty] = 1; //printf("	%d, %d\n", tx,ty);
					}
				}
			}
		}
		
		//3. 연쇄해서 터지는 부분 cnt
		int cnt2 = 0; //연쇄해서 터지는 0이 아닌 곳 개수

		while(!q2.empty())
		{
			int x = q2.front().first;
			int y = q2.front().second;
			q2.pop(); //printf("%d, %d\n", x,y);

			for(int dir=0 ; dir<8 ; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];
				if(tx<0 || ty<0 || tx>=N || ty>=N)
					continue;

				if(bomb[tx][ty] == 1 && visited[tx][ty] == 0)
				{
					cnt2++;
					visited[tx][ty] = 1; //printf("	%d, %d\n", tx,ty);
				}
			}
		}
		//printf("cnt1 : %d, cnt2 : %d\n",cnt1, cnt2);
		int CNT = N*N - bomb_cnt - cnt1 - cnt2;	
		printf("#%d %d\n",test_case, CNT);
	}

	return 0;
}

/*
크게 3단계로 풀었다.
1. 주변에 지뢰가 없는 곳(0인 곳)을 check (지뢰가 있는 곳은 1이상일텐데, 모두 1로 표시하였다.)
2. BFS로 0인 부분을 덩어리 로 다 터뜨리기
3. 0인 덩어리에서 한 겹 더 터뜨리기

이슈사항) 한 번 BFS로 다 터뜨리려 하였으나,,
처음에는 BFS를 한 번해서, 0과 인접한 부분이면 모두 터뜨리려고 하였으나,
0과 0이 인접해있는 경우를 처리하기 까다로워져서, 결국엔 2) 3)으로 분리하였다.
2에는 BFS를 적용하여, 0인 곳을 모두 터뜨리고, 
3)에서는 0인 덩어리에서 한 겹 더 터뜨리는 것으로 문제를 해결하였다.
*/
