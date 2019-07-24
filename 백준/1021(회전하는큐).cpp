#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
	int N, M; //N:큐의 크기, M:뽑아해려고 하는 수의 개수
	int num[50] = { 0 }; //뽑아내려고 하는 수의 위치

	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &num[i]);
	}

	int queue[50]; //1,2,3, ... ,M까지 순서대로 넣어준다.
	for (int i = 0; i < N; i++)
	{
		queue[i] = i + 1;
	}

	int min_dis = 0; //2,3번 연산의 최솟값
	int cnt = 0; //현재 뽑아낸 개수
	int index = 0; //뽑아내려고 하는 수의 인덱스
	int tN = N; //남은 개수
	while (cnt != M) //M개를 뽑아낼 때까지 수행
	{
		for (int j = 0; j < tN; j++) //뽑아내려고 하는 수의 인덱스를 찾는다.
		{
			if (queue[j] == num[cnt])
			{
				index = j; //printf("index = %d, ", index);
			}
		}
		//left와 right에 있는 원소의 수를 계산
		int left = index;
		int right = tN-1 - index; //printf("left = %d, right = %d, ", left, right);

		//해당 수를 뽑고, 나머지를 temp[]에 옮긴다..
		cnt++;

		int temp[50];
		int m = 0;
		if (left <= right) 
		{
			min_dis += left;
		}
		else 
		{
			min_dis += (right + 1); //해당 원소도 옮겨야 하므로 +1을 해준다.
		}
		for (int k = index + 1; k < tN; k++) //인덱스의 오른쪽을 먼저 옮긴다.
		{
			temp[m] = queue[k];
			m++;
		}
		for (int k = 0; k < index; k++) //나머지 왼쪽도 옮긴다.
		{
			temp[m] = queue[k];
			m++;
		}

		tN--;

		for (int t = 0; t < tN; t++)
		{
			queue[t] = temp[t];
		}
		//printf("cnt = %d, tN = %d, min_dis = %d\n", cnt, tN, min_dis);
	}


	printf("%d\n", min_dis);


	return 0;//Your program should return 0 on normal termination.
}

/*
우선 큐의 크기 N이 최대 50이므로, 배열을 사용하기로 하였다.
논리구조는 크게 3단계로 생각하였다.

1) 우선 뽑아내려고 하는 수가 위치한 인덱스를 알아야 한다.
2) 해당 인덱스를 알았으면, 해당 인덱스의 왼쪽의 원소의 수와, 오른쪽 원소의 수의 개수를 비교해야 한다. 
   더 적은 쪽을 옮겨야 하기 때문이다.
3) 2번에서 더 적은 쪽을 옮겨야 한다고 하긴 했지만, temp 배열에는 항상, 
   해당 인덱스의 오른쪽을 옮기고 이어서 왼쪽을 옮긴다. 
   (이유는 항상 첫 번째 위치한 원소만 뽑아낼 수 있다는 문제의 조건 때문)
+) 문제에서 구해야 하는 최소 이동거리(min_dis)는 2)에서 계산해주면 된다.

이슈사항) 배열의 인덱스는 0부터 시작!
//left와 right에 있는 원소의 수를 계산
int left = index;
int right = tN-1 - index;
이 부분에서 처음에는 right = tN – index;로 하여 결과가 제대로 나오지 않았다. 
배열의 인덱스는 0부터 시작하므로 마지막 원소는 tN-1이 되므로, 
tN-1에서 index를 빼야, 인덱스 오른쪽에 있는 원소의 개수가 된다.
*/
