#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{	
	int N, M, K;
	scanf("%d %d %d",&N,&M,&K);

	int A[10][10]; //매년 겨울에 더해질 양분
	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<N ; k++)
			scanf("%d",&A[i][k]);
	}

	int energy[10][10]; //양분
	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<N ; k++)
			energy[i][k] = 5;
	}

	deque<deque<deque<int> > > map(10, deque<deque<int> >(10)); //땅
	int tree_cnt = M; //나무의 개수
	int x, y, age;
	for(int i=0 ; i<M ; i++)
	{
		scanf("%d %d %d",&x, &y, &age);
		map[x-1][y-1].push_back(age);
	}
	//나무의 나이 내림차순으로 저장
	for(int i=0 ; i<N ; i++)
	{
		for(int k=0 ; k<N ; k++)
			sort(map[i][k].begin(), map[i][k].end(), greater<int>());
	}

	int dx[8] = {-1,-1,-1,0,0,1,1,1};
	int dy[8] = {-1,0,1,-1,1,-1,0,1};
	for(int year=1 ; year<=K ; year++)
	{
		//봄, 여름
		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<N ; k++)
			{
				int size = map[i][k].size();
				if(size == 0) //해당 칸에 나무가 없으면 넘어감
					continue;

				//나이가 어린 나무부터 양분을 먹음
				int n;
				for(n=size-1 ; n>=0 ; n--)
				{
					if(energy[i][k] >= map[i][k][n])
					{
						energy[i][k] -= map[i][k][n];
						map[i][k][n] += 1;
					}
					else //양분이 다 떨어짐
						break;
				}
				for(int m=0 ; m<=n ; m++) //죽은 나무가 양분으로 변함 + pop
				{
					tree_cnt--;
					energy[i][k] += map[i][k][0]/2;
					map[i][k].pop_front();
				}
			}
		}
		//가을
		for(int i=0 ; i<N ; i++)
		{
			for(int k=0 ; k<N ; k++)
			{
				int size = map[i][k].size();
				for(int n=size-1 ; n>=0 ; n--)
				{
					if(map[i][k][n] % 5 == 0) //인접한 8개의 칸에 나이가 1인 나무를 생성한다.
					{
						for(int dir=0 ; dir<8 ; dir++)
						{
							int tx = i + dx[dir];
							int ty = k + dy[dir];
							if(tx<0 || ty<0 || tx>=N || ty>=N)
								continue;

							tree_cnt++;
							map[tx][ty].push_back(1);
						}
					}
				}
				//겨울
				energy[i][k] += A[i][k];
			}
		}
	}

	printf("%d\n",tree_cnt);

	return 0;
}

/*
우선 처음에 떠올린 아이디어는 낚시왕 문제처럼, 스트럭쳐 tree를 선언해서, 해당 좌표에 벡터로 관리를 하려 했지만,, 
스트럭쳐를 얼만큼의 크기로 선언해야 할지도 명확하지 않기 때문에(나무는 입력자체는 최대 100개이지만, 
매년 8개의 인접 칸으로 생성될 수 있으므로, 매우 커질 수 있다.) 이 방법은 런타임에러 or 시간초과를 유발했다.

따라서, 벡터가 아닌 deque를 사용하였다. 
(deque를 처음 사용해본 것인데, 앞에서 입력/삭제, 뒤에서 입력/삭제가 모두 된다는 점이 굉장한 장점이라고 생각했고, 
벡터나 리스트보다도 훨씬 빠른 시간에 해당 연산이 된다는 점 또한 큰 장점이란 생각이 들어, 앞으로 자주 사용해야겠다는 생각이 들었다.)

deque<deque<deque<int> > > map(10, deque<deque<int> >(10)); //땅
위와 같이, 10바이10인 2차원 배열에, 각 원소는 동적으로 int 원소배열(나무들의 나이)을 가질 수 있다. 
즉, 행/열은 10바이10으로 고정이고, 해당 칸에 높이가 동적인, 3차원 배열이라고 생각할 수 있다.
자료구조를 위와 같이 3차원 deque로 생각한 후, 크게 4단계로 풀이하였다.

1. 나무의 나이를 내림차순으로 저장하였다.
  sort(map[i][k].begin(), map[i][k].end(), greater<int>());
2. 봄/여름 : 나이가 어린 나무부터 양분을 먹는다. 
   이 때, 양분이 떨어진 후의 나무들은 모두 죽은 나무가 되고, 양분으로 변한 후 deque에서 pop해준다. (pop을 안 하면 시간초과가 난다!)
3. 가을 : 나이가 5의 배수가 있는 나무에 인접한 8개의 칸에 나이가 1인 나무를 생성한다.
4. 겨울 : 양분을 추가한다.

예를 들어 (2,1)에 나무가 5,4,3,2,1 의 나이들이 있었고, 뒤에서부터 1,2,3에게 양분을 주었다고 해보자. 
이후 4,5 나무는 죽어 양분이 되고 pop해줘야 한다.
이때, deque의 pop_front()를 사용해서, 앞에서부터 즉, 5,4 순으로 pop하였다. 
그 다음, 인접한 칸에 나이가 1인 나무를 생성할 때에는, 나이가 1이므로, 가장 오른쪽에 push되어야 하므로, push_back(1)을 사용하였다.
물론, 오름차순으로 할 수도 있다. 하지만 처음에 vector를 이용해서 푸려고 했다보니, 내림차순으로 접근하는 로직을 생각했었다.
만약, 오름차순으로 정렬했다면, 앞에서부터 양분을 주고, 그 다음 지점부터 남은 나무의 개수만큼 pop하고, 
나이가 1인 새로운 나무는 push_front(1)를 사용하면 될 것이다.
*/
