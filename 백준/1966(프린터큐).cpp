#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
	int test_case;
	scanf("%d", &test_case);

	for (int T = 0; T < test_case; T++)
	{
		int N, M;
		int doc[100] = { 0 };
		int score[10] = { 0 }; //[1]~[9]까지 중요도를 카운트

		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &doc[i]);
			score[doc[i]]++;
		}

		//우선 max 중요도를 찾는다,, 
		int point = 0;
		int max = 0;
		for (int i = 0; i < N; i++)
		{
			if (max < doc[i])
			{
				max = doc[i];
				if (max == 9)
					break; //중요도 최대가 9이므로
			}
		}

		//시작 point를 설정해야 한다.
		for (int i = 0; i < N; i++)
		{
			if (doc[i] == max)
			{
				point = i;
				break;
			}
		}
		
		//중요도를 max부터 실행해나간다,,
		int cnt = 0; //해당 문서가 몇번째로 인쇄되는지 카운트
		while (1)
		{
			if (score[max] != 0)
			{
				if (doc[point] == max)
				{
					cnt++;
					score[max]--;
					if (point == M)
						break;
				}

				point = (point+1) % N;
			}
			else
			{
				max--; //해당 중요도의 문서가 더이상 없으면 다음 순번으로 넘어감,,
				if (max == 0) //중요도가 0인것은 없으므로 0이되면 break;
					break;
			}

		}
		printf("%d\n", cnt);
	}


	return 0;//Your program should return 0 on normal termination.
}


/*
배열을 사용하여, 원형큐와 같은 구조인 원형 배열로 생각하여 풀었다.
논리구조를 크게 4단계로 생각해보았다.

1) 입력을 받을 때, score[10]라는 배열에 해당 중요도를 카운트 한다. 
   (예시처럼, 중요도가 1 1 9 1 1 1 이면, score[1] = 5, score[9] = 1 이 된다.
2) 그 다음으로는 max 중요도를 찾는다. (9일 수도, 8일 수도,,,)
3) 시작 point를 설정한다. doc[] 배열 0번부터 시작하여, 처음으로 max 중요도가 나타나는 인덱스가 시작 point가 된다.
4) 이제 본격적으로 해당 문서가 몇번째로 인쇄되는지 cnt에 카운트를 한다. 
   이때 해당 중요도를 미리 카운트 해놨으므로 이를 이용한다. 
   (예를 들어, 중요도 9가 1개이면, 시작point부터 중요도가 9인 인덱스를 찾아가고, 찾았으면 score[max]--;한다. 
   그다음 해당 중요도에 해당하는 문서수가 0이되면 max--;하여 중요도를 9, 8, 7, 6, ... , 2, 1 순으로 한다. 
   이때 point == M이면 해당 문서를 찾은 것이므로 break;를 하여 while 무한루프를 빠져나가도록 하였다. 

이슈사항) point++ vs point+1 
문서를 인덱스 0번부터 N-1번까지 찾고, 다시 0번부터 시작해야 하므로, 원형 배열 구조로 해야 한다. 
이때 point = (point+1) % N; 이 되어야 한다. (point++) % N 으로 처음에는 했었는데, 결과값이 안맞았다. 
양변에 point가 둘 다 있는 경우는 안전하게 point+1로 해야 할 것이다.
*/
