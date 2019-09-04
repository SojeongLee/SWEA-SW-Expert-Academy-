#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


int main(int argc, char** argv)
{
	int N;
	scanf("%d", &N);

	int map[20][20];
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < N; k++)
			scanf("%d", &map[i][k]);
	}

	int C = N / 2; //각 팀의 팀원 수
	vector<int> ind;
	for (int i = 1; i <= C; i++)
		ind.push_back(1);
	for (int i = 1; i <= C; i++)
		ind.push_back(2);

	int DIFF = 2000;
	do
	{
		vector<int> s_team;
		vector<int> l_team;
		for (int i = 0; i < N; i++)
		{
			if (ind[i] == 1) //스타트팀
				s_team.push_back(i);
			else //링크팀
				l_team.push_back(i);
		}
		//스타트팀 능력치 계산
		int s_power = 0;
		for (int i = 0; i < C - 1; i++)
		{
			int a = s_team[i];
			for (int k = i + 1; k < C; k++)
			{
				int b = s_team[k];
				s_power += map[a][b];
				s_power += map[b][a];
			}
		}
		//링크팀 능력치 계산
		int l_power = 0;
		for (int i = 0; i < C - 1; i++)
		{
			int a = l_team[i];
			for (int k = i + 1; k < C; k++)
			{
				int b = l_team[k];
				l_power += map[a][b];
				l_power += map[b][a];
			}
		}
		int diff = abs(s_power - l_power);
		//printf("s : %d, l : %d => diff : %d\n", s_power, l_power, diff);
		if (DIFF > diff)
			DIFF = diff;

	} while (next_permutation(ind.begin(), ind.end()));

	printf("%d\n", DIFF);

	return 0;
}

/*
넥스트퍼뮤테이션 함수로, N개 중 절반인, N/2개를 고르는 조합을 만들었다.
절반은 스타트팀, 나머지 절반은 링크팀이 되며, 각 팀의 능력치를 구한 후, 차이를 계산했다. 
이 차이가 MIN일 경우 업데이트했고, 최종 MIN값이 정답이 된다.
*/
