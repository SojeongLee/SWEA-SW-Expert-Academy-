#include <iostream>
#include <string>

using namespace std;

struct Ant
{
	char c;
	int dir; //1:왼쪽->오른쪽, -1:오른쪽->왼쪽
};

int main(int argc, char** argv)
{
	int N1, N2;
	scanf("%d %d", &N1, &N2);

	struct Ant* ants = new struct Ant[N1 + N2];
	string group1, group2;
	cin >> group1;
	cin >> group2;
	//첫번째 개미 그룹
	for (int i = 0 ; i<N1 ; i++)
	{
		ants[N1 - 1 - i].c = group1[i];
		ants[i].dir = 1;
	}
	//두번째 개미 그룹
	for (int i = N1; i < N1+N2; i++)
	{
		ants[i].c = group2[i - N1];
		ants[i].dir = -1;
	}

	int T;
	scanf("%d", &T);
	//T초동안 이동하기
	for (int i = 0; i < T; i++)
	{
		for (int k = 0; k < N1 + N2-1; k++)
		{
			//서로 교차하는 방향이면 => 점프한다(서로를 바꾼다.)
			if (ants[k].dir == 1 && ants[k + 1].dir == -1)
			{
				struct Ant temp = ants[k];
				ants[k] = ants[k + 1];
				ants[k + 1] = temp;

				k++;
			}
		}
	}

	for (int j = 0; j < N1 + N2; j++)
	{
		printf("%c", ants[j].c);
	}

	return 0;//Your program should return 0 on normal termination.
}

/*
개미 struct를 선언하여, 첫번째 개미그룹의 디렉션(왼쪽->오른쪽)으로는 1을, 
두번째 개미그룹의 디렉션(오른쪽->왼쪽)으로는 -1을 초기화하여 사용하였다.
그런 후 서로 교차하는 방향이면(왼쪽->오른쪽/왼쪽<-오른쪽) struct Ant temp 변수를 사용하여, 두 개미를 바꾸었다.
*/
