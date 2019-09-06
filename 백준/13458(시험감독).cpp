#include <iostream>

using namespace std;

int num[1000001];

int main(int argc, char** argv)
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &num[i]);
	}

	int B, C;
	scanf("%d %d", &B, &C);

	long long cnt = 0;
	for (int i = 0; i < N; i++)
	{
		num[i] -= B;
		cnt++;
		if (num[i] <= 0)
			continue;

		cnt += (num[i]/C + 1);
		if(num[i] % C == 0)
			cnt--;
	}

	printf("%ld\n", cnt);


	return 0;
}

/*
처음에는 for문으로 감독관의 수를 구하려고 했지만, 시간초과가 났다.
따라서, 수학문제처럼, 나누기로 계산하였다.

이슈사항) 정수 범위
시험장의 개수가 백만 개, 응시자의 수도 백만 명까지 가능하다. 
따라서 int가 아닌 long long 변수를 사용해야한다.
long long 범위) -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807
*/
