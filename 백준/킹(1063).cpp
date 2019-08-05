#include <iostream>
#include <string>
using namespace std;

struct item
{
	int x, y;
};

int main(int argc, char** argv)
{
	string temp;
	int N;
	struct item King, Stone;
	
	cin >> temp;
	King.x = temp[0] - 'A'+1;
	King.y = temp[1] - '0';

	cin >> temp;
	Stone.x = temp[0] - 'A'+1;
	Stone.y = temp[1] - '0';

	scanf("%d", &N);

	//printf("%d %d\n%d %d\n%d", King.x, King.y, Stone.x, Stone.y, N);

	//킹의 방향을 입력받아 시뮬레이션한다.
	int tx, ty;
	int dir; //R, L, B, T, RT, LT, RB, LB
	int dx[8] = {1, -1, 0, 0, 1, -1, 1, -1};
	int dy[8] = {0, 0, -1, 1, 1, 1, -1, -1};
	for (int i = 0; i < N; i++)
	{
		cin >> temp;
		if (temp == "R") dir = 0;
		else if (temp == "L") dir = 1;
		else if (temp == "B") dir = 2;
		else if (temp == "T") dir = 3;
		else if (temp == "RT") dir = 4;
		else if (temp == "LT") dir = 5;
		else if (temp == "RB") dir = 6;
		else if (temp == "LB") dir = 7;
		
		tx = King.x + dx[dir];
		ty = King.y + dy[dir];
		if (tx<1 || tx>8 || ty<1 || ty>8) //킹이 체스판 밖으로 나가는 경우
		{
			//이동을 건너뛴다.
		}
		else if (tx==Stone.x && ty==Stone.y) //킹이 돌의 위치로 이동하는 경우
		{
			int sx = Stone.x + dx[dir];
			int sy = Stone.y + dy[dir];
			if (sx < 1 || sx>8 || sy < 1 || sy>8) //돌이 체스판 밖으로 나가는 경우
			{
				//이동을 건너뛴다.
			}
			else //아닌경우 둘 다 좌표 업데이트
			{
				King.x = tx;
				King.y = ty;
				Stone.x = sx;
				Stone.y = sy;
			}			
		}
		else //위의 2가지가 아니면 임시좌표를 좌표에 업데이트 한다.
		{
			King.x = tx;
			King.y = ty;
		}
	}

	printf("%c%d\n", King.x+'A'-1, King.y);
	printf("%c%d\n", Stone.x+'A'-1, Stone.y);

	return 0;//Your program should return 0 on normal termination.
}

/*
우선 디렉션을 8개의 배열로 값을 저장하여, 이동하게 하였다.
이동할 좌표를 temp에 저장해놓고, 이동할 수 있는지의 여부를 먼저 판단한 후, 
이동이 가능하다고 판단되면 이동하였고, 불가능하다고 판단되면 해당 이동명령을 건너뛰었다.
크게 3가지 경우로 생각하였다.

1) 킹이 체스판 밖으로 나가는 경우 => 이동을 건너뛴다.
2) 킹이 돌의 위치로 이동하는 경우 (돌도 킹과 같은 방향으로 이동하게 된다.)
   1) 돌이 체스판 밖으로 나가는 경우 => 이동을 건너뛴다.
   2) 아닌경우 둘 다(킹, 돌) 좌표 업데이트
3) 위의 1,2번 경우가 아닌 경우, 킹의 좌표를 업데이트
*/
