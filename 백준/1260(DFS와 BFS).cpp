#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
	int N, M, V;
	scanf("%d %d %d",&N,&M,&V);

	vector<vector<int> > v(N+1); //정점 : 1번~N번
	int a, b;
	for(int i=0 ; i<M ; i++)
	{
		scanf("%d %d",&a,&b);
		v[a].push_back(b);
		v[b].push_back(a);
	}

	//오름차순으로 정렬
	for(int i=1 ; i<=N ; i++)
		sort(v[i].begin(), v[i].end());

	//DFS
	int* visited = new int[N+1];
	for(int i=1 ; i<=N ; i++)
		visited[i] = 0;

	stack<int> s;
	s.push(V);
	visited[V] = 1;
	printf("%d ",V);
	while(!s.empty())
	{
		int x = s.top();
		int flag = 0; //인접한 정점 중 방문 안한 정점이 있으면 1로
		for(int i=0 ; i<v[x].size() ; i++)
		{
			int tx = v[x][i];
			if(visited[tx] == 0)
			{
				flag = 1;

				visited[tx] = 1;
				printf("%d ",tx);
				s.push(tx);
				break;
			}
		}
		if(flag == 0) //모든 인접 정점들을 방문했음 => stack에서 pop하여 돌아가기
		{
			s.pop();
		}
	}printf("\n");

	//BFS
	for(int i=1 ; i<=N ; i++)
		visited[i] = 0;

	queue<int> q;
	q.push(V);
	visited[V] = 1;
	printf("%d ",V);
	while(!q.empty())
	{
		int x = q.front();
		q.pop();

		for(int i=0 ; i<v[x].size() ; i++)
		{
			int tx = v[x][i];
			if(visited[tx] == 0) //아직 방문안했으면 방문하고 push
			{
				visited[tx] = 1;
				printf("%d ",tx);
				q.push(tx);
			}
		}
	}

	return 0;
}

/*
BFS는 많이 해봤었지만, DFS는 처음 해본 것이므로 생각을 많이 해보는 계기가 되었다.
우선 처음으로 동적 벡터 배열을 사용해 보았다.
정점번호-인접한 정점들로 구성된 자료구조를 생각해보았다.
1-2,3,4
2-1,4
3-1,4
4-1,2,3
이런 식으로 입력 받기 위해,
vector<vector<int> > v(N+1); //정점 : 1번~N번
로 N+1개의 벡터를 생성했다.
그리고 각 원소는 또 벡터이므로, int형 자료들을 여러 개 담을 수 있다.
입력을 받은 후, 오름차순으로 정렬하였고, DFS를 적용했다.

1. 인접한 정점 중 방문하지 않은 정점이 있으면 방문처리하고 push하고 break; 하였다.
2. 새로 방문한 정점에 대해서 1) 과정을 반복한다.
3. 만약 인접한 정점 중 방문하지 않은 정점이 없다면 pop하여 돌아간다.
*/
