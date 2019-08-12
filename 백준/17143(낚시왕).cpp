#include <iostream>

using namespace std;

struct Shark
{
	int x, y; //위치
	int speed, dir, size; //속력, 이동방향, 크기
	int alive; //살아있으면1, 죽으면0 (낚시로 잡혔거나, 다른 상어에게 잡아먹힌 경우)
};

int main(int argc, char** argv)
{
	int R, C, M;
	scanf("%d %d %d",&R,&C,&M);

	struct Shark* shark = new struct Shark[M+1]; //상어 1번~M번
	int map[110][110] = {0};
	int tx, ty, ts, td, tz;
	for(int i=1 ; i<=M ; i++)
	{
		scanf("%d %d %d %d %d",&tx,&ty,&ts,&td,&tz);
		shark[i].x = tx;
		shark[i].y = ty;
		shark[i].speed = ts;
		shark[i].dir = td-1; //dx[4]배열에서 인덱스  0~3 사용하려구
		shark[i].size = tz;
		shark[i].alive = 1;
		map[tx][ty] = i;
	}

	int sum = 0; //잡은 상어들 크기 합
	int dx[4] = {-1,1,0,0}; //위, 아래, 오른쪽, 왼쪽 순서
	int dy[4] = {0,0,1,-1};
	for(int k=1 ; k<=C ; k++) //총 C번 낚시 -> 상어 이동
	{
		//낚시
		for(int i=1 ; i<=R ; i++)
		{
			if(map[i][k] != 0)
			{
				int num = map[i][k];
				sum += shark[num].size;
				shark[num].alive = 0;
				map[i][k] = 0;
				break;
			}
		}

		//상어 이동
		int modUD = R*2-2;
		int modRL = C*2-2;
		for(int n=1 ; n<=M ; n++)
		{
			if(shark[n].alive == 0)
				continue;

			map[shark[n].x][shark[n].y] = 0;
			int speed = shark[n].speed;
			int dir = shark[n].dir;
			if(dir == 0 || dir == 1) //위, 아래
			{
				speed %= modUD;
			}
			else //오른쪽, 왼쪽
			{
				speed %= modRL;
			}

			int mov = 0;
			while(mov < speed)
			{
				dir = shark[n].dir;
				tx = shark[n].x + dx[dir];
				ty = shark[n].y + dy[dir];
				
				switch(dir)
				{
				case 0: //위
					if(tx < 1) shark[n].dir = 1;
					else
					{
						mov++;
						shark[n].x = tx;
						shark[n].y = ty;
					}
					break;
				case 1: //아래
					if(tx > R) shark[n].dir = 0;
					else
					{
						mov++;
						shark[n].x = tx;
						shark[n].y = ty;
					}
					break;
				case 2: //오른쪽
					if(ty > C) shark[n].dir = 3;
					else
					{
						mov++;
						shark[n].x = tx;
						shark[n].y = ty;
					}
					break;
				case 3: //왼쪽
					if(ty < 1) shark[n].dir = 2;
					else
					{
						mov++;
						shark[n].x = tx;
						shark[n].y = ty;
					}
					break;
				}
			}
			//printf("%d번 상어 위치 : %d, %d\n",n,shark[n].x, shark[n].y);
		}
		
		//상어들끼리 잡아먹기
		for(int n=1 ; n<=M ; n++)
		{
			if(shark[n].alive == 0)
				continue;

			int x = shark[n].x;
			int y = shark[n].y;
			if(map[x][y] == 0)
			{
				map[x][y] = n;
			}
			else //다른 상어가 있는 경우 => 크기 비교해서 큰게 살아남는다
			{
				int other = map[x][y];
				int other_size = shark[other].size;
				if(other_size < shark[n].size) //잡아먹는다.
				{
					shark[other].alive = 0;
					map[x][y] = n;
				}
				else //잡아먹힌다.
				{
					shark[n].alive = 0;
				}
			}
		}

		/*for(int i=1 ; i<=R ; i++)
		{
			for(int k=1 ; k<=C ; k++)
			{
				printf("%2d ",map[i][k]);
			}printf("\n");
		}printf("%d\n",sum);*/
	}

	printf("%d\n",sum);


	return 0;//Your program should return 0 on normal termination.
}

/*
우선 상어 struct를 선언하였다. 
위치, 속력, 이동방향, 크기 외에도 alive라는 변수를 추가하여, 상어가 살아있으면1, 죽으면0으로 설정하여, 로직을 구성하였다.

크게 3단계로 구성하였다.
1) 낚시를 한다.
이때 map[][] 이차원 배열을 해당 col의 위에서부터 아래로 내려간다. 
상어의 번호는 1부터 N까지 배열에 적어놓았다. 
0이 아니면 상어를 잡은 것이므로, sum의 해당 상어의 크기를 더해주고, 해당 상어의 alive를 0으로 만든 후 break;로 낚시를 마친다.

2) 상어가 이동한다.
이때 처음부터 그냥 시뮬레이션을 하면 (이슈사항)시간초과가 나왔다. 따라서
int modUD = R*2-2;
int modRL = C*2-2;
를 선언하여, speed 변수에 %= mod; 로 시뮬레이션 할 이동횟수를 줄여줬다.
길이*2-2가 포인트인데, 길이가 4일때는 제자리에 돌아오려면 이동횟수 6이 필요하고, 
길이가 5일때는 이동횟수 8이, 6일때는 10이, 7일때는 12,,,가 필요하다는 규칙에서 얻었다.

3) 상어들끼리 잡아먹는다.
상어들의 새로운 좌표를 다 구했으면, map[][] 에 상어를 한 마리씩 배치시킨다. 
이 때 이미 해당 칸에 다른 상어가 있는 경우는 크기를 비교하여 큰 것이 살아남도록 하였다. 
*/
