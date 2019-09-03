#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d", &N, &M);

	vector<vector<int> > light(N + 1); //나보다 가벼운 것들
	vector<vector<int> > heavy(N + 1); //나보다 무거운 것들
	int h, l;
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d", &h, &l);
		light[h].push_back(l);
		heavy[l].push_back(h);
	}

	int ANS = 0; //답
	int CNT = N / 2 + 1; //CNT개 만큼 가볍거나 무거운 것이 있어야 중간이 될 가능성이 전혀 없게 되는 것
	//light
	for (int i = 1; i <= N; i++)
	{
		bool visited[100] = { 0 };
		queue<int> q;
		q.push(i);
		visited[i] = 1;

		int cnt = 0;
		while (!q.empty())
		{
			int x = q.front();
			q.pop();
			for (int k = 0; k < light[x].size(); k++)
			{
				int t = light[x][k];
				if (visited[t] == 0)
				{
					visited[t] = 1;
					q.push(t);
					cnt++;
				}
			}
		}
		if (CNT <= cnt)
		{
			//printf("구슬 : %d\n", i);
			ANS++;
		}
	}

	//heavy
	for (int i = 1; i <= N; i++)
	{
		bool visited[100] = { 0 };
		queue<int> q;
		q.push(i);
		visited[i] = 1;

		int cnt = 0;
		while (!q.empty())
		{
			int x = q.front();
			q.pop();
			for (int k = 0; k < heavy[x].size(); k++)
			{
				int t = heavy[x][k];
				if (visited[t] == 0)
				{
					visited[t] = 1;
					q.push(t);
					cnt++;
				}
			}
		}
		if (CNT <= cnt)
		{
			//printf("구슬 : %d\n", i);
			ANS++;
		}
	}

	printf("%d\n", ANS);

	return 0;
}

/*
알고리즘은 DFS로 분류되어있지만, BFS로 풀이하였다.
무게가 중간이 절대로 될 수 없으려면, 
나보다 무거운 구슬이 N/2+1개 이상 있거나, 또는 나보다 가벼운 구슬이 N/2+1개 이상 있으면 된다.

예를 들어, 구슬이 5개일 때, 중간은 3(=N/2+1)번째 이므로, 
나보다 무거운 구슬이 3개만(=이상) 있으면, 중간인 3번이 절대로 될 수 없다. (가벼운 구슬이 3개가 있어도 마찬가지이다.)
따라서, BFS로 나보다 무거운 구슬의 개수와 무거운 구슬의 개수를 구하고, 이 수가 N/2+1이상이면 카운트를 ++하여 답을 찾았다.
*/
