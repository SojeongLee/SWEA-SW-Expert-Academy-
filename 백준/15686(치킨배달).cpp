#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>

using namespace std;


int main(int argc, char** argv)
{
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<pair<int, int> > home;
	vector<pair<int, int> > chi;
	int temp;
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < N; k++)
		{
			scanf("%d", &temp);
			if (temp == 1)
				home.push_back(pair<int, int>(i, k));
			else if (temp == 2)
				chi.push_back(pair<int, int>(i, k));
		}
	}
	
	//집-치킨 거리 구하기
	int home_cnt = home.size();
	int chi_cnt = chi.size();
	int map[101][51]; //[home][chi] : 치킨거리
	int dist;
	for (int i = 0; i < home.size(); i++)
	{
		for (int k = 0; k < chi.size(); k++)
		{
			dist = abs(home[i].first - chi[k].first) + abs(home[i].second - chi[k].second);
			map[i][k] = dist;
		}
	}
	
	//chi_cnt 개의 치킨집 중 M개를 골라(조합) 그 때의 치킨거리 구하기 => min을 갱신해 나간다.
	vector<int> v;
	for (int i = 0; i < chi_cnt; i++)
		v.push_back(i);

	vector<int> ind;
	for (int i = 1; i <= M; i++)
		ind.push_back(1);
	for (int i = 1; i <= chi_cnt - M; i++)
		ind.push_back(2);

	int sum = 10000;
	do
	{
		int* chi_dist = new int[home_cnt];
		memset(chi_dist, 10000, sizeof(int)*home_cnt);
		for (int i = 0; i < chi_cnt; i++)
		{
			if (ind[i] == 1)
			{
				for (int k = 0; k < home_cnt; k++)
				{
					if (chi_dist[k] > map[k][i])
						chi_dist[k] = map[k][i];
				}
			}
		}
		int temp_sum = 0;
		for (int k = 0; k < home_cnt; k++)
			temp_sum += chi_dist[k];

		if (sum > temp_sum)
			sum = temp_sum;

	} while (next_permutation(ind.begin(), ind.end()));

	printf("%d\n", sum);


	return 0;//Your program should return 0 on normal termination.
}

/*
크게 2단계로 풀었다.
1) 각 집과 치킨집과의 거리 구하기
집들의 좌표를 저장하는 vector와, 치킨집들의 좌표를 저장하는 vector를 하나씩 만들어, 좌표들을 저장했다.
임의의 두 칸 (r1, c1)과 (r2, c2) 사이의 거리는 |r1-r2| + |c1-c2|로 구한다.
라고 문제에서 명시했으므로, abs 함수를 사용하여 거리를 구했다.

2) 치킨집 중 M개를 골라(조합) 그 때의 치킨거리를 구했다.
예시1)에서 집1은 치킨집1과는 거리가 2고, 치킨집2와는 거리가 6이므로, 
M=2인 상황에서, 집1,2를 선택한 상황에서 집1의 치킨거리는 min(2,6)이므로 2가 된다. 
이런 식으로 모든 집들의 치킨거리를 구하고 다 더한다.
그 다음으로는 치킨집1,3 / 1,4 / 1,5 / 2,3 / ,,, / 4,5의 조합에서의 치킨거리를 구한다. 이 중 가장 min이 답이 된다.

이슈사항1) 조합을 어떻게 구할 것인가
https://twpower.github.io/90-combination-by-using-next_permutation 를 참조했다.
#include <algorithm> 의 next_permutation함수를 사용했다.

이슈사항2) 런타임에러
런타임에러는 대부분 배열의 인덱스를 참조할 때, 범위를 벗어날 때 발생한다.
각 집에서 치킨집 까지의 거리를 구하는 map[home][chi]배열의 인덱스를 [51][51]로 잡았었다. 
하지만, 집은 최대 100개이므로, [101][51]로 수정해, 런타임에러를 해결할 수 있었다. 
(추후, 조건 중 치킨집의 최대 개수인 13을 보았다. [100][13]으로 하는 것이 메모리를 최소로 쓸 수 있는 것일 것이다.)
*/
