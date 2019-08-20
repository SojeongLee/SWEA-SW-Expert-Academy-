#include <iostream>
#include <queue>

using namespace std;

bool visited[100001];

int main(int argc, char** argv)
{
	int A, B, N, M;
	scanf("%d %d %d %d", &A, &B, &N, &M);

	int dx[6] = {1,-1,A,-A,B,-B};
	queue<int> q;
	q.push(N);
	visited[N] = 1;

	int cnt = -1;
	while (!q.empty())
	{
		cnt++;

		int size = q.size();
		for (int s = 0; s < size; s++)
		{
			int x = q.front();
			//printf("%d : ", x);
			q.pop();
			if (x == M)
			{
				printf("%d\n", cnt);
				return 0;
			}	
			//dx로 이동
			for (int dir = 0; dir < 6; dir++)
			{
				int tx = x + dx[dir];
				if (tx < 0 || tx>100000)
					continue;
				if (visited[tx] == 0)
				{
					//printf("%d, ", tx);
					visited[tx] = 1;
					q.push(tx);
				}
			}
			//*A, *B만큼 이동
			int tx = x * A;
			if (tx>100000) 
				continue;
			if (visited[tx] == 0)
			{
				//printf("%d, ", tx);
				visited[tx] = 1;
				q.push(tx);
			}

			tx = x * B;
			if (tx > 100000)
				continue;
			if (visited[tx] == 0)
			{
				//printf("%d, ", tx);
				visited[tx] = 1;
				q.push(tx);
			}//printf("\n");
		}
	}

	return 0;//Your program should return 0 on normal termination.
}

/*
1697(숨바꼭질) 문제와 유사하다.
int dx[6] = {1,-1,A,-A,B,-B}; 과
int tx = x * A;
tx = x * B;
를 이용해서, BFS로 +/-1, +/-A, +/-B, *A, *B 만큼씩 이동할 수 있도록 하였다.
*/
