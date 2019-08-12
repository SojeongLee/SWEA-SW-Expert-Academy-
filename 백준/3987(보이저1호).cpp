#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d", &N, &M);

	string *map = new string[N];
	for (int i = 0; i < N; i++)
	{
		cin >> map[i];
	}

	int X, Y; //탐사선의 위치
	scanf("%d %d", &X, &Y);
	X--, Y--; //배열의 인덱스는 0부터 시작하므로,,

	//위:U / 오른쪽:R / 아래:D / 왼쪽:L 한 번씩 해서, MAX 구하기
	int MAX = 0;
	int MAX_IND = 0;
	int dx[4] = {-1,0,1,0};
	int dy[4] = {0,1,0,-1};
	int DIR; //U/R/D/L
	for (DIR = 0; DIR < 4; DIR++)
	{
		int dir = DIR;
		int cnt = 0;
		int tx = X;
		int ty = Y;
		//전파시작
		while (1)
		{
			cnt++;
			tx += dx[dir];
			ty += dy[dir];
			//printf("%d, %d\n", tx, ty);

			if (tx<0 || tx>=N || ty<0 || ty>=M) //항성계 범위를 벗어남 => 전파 종료
				break;
			if (map[tx][ty] == 'C') //블랙홀 => 전파 종료
				break;

			if (map[tx][ty] == '/')
			{
				switch (dir)
				{
				case 0: dir = 1; break;
				case 1: dir = 0; break;
				case 2: dir = 3; break;
				case 3: dir = 2; break;
				}
			}
			else if (map[tx][ty] == '\\')
			{
				switch (dir)
				{
				case 0: dir = 3; break;
				case 1: dir = 2; break;
				case 2: dir = 1; break;
				case 3: dir = 0; break;
				}
			}

			if (cnt > 250000)
			{
				switch (DIR)
				{
				case 0: printf("U\n"); break;
				case 1: printf("R\n"); break;
				case 2: printf("D\n"); break;
				case 3: printf("L\n"); break;
				}
				printf("Voyager\n");
				return 0;
			}
		}
		//printf("DIR : %d, cnt : %d\n", DIR, cnt);
		//최댓값 갱신
		if (MAX < cnt)
		{
			MAX = cnt;
			MAX_IND = DIR;
		}
	}

	switch (MAX_IND)
	{
	case 0: printf("U\n"); break;
	case 1: printf("R\n"); break;
	case 2: printf("D\n"); break;
	case 3: printf("L\n"); break;
	}
	printf("%d\n", MAX);

	return 0;//Your program should return 0 on normal termination.
}

/*
이슈사항1) 역슬래쉬 문자 비교
‘\’로 비교하려 하였으나 빨간줄이 갔다. ‘\\’로 비교하여야 한다. 

이슈사항2) Voyager만 출력하면 안됐다.
처음에는 틀린 이유를 몰라서, 해당 문제의 대회 테스트케이스를 살펴보니, 
Voyager를 출력할 때에도 어떤 방향(U/R/D/L)에서 무한히 시그널이 전파되는지를 출력해야 했다.
if (cnt > 250000)
{
	switch (DIR)
항성계의 크기가 500바이500이 최대이므로, 전파횟수 cnt가 25만이 넘어가면, 무한히 전파되는 것으로 보았다.
또한 이 때, 현재 방향 DIR에 따라서 U/R/D/L 알파벳을 먼저 출력하고, 그 다음 줄에 Voyager를 출력해야 한다.
*/
