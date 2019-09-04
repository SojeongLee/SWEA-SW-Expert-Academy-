#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
	int N;
	scanf("%d", &N);

	int num[12];
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &num[i]);
	}

	int op[4]; //+, -, *, /
	vector<int> ind;
	for (int i = 0; i < 4; i++)
	{
		scanf("%d", &op[i]);
		for (int k = 0; k < op[i]; k++)
			ind.push_back(i);
	}

	int MAX = -1000000000;
	int MIN = 1000000000;
	do
	{
		int result = num[0];
		for (int i = 0; i < N - 1; i++)
		{
			switch (ind[i])
			{
			case 0: result += num[i + 1];
				break;
			case 1: result -= num[i + 1];
				break;
			case 2: result *= num[i + 1];
				break;
			case 3: result /= num[i + 1];
				break;
			}
		}
		if (MAX < result) MAX = result;
		if (MIN > result) MIN = result;

	} while (next_permutation(ind.begin(), ind.end()));
	
	printf("%d\n%d\n", MAX, MIN);


	return 0;
}

/*
넥스트퍼뮤테이션 함수를 사용하여, 연산자들을 순열로 구성하였다.
예를 들어, 1 2 3 1 이 주어진다면, +는 0번(0), -는 2번(1,2), *는 3번(3,4,5), /는 1번(6) 사용해야 한다.
벡터에 0,1,2,3,4,5,6를 넣고, 이를 순열로 돌린다. 처음에는 + - - * * * / 가 연산되고,
그 다음에 순열은 0,1,2,3,4,6,5가 되고, 연산 순서는 + - - * * / *가 된다.
모든 순열이 끝나면 do-while문은 끝나게 되고, 연산 과정에서 MAX와 MIN값을 업데이트해나간다.
*/
