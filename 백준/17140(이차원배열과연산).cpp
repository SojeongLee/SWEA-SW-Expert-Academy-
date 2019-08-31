#include <iostream>

using namespace std;

int map[101][101];

int main(int argc, char** argv)
{	
	int r,c,k;
	scanf("%d %d %d",&r,&c,&k);
	
	for(int i=1 ; i<=3 ; i++)
	{
		for(int k=1 ; k<=3 ; k++)
			scanf("%d",&map[i][k]);
	}

	int R = 3;
	int C = 3;
	int time;
	for(time=0 ; time<=100 ; time++)
	{
		//printf("time : %d, R = %d, C = %d\n",time,R,C);
		if(map[r][c] == k)
		{
			printf("%d\n",time);
			return 0;
		}

		//행 연산
		if(R >= C)
		{
			for(int i=1 ; i<=R ; i++)
			{
				int number[101] = {0}; //1부터 100까지 자연수가 몇 개가 있는지 카운트
				for(int k=1 ; k<=C ; k++)
				{
					number[map[i][k]]++;
					map[i][k] = 0;
				}
				int a=1;
				int min, ind;
				while(1) //정렬 (수 - 횟수)
				{
					min = 100;
					ind = 0;
					for(int k=1 ; k<=100 ; k++)
					{
						if(min > number[k] && number[k] > 0)
						{
							min = number[k];
							ind = k;
						}
					}
					if(ind == 0)
						break;

					number[ind] = 0;
					map[i][a] = ind;
					map[i][a+1] = min;
					a += 2;
				}
				a -= 1;
				if(C < a)
					C = a;
			}
		}

		//열 연산
		else
		{
			for(int k=1 ; k<=C ; k++)
			{
				int number[101] = {0}; //1부터 100까지 자연수가 몇 개가 있는지 카운트
				for(int i=1 ; i<=R ; i++)
				{
					number[map[i][k]]++;
					map[i][k] = 0;
				}
				int a=1;
				int min, ind;
				while(1) //정렬 (수 - 횟수)
				{
					min = 100;
					ind = 0;
					for(int i=1 ; i<=100 ; i++)
					{
						if(min > number[i] && number[i] > 0)
						{
							min = number[i];
							ind = i;
						}
					}
					if(ind == 0)
						break;

					number[ind] = 0;
					map[a][k] = ind;
					map[a+1][k] = min;
					a += 2;
				}
				a -= 1;
				if(R < a)
					R = a;
			}
		}

		/*for(int i=1 ; i<=R ; i++)
		{
			for(int k=1 ; k<=C ; k++)
				printf("%d ",map[i][k]);
			printf("\n");
		}printf("\n");*/
	}
	
	printf("-1\n");


	return 0;
}

/*
크게 2단계로 풀었다.
1) [r][c]의 값이 k인지 확인한다. => k이면 종료 (|| 100번 초과로 검사하면 종료)
2) R과 C의 값을 비교하여, 행 연산 or 열 연산을 수행한다.

연산을 수행하는 과정에서, 크게 두 가지 포인트가 있다.
첫 번째로는, R과 C의 값이 늘어나거나 줄어들 수도 있다는 점이다.
처음에는 줄어드는 점을 생각을 못해서 틀렸었다. (3 3 3 => 3 3 이 된다.)

두 번째로는, 줄어드는 경우, 그 이후의 값은 0으로 세팅해줘야 한다는 점이다.
값이 남아있으면, 이후 턴에서 잘못된 계산을 하기 때문이다.

연산은 간단한 아이디어로, 
int number[101] = {0}; //1부터 100까지 자연수가 몇 개가 있는지 카운트
배열에 카운트를 한 후, 가장 MIN 카운트를 가진 것부터, 수 – 횟수 순으로 배열에 저장하였다.
*/
