#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	int N, L;
	scanf("%d %d",&N, &L);

	int meter = 0; 
	int cnt = 0; //몇 초
	for(int i=0 ; i<N ; i++)
	{
		int D, R, G;
		scanf("%d %d %d", &D, &R, &G);

		while(meter<D)
		{
			meter++;
			cnt++;
		}
		//신호등이 있음,, 기다려야하는 시간 구하기
		int plus = 0;
		int x = 0;
		int y = -1;
		while(1)
		{
			if((R+G)*x <= cnt && cnt < (R+G)*x+R) //빨간불
			{
				plus = (R+G)*x+R - cnt;
				break;
			}
			else if((R+G)*x+R <= cnt && cnt < (R+G)*(x+1)) //초록불
			{
				break;
			}
			else
			{
				x++;
			}
		}
		cnt += plus;
	}

	while(meter<L)
	{
		meter++;
		cnt++;
	}

	printf("%d\n",cnt);


	return 0;//Your program should return 0 on normal termination.
}


/*
우선 meter와 cnt변수를 0으로 초기화하고 ++해가며 meter가 L까지 도달했을 때의 cnt를 출력하고자 하였다.
cnt가 특정 meter에 도달했을 때, 신호등이 있는 경우, 
빨간불의 시간영역에 속하는지, 초록불의 시간영역에 속하는지를 구하는 것이 가장 중요한 포인트이다.
빨간불의 시간영역에 속한다면, 기다려야하는 시간을 plus 변수에 저장하여 cnt에 더해주도록 하였다. 
초록불의 시간영역에 속한다면, 기다려야할 필요가 없다. 

이슈사항) 신호등의 색이 지속되는 시간?
빨간불의 시간영역과 초록불의 시간영역을 구했을 때, 처음에는 (R=5,G=5인 경우)
빨간불 : 1~5, 11~15,,,
초록불 : 6~10, 16~20,,, 으로 구했다. 하지만, 0초부터 시작하므로
빨간불 : 0~4, 10~14,,,
초록불 : 5~9, 15~19,,, 로 해야 맞는 것이다.
예를 들어, 위의 경우에, 10초에 신호등을 만났다면, 빨간불이 켜있는 것이다. 따라서 5초를 기다려야 한다. 
하지만 처음에 한 식으로 하면, 10초가 초록불의 시간영역에 있어서, 기다리지 않고 지나가게 되어, 틀린 결과를 낳았다.
*/
