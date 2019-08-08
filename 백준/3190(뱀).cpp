#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{

	int N;
	scanf("%d", &N);
	
	int Apple;
	scanf("%d", &Apple);

	int map[110][110] = { 0 }; //빈칸:0, 사과:1, 뱀:2
	for (int i = 0; i < Apple; i++)
	{
		int tx, ty;
		scanf("%d %d", &tx, &ty);
		map[tx][ty] = 1; 
	}

	int cnt = 0; //게임 실행 시간(초)
	queue<pair<int, int> > snake;
	snake.push(pair<int, int>(1, 1));
	map[1][1] = 2; //1행1열에서 뱀이 시작
	//int x = 1, y = 1; //뱀의 현재 좌표
	
	int dir = 0; //동, 서, 남, 북
	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = {1, -1, 0, 0}; 

	int L;
	scanf("%d", &L);

	int X;
	char C;
	for (int i = 0; i <= L; i++)
	{
		if (i != L) //마지막 명령은 계속 실행되어야 하므로,,
		{
			scanf("%d %c", &X, &C);
		}

		while (1)
		{
			cnt++;
			//현재 방향으로 한칸 이동함
			int tx = snake.back().first + dx[dir];
			int ty = snake.back().second + dy[dir];
			//map[tx][ty] = 2;
			//printf("cnt = %d, 뱀 : %d, %d\n",cnt, tx, ty);

			if (tx <= 0 || tx > N || ty <= 0 || ty > N) //벽에 부딪힘 => 게임이 끝남
			{
				printf("%d\n", cnt);
				return 0;
			}
			if (map[tx][ty] == 2) //뱀 몸에 부딪힘 => 게임이 끝남
			{
				printf("%d\n", cnt);
				return 0;
			}

			//사과를 먹지 않은 경우 : push & pop
			if (map[tx][ty] == 0)
			{
				//push
				map[tx][ty] = 2;
				snake.push(pair<int, int>(tx, ty));
				//pop
				tx = snake.front().first;
				ty = snake.front().second;
				map[tx][ty] = 0;
				snake.pop();
			}
			//사과를 먹은 경우 : push
			else if(map[tx][ty] == 1)
			{
				//push
				map[tx][ty] = 2;
				snake.push(pair<int, int>(tx, ty));
			}

			/*printf("cnt = %d\n", cnt);
			for (int a = 1; a <= N; a++)
			{
				for (int b = 1; b <= N; b++)
				{
					printf("%d", map[a][b]);
				}printf("\n");
			}printf("\n");*/

			//방향을 바꿔야,,
			if (cnt == X)
			{
				switch (C)
				{
				case 'L'://왼쪽으로 턴
					if (dir == 0) dir = 3;
					else if (dir == 1) dir = 2;
					else if (dir == 2) dir = 0;
					else if (dir == 3) dir = 1;
					break;
				case 'D'://오른쪽으로 턴
					if (dir == 0) dir = 2;
					else if (dir == 1) dir = 3;
					else if (dir == 2) dir = 1;
					else if (dir == 3) dir = 0;
					break;
				}

				break;
			}
		
		}

	}

	return 0;//Your program should return 0 on normal termination.
}


/*
맨 처음에는 문제 이해가 잘 되지 않아, 구글에 snake game을 검색해서 플레이를 해보았다.
우선 맵을 2차원 배열로 만들고 0으로 초기화했다. 0은 빈칸을, 1은 사과를, 2를 뱀을 의미하도록 하였다.
그런 다음 queue<pair<int, int> > snake를 만들었는데, snake의 x,y좌표를 저장시킬 자료구조이다. 처음에는 (1,1)을 push 시킨다.

while(1)을 실행시키고, 게임이 끝날 조건에 걸리면 return 0;으로 프로그램을 종료하도록 하였다. 게임이 끝날 조건은 2가지로
1) 벽에 부딪히는 경우 2) 뱀 몸에 부딪히는 경우 이다.

이 두 가지 경우가 아니라면, 뱀은 한 칸을 이동하는데 이 때, 사과를 먹었는지의 여부가 중요하다.
1) 사과를 먹지 않은 경우 : 뱀의 몸은 늘어나지 않으므로, 머리부분을 push하고, 꼬리부분을 pop한다.
2) 사과를 먹은 경우 : 뱀의 몸이 늘어나므로, 머리부분을 push한다.

그 다음 포인트로는, 뱀의 머리가 방향을 바꾸는 경우이다. dir 변수 값 0,1,2,3을 동,서,남,북 으로 생각하였고, 
dx[4]와 dy[4]를 좌표에 더해감으로써, 이동하는 것으로 구현했다.

이슈사항1) for문의 인덱스는 i=0부터 i<=L 까지!
명령이 L개이므로, 처음에는 i<L 로 for문의 종료조건을 설정하였다. 
하지만 마지막 명령은 게임이 종료되기 전까지는 계속 실행되어야 하는 것이므로, 
이러한 효과를 주기 위해서는 명령은 L개를 받지만, 마지막 명령이 실행되게 하기 위해서는 하나의 명령이 더 있어야 하는 것이다.

이슈사항2) 런타임 에러
런타임 에러는 보통 배열의 인덱스 문제에서 발생한다고 한다. 
처음에 int map[100][100]으로 설정하였는데, 문제에서 1부터100까지의 수가 N으로 올 수 있으므로, int map[101][101]로 설정해야 한다.
앞으로는 배열의 인덱스를 다소 넉넉히 설정해야겠다고 생각하였다. 
가령 이 문제에선 int map[110][110]정도로 설정하면, 런타임 에러를 애초에 막을 수 있다.
*/
