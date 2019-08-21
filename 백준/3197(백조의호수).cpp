#include <iostream>
#include <queue>
#include <string>
#include <algorithm> //swap함수

using namespace std;

int visited_water[1501][1501]; //몇일만에 빙산이 녹는지 저장
bool visited_q[1501][1501];

int main(int argc, char** argv)
{
	int R, C;
	scanf("%d %d", &R, &C);

	string *map = new string[R];
	//물
	queue<pair<int, int> > water;
	//백조
	int st_x, st_y;
	for (int i = 0; i < R; i++)
	{
		cin >> map[i];
		for (int k = 0; k < C; k++)
		{
			if (map[i][k] == '.' || map[i][k] == 'L')
			{
				water.push(pair<int, int>(i, k));
				visited_water[i][k] = 0;
			}
			if (map[i][k] == 'L')
			{
				st_x = i;
				st_y = k;
			}
		}
	}

	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	//빙산이 다 녹는 시간 전처리
	int wc = 1;
	while (!water.empty())
	{
		int size = water.size();
		//printf("wc = %d, size = %d\n",wc,size);
		for (int s = 0; s < size; s++)
		{
			int x = water.front().first;
			int y = water.front().second;
			water.pop();
			for (int dir = 0; dir < 4; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];
				if (tx < 0 || ty < 0 || tx >= R || ty >= C)
					continue;
				if (visited_water[tx][ty] == 0 && map[tx][ty] == 'X')
				{
					visited_water[tx][ty] = wc;
					map[tx][ty] = '.';
					water.push(pair<int, int>(tx, ty));
				}
			}
		}
		wc++;
	}

	/*for (int i = 0; i < R; i++)
	{
		for (int k = 0; k < C; k++)
			printf("%d ", visited_water[i][k]);
		printf("\n");
	}*/

	//이분탐색
	int min_day = 0;
	int max_day = wc-2;
	int day = max_day / 2.0 + 0.5;
	while(1) 
	{
		//백조가 day일 만에 만날 수 있는지 확인
		int flag = 0; //만날 수 있으면 1로

		queue < pair<int, int> > q;
		q.push(pair<int, int>(st_x, st_y));
		//visited_q 배열 초기화 해야!
		for(int i=0 ; i<R ; i++)
		{
			for(int k=0 ; k<C ; k++)
				visited_q[i][k] = 0;
		}
		visited_q[st_x][st_y] = 1;	
		while (!q.empty())
		{
			int x = q.front().first;
			int y = q.front().second;
			q.pop();
			for (int dir = 0; dir < 4; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];
				if (tx < 0 || ty < 0 || tx >= R || ty >= C)
					continue;
				if (visited_q[tx][ty] == 0 && visited_water[tx][ty] <= day)
				{
					//printf("%d, %d\n", tx, ty);
					visited_q[tx][ty] = 1;
					q.push(pair<int, int>(tx, ty));
					if (map[tx][ty] == 'L')
					{
						flag = 1;
						goto A;
						//printf("tc = %d, 좌표 : %d, %d\n", tc, tx, ty);
					}
				}
			}
		}
		A:
		/*printf("day : %d, flag : %d\n",day,flag);
		for (int i = 0; i < R; i++)
		{
			for (int k = 0; k < C; k++)
				printf("%d ", visited_q[i][k]);
			printf("\n");
		}*/
		if(flag) //백조들이 만남 
		{
			max_day = day;
		}
		else //백조들이 못만남 
		{
			min_day = day;
		}
		day = (min_day + max_day) / 2.0 + 0.5;
		if(day >= max_day)
			break;
	}

	printf("%d\n",day);

	return 0;//Your program should return 0 on normal termination.
}

/*
우선 처음에는 누구나 생각할 평범한 BFS를 사용하여,
1) 얼음을 녹이고 2) 백조가 서로 만날 수 있는지 확인했다.
하지만 이렇게 풀면 ‘시간초과’가 난다.

결국 질문)탭 https://www.acmicpc.net/board/view/18525에서 아이디어를 얻어 풀었다.
아이디어는 크게 두 가지 절차로
1) 빙산이 몇 일째에 녹는지 미리 전처리를 하는 겁니다.
2) 이분탐색 (d일 째에 백조가 서로 만나지 못했는데, d-1일 째에는 백조가 만날 수 있을까?)
이다.

빙산이 몇 일째에 녹는지 전처리 하는 부분은, BFS로 한 칸씩 이동하여 하면 된다.

이분탐색 부분을 거의 처음 코딩 해보았는데, 
//이분탐색
int min_day = 0;
int max_day = wc-2;
int day = max_day / 2.0 + 0.5;
이 세 변수를 두어 처리하였다. 
0.5를 더해 준 이유는, 홀수일 때, 예를 들어 3일 때, 1이 아닌 2일부터 탐색하고 싶어서 더해주었다.

if (visited_q[tx][ty] == 0 && visited_water[tx][ty] <= day)
방문할 때, 방문을 안 한곳임을 체크하는 것은 물론, 
day보다 작거나 같다. 즉 빙산이 녹은 곳이면 방문할 수 있도록 하였다.
백조들이 해당 day에 만났으면 max_day를 day로 줄여야 하고, 못만났으면 min_day를 day로 늘려야 한다. 
이 부분이 이분탐색의 적용 부분이다.
*/
