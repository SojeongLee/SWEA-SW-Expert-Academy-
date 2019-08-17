#include <iostream>
#include <queue>

using namespace std;

int visited[1000001];

int main(int argc, char** argv)
{
	int F, S, G, U, D;
	scanf("%d %d %d %d %d",&F,&S,&G,&U,&D);

	//엘레베이터로 도달이 불가능한 경우
	if(S > G && D == 0) //내려가야 하는데 D가 0인 경우
	{
		printf("use the stairs\n");
		return 0;
	}
	if(S < G && U == 0) //올라가야 하는데 U가 0인 경우
	{
		printf("use the stairs\n");
		return 0;
	}

	int cnt = 0;
	queue<int> q;
	q.push(S);
	visited[S] = 1;
	while(!q.empty())
	{
		int size = q.size();
		for(int s=0 ; s<size ; s++)
		{
			int x = q.front();
			q.pop();

			if(x == G)
			{
				printf("%d\n",cnt);
				return 0;
			}

			//UP
			int tx = x + U;
			if(tx <= F && visited[tx] == 0)
			{
				visited[tx] = 1;
				q.push(tx);
			}
			//DOWN
			tx = x - D;
			if(tx > 0 && visited[tx] == 0)
			{
				visited[tx] = 1;
				q.push(tx);
			}
		}
		cnt++;
	}

	printf("use the stairs\n");

	return 0;//Your program should return 0 on normal termination.
}

/*
우선 출력해야 할 값이 크게 2가지로 구분된다.
1) 눌러야 하는 버튼의 수의 최솟값을 출력
2) 만약, 엘리베이터로 이동할 수 없을 때는 "use the stairs"를 출력

1)은 최단거리를 구해야 하는 것이므로, BFS를 적용하면 된다.
이 때, 예외사항인 2)부터 처리하였다. 엘리베이터로 이동할 수 없는 경우는 크게 2가지가 있다.
if(S > G && D == 0) //내려가야 하는데 D가 0인 경우
if(S < G && U == 0) //올라가야 하는데 U가 0인 경우
이 두 가지 경우를 먼저 예외처리 한 후 1)을 BFS로 구했다.

이슈사항) 메모리 초과
BFS를 적용했을 때, 메모리 초과가 나는 경우는 항상, visited배열을 if문 안에 써주지 않아서 발생하는 것 같다.
처음에는
if(tx <= F)
로만 조건을 체크했는데, 방문을 안 했으면 해야 하는 것이므로,
if(tx <= F && visited[tx] == 0)
visited배열의 값이 0인지 추가하여, 메모리 초과 문제를 해결하였다.
*/
