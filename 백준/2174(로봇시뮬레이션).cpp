#include <iostream>

using namespace std;

struct Robot
{
	int x, y;
	int dir; //0:동, 1:북, 2:서, 3:남
};

int main(int argc, char** argv)
{
	int A, B; //줄, 열
	scanf("%d %d", &A, &B);

	int N, M; //로봇 수, 명령 수
	scanf("%d %d", &N, &M);

	int map[110][110] = { 0 }; //줄:1번~A번, 열:1번~B번
	struct Robot robot[110];
	//초기화
	int tx, ty;
	char td;
	for (int i = 1; i <= N; i++) //로봇 1번~N번
	{
		scanf("%d %d %c", &tx, &ty, &td);
		robot[i].x = tx;
		robot[i].y = ty;
		switch (td)
		{
		case 'E': robot[i].dir = 0; break;
		case 'N': robot[i].dir = 1; break;
		case 'W': robot[i].dir = 2; break;
		case 'S': robot[i].dir = 3; break;
		}
		map[tx][ty] = i;
	}

	//이동방향 : 동-북-서-남(반시계)로갈때 ++
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	int TD; //0:동, 1:북, 2:서, 3:남
	//명령을 입력받아 실행
	int num, loop; //명령을 받는 로봇, 명령 반복 회수
	char type; //명령의 종류(L:왼쪽으로90도회전, R:오른쪽으로90도회전, F:한칸앞으로)
	for (int i = 1; i <= M; i++) //명령 1번~N번
	{
		scanf("%d %c %d", &num, &type, &loop);

		if (type == 'L') //0->1->2->3->0
		{
			loop = loop % 4;
			robot[num].dir = (robot[num].dir + loop) % 4;
		}
		else if (type == 'R') //0->3->2->1->0
		{
			loop = loop % 4;
			robot[num].dir = (robot[num].dir + 4 - loop) % 4;
		}
		else //type == 'F'
		{
			tx = robot[num].x;
			ty = robot[num].y;
			TD = robot[num].dir;
			//충돌 시뮬레이션
			for (int f = 0; f < loop; f++)
			{
				tx += dx[TD];
				ty += dy[TD];

				if (tx<1 || tx>A || ty<1 || ty>B) //범위를 벗어남 -> 벽에 충돌
				{
					//int a, b;
					//char c;
					//for(int h=0 ; h<N-i ; h++) //남은 입력 받기,,
					//	scanf("%d %c %d", &a, &c, &b); 
					printf("Robot %d crashes into the wall", num);
					return 0;
				}
				else if (map[tx][ty] != 0) //다른 로봇에 충돌
				{
					//int a, b;
					//char c;
					//for (int h = 0; h < N - i; h++) //남은 입력 받기,,
					//	scanf("%d %c %d", &a, &c, &b);
					printf("Robot %d crashes into robot %d", num, map[tx][ty]);
					return 0;
				}

				map[robot[num].x][robot[num].y] = 0;
				robot[num].x = tx;
				robot[num].y = ty;
				map[robot[num].x][robot[num].y] = num;
			}

		}

	}

	printf("OK");


	return 0;//Your program should return 0 on normal termination.
}

/*
크게 4가지 포인트로 문제를 해결하였다.
1) 우선 Robot이라는 struct를 선언하였다. 로봇의 좌표와 방향을 변수로 갖게 하였다.
2) 로봇끼리의 충돌검사를 어떻게 할까? 일일이 모든 로봇을 포문으로 돌릴 수는 없다고 생각하여, 
	map[][]을 선언하여, 해당 좌표에 있는 로봇의 넘버를 값으로 저장하였다. 
	예를 들어, 5,4지점에 로봇 2가 있다면, map[5][4]=2로 하였다. 
	로봇이 없는 지점은 다 0으로 초기화했다. (로봇은 1번부터 N번까지 있으므로)
3) 로봇이 시계/반시계 방향으로 전환하는 것을 어떻게 할까? 
	우선 반시계방향은 동->북->서->남을 바라보는 것이다. 
	따라서 동:0->북:1->서:2->남:3 이라는 번호를 부여했다. 
	따라서 반시계방향은 디랙션을++, 시계방향은 디랙션을-- 하면 된다.
4) 해당방향으로 이동하는 것을 어떻게 할까?
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	int TD; //0:동, 1:북, 2:서, 3:남

	tx += dx[TD];
	ty += dy[TD];
	이제껏 그래왔듯,, dx[4]와 dy[4]를 선언하였다. 
	동,북,서,남으로 이동할 때 더해주어야 할 값을 dx[], dy[]에 저장해놓고, 
	바라보는 방향인 TD를 인덱스로 하여, 이동할 값을 알게 하였다.

이슈사항) 틀린 이유를 오해하다.
명령이 1번부터 M번인데, N으로 포문에 넣다 보니, 틀렸다고 채점 결과가 나왔다. 
그래서 남은 입력을 다 받아야 하는 것으로 오해?해서 실행해봤지만, 역시 틀렸다고 나와서, 
다른부분을 보았고, N을 M으로 고치니 맞았다,,
이로써, 주어진 입력을 다 받지 않고, 정답을 출력하고 프로그램을 종료해도 된다는 것을 알았다.
*/
