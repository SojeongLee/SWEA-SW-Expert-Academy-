#include <iostream>
#include <queue>

using namespace std;

int map[1010][1010] = {0}; //0으로 초기화, 안전함

int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d",&N,&M);

	int Q,K,P;
	int x, y;
	queue<pair<int,int> > Queen, Knight;
	
	scanf("%d",&Q);
	for(int i=0 ; i<Q ; i++)
	{
		scanf("%d %d",&x,&y);
		Queen.push(pair<int,int>(x, y));
		map[x][y] = 1; //1이면 퀸
	}
	scanf("%d",&K);
	for(int i=0 ; i<K ; i++)
	{
		scanf("%d %d",&x, &y);
		Knight.push(pair<int,int>(x, y));
		map[x][y] = 2; //2이면 나이트
	}
	scanf("%d",&P);
	for(int i=0 ; i<P ; i++)
	{
		scanf("%d %d",&x,&y);
		map[x][y] = 3; //3이면 pawn
	}

	int cnt = N*M -Q-K-P; //초기 안전한 칸의 개수
	//printf("초기 안전칸 개수 : %d\n",cnt);
	//퀸이 잡을 수 있는 곳을 4로,,
	int dx[8] = {-1,-1,1,1,0,0,1,-1};
	int dy[8] = {-1,1,-1,1,1,-1,0,0};
	int tx, ty;
	while(!Queen.empty())
	{
		x = Queen.front().first;
		y = Queen.front().second;
		Queen.pop();

		for(int dir=0 ; dir<8 ; dir++)
		{
			tx = x, ty = y;
			while(1)
			{
				tx += dx[dir];
				ty += dy[dir];
				if(tx<=0 || tx>N || ty<=0 || ty>M)
					break;
				if(map[tx][ty] == 0) //현재 빈칸(안전한칸)이면 4로 설정(잡힐 수 있는 지역)
				{
					map[tx][ty] = 4;
					cnt--;
				}
				else if(map[tx][ty] == 4)
					continue;
				else
					break;					
			}
		}
	}

	//나이트가 잡을 수 있는 곳을 4로,,
	int nx[8] = {-2,-1,1,2,-2,-1,1,2};
	int ny[8] = {-1,-2,-2,-1,1,2,2,1};
	while(!Knight.empty())
	{
		x = Knight.front().first;
		y = Knight.front().second;
		Knight.pop();

		for(int dir=0 ; dir<8 ; dir++)
		{
			tx = x + nx[dir];
			ty = y + ny[dir];
			if(tx<=0 || tx>N || ty<=0 || ty>M)
				continue;
			if(map[tx][ty] == 0) //현재 빈칸(안전한칸)이면 4로 설정(잡힐 수 있는 지역)
			{
				map[tx][ty] = 4;
				cnt--;
			}
		}
	}

	//안전한 구역(0)을 센다.
	cout << cnt << endl;
	/*for(int i=1 ; i<=N ; i++)
	{
		for(int k=1 ; k<=M ; k++)
		{
			printf("%d ",map[i][k]);
		}printf("\n");
	}*/


	return 0;//Your program should return 0 on normal termination.
}

/*
map을 0으로 초기화하였다.
0은 안전구역, 1은 퀸 위치, 2는 나이트 위치, 3은 Pawn 위치, 4는 잡힐 구역으로 설정했다.
퀸과 나이트 모두 8가지 방향으로 이동할 수 있다.
다른 점은 퀸의 이동은 연속적이기 때문에, while문을 사용하였고,
나이트는 딱 8방향으로 한 번씩만 검사하면 된다. 
이슈사항) 0이어야만 방문? 아니다!
처음에는 퀸이 방문하는 것을
if(map[tx][ty] == 0) //현재 빈칸(안전한칸)이면 4로 설정(잡힐 수 있는 지역)
{
	map[tx][ty] = 4;
	cnt--;
}
else
	break;	
로 해서 계속 틀렸었다. 질문 올라와있는 걸 참조해서 풀 수 있었다.

답변) 어떤 퀸이 어떤 칸에 먼저 방문했다고 해서, 다른 퀸이 그 칸을 지나가면 안 되는 건 아닙니다.
즉, 0이어야만 방문하는 것이 아니고, 4여도 방문할 수 있다. 
정확히 말하면 방문이 아니라 지나갈 수 있는 것이다. (4는 잡힐 구역이지, 장애물이 아니기 때문이다)
else if(map[tx][ty] == 4)
	continue;
따라서, else if문을 추가하여, 4일 때는, continue;를 하여 지나갈 수 있도록 수정하였다.
*/
