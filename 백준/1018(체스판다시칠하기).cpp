#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d ",&N,&M);

	string board[50];
	for(int i=0 ; i<N ; i++)
	{
		cin >> board[i];
	}

	int X = M - 8; //열에 더해질 DIFF
	int Y = N - 8; //행에 더해질 DIFF
	int min = 50;
	for(int s=0 ; s<=Y ; s++)
	{
		for(int t=0 ; t<=X ; t++)
		{
			int cnt1 = 0;
			int cnt2 = 0;
			for(int i=s ; i<s+8 ; i++)
			{
				for(int k=t ; k<t+8 ; k++)
				{
					//cnt1 ; 왼쪽 위 코너가 흰색인 것(다음차례엔 검정색 / 흰색 / 검정색,,,)
					//cnt2 ; 왼쪽 위 코너가 검정색인 것(다음차례엔 흰색 / 검정색 / 흰색,,,)
					if((i+k)%2 == 0)
					{
						if(board[i][k] == 'B') cnt1++;
						else cnt2++;
					}
					else
					{
						if(board[i][k] == 'W') cnt1++;
						else cnt2++;
					}
				}
			}
			if(min > cnt1) min = cnt1; //printf("cnt1 = %d\n",cnt1);
			if(min > cnt2) min = cnt2; //printf("cnt2 = %d\n",cnt2);
		}
	}

	
	printf("%d\n",min);


	return 0;//Your program should return 0 on normal termination.
}


/*
크게 2단계로 생각하였다.

1) 우선 몇 개의 8by8 체스판을 확인해야 하는지 계산해야 했다.
int X = M - 8; //열에 더해질 DIFF
int Y = N - 8; //행에 더해질 DIFF
예를 들어, 8by8이면 X와 Y가 모두 0이기 때문에, 더해질 것이 없고, 즉, 딱 한판의 체스판이 보드에서 나오는 것이다.
예제2에서와 같이 13by10이면 X가 5, Y가 2이기 때문에 0~5 * 0~2 = 6 * 3 = 18개의 체스판이 보드에 존재하게 된다.

2) 그 다음으로는 한 판의 체스판을 모두 하나의 원소씩 화이트인지 블랙인지 검사해야 하는데, 이 때 두 번을 훑어야 한다. 
왜냐하면 왼쪽모서리가 화이트인 경우와 블랙인 경우, 두 가지가 존재하기 때문이다.
//cnt1 ; 왼쪽 위 코너가 흰색인 것(다음차례엔 검정색 / 흰색 / 검정색,,,)
//cnt2 ; 왼쪽 위 코너가 검정색인 것(다음차례엔 흰색 / 검정색 / 흰색,,,)

체스판의 특징은 배열의 각 원소의 인덱스 i+k 값이 짝수인 곳은 모두 같은 색이고, 
홀수인 곳은 또 다른색으로 같은 색이어야, 바둑모양으로 색이 칠해지는 것이다.

이슈사항) for문의 조건식
for(int s=0 ; s<=Y ; s++)
{
	for(int t=0 ; t<=X ; t++)
	{
for문의 조건식에 등호를 넣어줘야, 8by8일 때 딱 한번 실행하게 된다. 
처음에는 등호를 넣어주지 않아, for문이 아예 실행되지 않아 당황했다.
*/
