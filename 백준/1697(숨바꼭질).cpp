#include <iostream>
#include <queue>

using namespace std;


int main(int argc, char** argv)
{
	int N, K;
	scanf("%d %d", &N, &K);

	int diff = K - N;
	if (diff < 0)
	{
		printf("%d\n", -diff);
	}
	else if (diff == 0)
	{
		printf("0\n");
	}
	else //diff > 0 => K > N (BFS)
	{
		int cnt = -1;
		queue<int> subin;
		subin.push(N);
		bool visited[100001] = { 0 };
		visited[N] = 1;

		while (!subin.empty())
		{
			cnt++;
			//printf("cnt : %d\n", cnt);
			int size = subin.size();

			for (int i = 0; i < size; i++)
			{
				int x = subin.front();
				subin.pop();
				//printf("%d\n", x);
				if (x == K) //동생을 찾음
				{
					printf("%d\n", cnt);
					return 0;
				}

				if (x - 1 >= 0 && visited[x - 1] == 0)
				{
					visited[x - 1] = 1;
					subin.push(x - 1);
				}
				if (x + 1 <= 100000 && visited[x + 1] == 0)
				{
					visited[x + 1] = 1;
					subin.push(x + 1);
				}
				if (x * 2 <= 100000 && visited[x * 2] == 0)
				{
					visited[x * 2] = 1;
					subin.push(x * 2);
				}	
			}
		}

	}

	//printf("실패\n");

	return 0;//Your program should return 0 on normal termination.
}

/*
우선 크게 수빈(N)이와 동생(K)좌표의 차(diff = K-N)로, 3가지 상황으로 나누었다.
1) 수빈 > 동생 (diff < 0)
수빈이는 -1씩 해가며 동생을 찾을 수 밖에 없으므로, 답은 –diff가 된다.

2) 수빈 == 동생 (diff == 0)
수빈이는 동생을 바로 찾게 되므로, 답은 0이 된다.

3) 수빈 < 동생 (diff > 0)
이 경우에 비로소 BFS를 실행하게 된다.
현재 좌표에서, 총 3가지(-1, +1, *2)를 수행하여, 범위에 들었을 때 && 아직 방문하지 않은 좌표이면, 큐에 push하여, BFS를 수행한다.

이슈사항) if문에서 && 할 때 순서
처음에는 시간초과가 나서 위의 3가지 경우로 나눈 것이었다. 하지만 그래도 시간초과가 났는데, 그 이유는
if (visited[x - 1] == 0 && x - 1 >= 0)
으로 해서, 인덱스 에러가 난 것이다. 
먼저 해당 인덱스가 범위에 있는지를 판단한 후, 그 인덱스를 사용하여 배열의 값을 얻어와야 한다. 따라서, 이를
if (x - 1 >= 0 && visited[x - 1] == 0)
로 순서를 바꾸어주어, 문제를 해결할 수 있었다.
*/
