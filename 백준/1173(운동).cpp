#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	int N, m, M, T, R;
	scanf("%d %d %d %d %d", &N, &m, &M, &T, &R);

	int min = 0; //운동 끝내는데 걸리는 시간
	int cnt = 0; //운동 횟수 (==N 이 되면 break;)
	int pulse = m; //초기 맥박은 m

	//운동을 끝낼 수 없는 경우 -1 출력
	int diff = M - m;
	if (diff < T)
	{
		printf("-1");
		return 0;
	}

	int temp;
	while (1)
	{
		temp = pulse + T;
		if (temp <= M) //운동을 할 수 있는 경우
		{
			pulse = temp;
			cnt++;
		}
		else //휴식을 취해야 함
		{
			pulse -= R;
			if (pulse < m)
			{
				pulse = m;
			}
		}
		min++;

		if (cnt == N) //운동 끝!
			break;
	}

	printf("%d\n", min);

	return 0;//Your program should return 0 on normal termination.
}

/*
이슈사항) 운동을 끝낼 수 없는 경우가 있다.
문제자체는 쉽지만, 한 가지 생각해야 할 점이 바로, 운동을 끝낼 수 없는 경우에 대해서라고 생각했다.
M(최대맥박)과 m(최소맥박)의 차이보다 운동을 했을 때의 T(맥박 증가수)가 더 크다면, 
운동을 시작할 수 없으므로, 이 경우 -1을 출력하고 프로그램을 종료하도록 하였다. 
*/
