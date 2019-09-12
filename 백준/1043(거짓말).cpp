#include <iostream>
#include <queue>

using namespace std;


int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d",&N,&M);

	int T;
	int truth[51];
	scanf("%d",&T);
	for(int i=0 ; i<T ; i++)
		scanf("%d",&truth[i]);

	int graph[51][51] = {0};
	int party[51][51];
	for(int i=0 ; i<M ; i++)
	{
		int n;
		scanf("%d",&n);
		party[i][0] = n;

		for(int k=1 ; k<=n ; k++)
			scanf("%d",&party[i][k]);

		for(int a=1 ; a<=n-1 ; a++)
		{
			for(int b=a+1 ; b<=n ; b++)
			{
				int x = party[i][a];
				int y = party[i][b];
				graph[x][y] = 1;
				graph[y][x] = 1;
			}
		}
	}

	int visited[51] = {0};
	for(int i=0 ; i<T ; i++) //진실을 아는 사람에 대해서 BFS
	{
		queue<int> q;
		q.push(truth[i]);
		visited[truth[i]] = 1;

		while(!q.empty())
		{
			int x = q.front();
			q.pop();

			for(int k=1 ; k<=N ; k++)
			{
				if(visited[k] == 0 && graph[x][k] == 1)
				{
					visited[k] = 1;
					q.push(k);
				}
			}

		}
	}

	//거짓말 할 수 있는 party 수 구하기
	int cnt = 0;
	for(int i=0 ; i<M ; i++)
	{
		int n = party[i][0];
		for(int k=1 ; k<=n ; k++)
		{
			if(visited[party[i][k]] == 1)
				goto A;
		}
		cnt++;
		A: ;
	}

	printf("%d\n",cnt);

	return 0;
}

/*
BFS로 풀었다.
이유는, 진실을 알고 있는 사람이 한 명이라도 해당 파티에 있으면, 지민이는 해당 파티에서 진실을 말해야 한다.
그러면, 해당 파티에 1, 2, 3이 있고, 1만 진실을 아는 사람이었어도, 2, 3도 결국 진실을 알게 된다.

따라서, 진실을 아는 사람에 대해서 BFS를 실행한다. 
즉, 진실을 아는 사람과 같은 파티에 참여하는 모든 사람에 대해서 조사하는 것이다. 
이 사람들을 visited 배열에 1로 체크하고, 각 파티마다 visited값을 1로 가지는 사람이 한 명이라도 있는지 조사한다.
1명이라도 있으면 해당파티에서 거짓말을 할 수 없고, 아무도 없다면 거짓말을 할 수 있게 되므로, 카운트한다.
*/
