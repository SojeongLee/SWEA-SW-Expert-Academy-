#include <iostream>
#include <string>

using namespace std;

string topni[4]; //톱니바퀴0번~3번 => 4개, 0~7(12시~)

void left(int num) //반시계방향으로 한칸씩
{
	char temp = topni[num][0];
	for(int i=1 ; i<8 ; i++)
	{
		topni[num][i-1] = topni[num][i];
	}
	topni[num][7] = temp;
}

void right(int num) //시계방향으로 한칸씩
{
	char temp = topni[num][7];
	for(int i=6 ; i>=0 ; i--) //이부분,, 덮어씌우는거 잘 생각하기..!!
	{
		topni[num][i+1] = topni[num][i];
	}
	topni[num][0] = temp;
}

int main(int argc, char** argv)
{
	for(int i=0 ; i<4 ; i++)
	{
			cin >> topni[i];
	}

	int K;
	scanf("%d",&K);

	for(int i=0 ; i<K ; i++)
	{
		int num, dir;
		scanf("%d %d",&num,&dir);

		int flag1=0, flag2=0, flag3=0; //서로 다른 극이면 1로 세팅 => 회전해야
		if(topni[0][2] != topni[1][6]) flag1 = 1;
		if(topni[1][2] != topni[2][6]) flag2 = 1;
		if(topni[2][2] != topni[3][6]) flag3 = 1;
		
		switch(num-1)
		{
		case 0: //0번을 돌림
			if(dir == -1) //0번이 반시계(left)로 돌아감
			{
				left(0);
				if(flag1) //1번도 돌아가야함
				{
					right(1); //1번은 시계로 돌아감
					if(flag2) //2번도 돌아가야함
					{
						left(2); //2번은 반시계로 돌아감
						if(flag3) //3번도 돌아가야함
							right(3); //3번은 시계로 돌아감
					}
				}
			}
			else if(dir == 1) //0번이 시계(right)로 돌아감
			{
				right(0);
				if(flag1)
				{
					left(1);
					if(flag2)
					{
						right(2);
						if(flag3)
							left(3);
					}
				}
			}
			break;
		case 1: //1번을 돌림
			if(dir == -1) //반시계
			{
				left(1);
				if(flag1)
					right(0);
				if(flag2)
				{
					right(2);
					if(flag3)
						left(3);
				}
			}
			else if(dir == 1) //시계
			{
				right(1);
				if(flag1)
					left(0);
				if(flag2)
				{
					left(2);
					if(flag3)
						right(3);
				}
			}
			break;
		case 2: //2번을 돌림
			if(dir == -1) //반시계
			{
				left(2);
				if(flag2)
				{
					right(1);
					if(flag1)
						left(0);
				}
				if(flag3)
					right(3);
			}
			else if(dir == 1) //시계
			{
				right(2);
				if(flag2)
				{
					left(1);
					if(flag1)
						right(0);
				}
				if(flag3)
					left(3);
			}
			break;
		case 3: //3번을 돌림
			if(dir == -1) //반시계
			{
				left(3);
				if(flag3)
				{
					right(2);
					if(flag2)
					{
						left(1);
						if(flag1)
							right(0);
					}
				}
			}
			else if(dir == 1) //시계
			{
				right(3);
				if(flag3)
				{
					left(2);
					if(flag2)
					{
						right(1);
						if(flag1)
							left(0);
					}
				}
			}
			break;
			//default: printf("오류");
		}
		
	}

	int score = 0;
	if(topni[0][0] == '1') score += 1;
	if(topni[1][0] == '1') score += 2;
	if(topni[2][0] == '1') score += 4;
	if(topni[3][0] == '1') score += 8;

	printf("%d\n",score);


	return 0;//Your program should return 0 on normal termination.
}

/*
우선 flag를 3개를 두어, 서로 다른 극이면 1로 세팅했고, 1일 때, 회전해야 하는 것이다.
그 후로는, left함수와 right함수를 만들었는데, left함수는 해당 톱니바퀴를 반시계방향으로 한 칸씩 돌리는 것이고, 
right함수는 시계방향으로 한 칸씩 돌리는 것이다.

그 다음으로는 switch case 문으로, 몇 번 톱니바퀴를 돌리는 것인지 시뮬레이션 하였다.
예를 들어, 0번 톱니바퀴를 반시계 방향으로 돌려야 한다면 left함수를 호출한다.
그 다음으로는 flag1을 확인하여, 1번 톱니바퀴도 돌려야 하는지 확인한다. 
만약 flag1이 1이라서 1번 톱니바퀴가 돌아가야 한다면, 0번 톱니바퀴가 반시계 방향으로 돌리는 것이었기에, 
1번 톱니바퀴는 시계방향으로 돌려야 하므로 right함수를 호출한다.
위와 마찬가지로, 그 다음으로는 flag2로,, flag3으로 순차적으로 (중복 if로) 실행하면 된다.
*/
