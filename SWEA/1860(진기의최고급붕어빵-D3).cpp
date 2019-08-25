#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{
	int T;
	scanf("%d",&T);
	for(int test_case = 1 ; test_case <= T ; test_case++)
	{
		int N, M, K;
		scanf("%d %d %d",&N,&M,&K);

		vector<int> sec;
		int in;
		for(int i=0 ; i<N ; i++)
		{
			scanf("%d",&in);
			sec.push_back(in);
		}
		sort(sec.begin(), sec.end());

		int cnt = 0; //0번부터 서빙한다. (K명 씩)
		int time = 0; //흐른 시간
		while(1)
		{
			time += M; //K개가 만들어짐
			for(int i=cnt ; i<cnt+K ; i++)
			{
				if(i >= N) //서빙 끝
				{
					printf("#%d Possible\n",test_case);
					goto A;
				}
				if(time > sec[i]) //서빙할 수 없음
				{
					printf("#%d Impossible\n",test_case);
					goto A;
				}
			}
			cnt += K;
		}
A: ;
	}

	return 0;//Your program should return 0 on normal termination.
}

/*
우선 손님들 중에 먼저 도착하는 손님부터 붕어빵을 제공해야 하므로,
손님들의 도착 시간을 가지는 sec 벡터를 sort함수로 오름차순 정렬하였다.
그 후, time 변수에 M초를 더한 후, K개를 서빙하였다. 
이 때, time 변수의 값 보다 손님의 도착시간이 작은 경우, 서빙을 할 수 없게 되어 Impossible을 출력하면 된다.  
*/
