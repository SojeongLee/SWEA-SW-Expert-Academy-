#include <iostream>

using namespace std;

int N;
int T[20];
int P[20];

int MAX;

void consult(int pay, int day)
{
	if (day > N /*|| day + T[day] > N+1*/)
	{
		if (MAX < pay)
			MAX = pay;
		return ;
	}
	else if (day + T[day] > N + 1) //분리해야!
	{
		consult(pay, day + 1);
	}
	else
	{
		consult(pay + P[day], day + T[day]);
		consult(pay, day + 1);
	}
}

int main(int argc, char** argv)
{	
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &T[i], &P[i]);
	}

	consult(0, 1);

	printf("%d\n", MAX);

	return 0;
}

/*
우선 로직을 3부분으로 생각하였다.
1) 해당 day에 일을 할 수 없는 경우 => 내일로 넘어간다!
2) 해당 day에 일을 할 수 있고 => 일을 하는 경우
3) 해당 day에 일을 할 수 있지만 => 일을 안 하는 경우

이렇게 3부분을 모두 검사해봐야 하는 것이므로, dfs 즉, 재귀를 이용하였다.
재귀의 종료 조건은 퇴사일을 넘어가는 경우이다.

이슈사항) 1번 로직
처음에는, 해당 day에 일을 할 수 없는 경우 바로 종료를 하여, 그 다음날 일을 할 수 있는 상황이 있는 경우, 틀린 결과를 도출했다.
따라서,
if (day > N /*|| day + T[day] > N+1*/)

else if (day + T[day] > N + 1) //분리해야!
로 if문을 분리하였다.
*/
