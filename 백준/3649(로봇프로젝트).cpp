#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
	int x;
	while(scanf("%d",&x) == 1)
	{
		x *= 10000000;

		int n;
		scanf("%d",&n);

		vector<int> v;
		int temp;
		for(int i=0 ; i<n ; i++)
		{
			scanf("%d",&temp);
			v.push_back(temp);
		}
		sort(v.begin(),v.end());

		int start = 0;
		int end = n-1;
		int sum;
		int flag = 0;
		while(start<end)
		{
			sum = v[start] + v[end];
			if(sum == x)
			{
				flag = 1;
				break;
			}
			else if(sum < x)
			{
				start++;
			}
			else //sum > x
			{
				end--;
			}
		}
		if(flag) printf("yes %d %d\n",v[start],v[end]);
		else     printf("danger\n");
	}

	return 0;
}

/*
우선 1cm 는 10000000나노미터이다.
해당 숫자들을 벡터에 저장하여, sort함수로 오름차순 하였다.
그 후, 처음과 끝에 인덱스를 두고, 이 두 인덱스가 가리키는 값을 더한 값과, 찾으려는 값을 비교하여, 
작으면 앞의 인덱스를 ++하고, 크면 뒤에 인덱스를 --하였다.

이슈사항) 조건 중 [입력은 여러 개의 테스트 케이스로 이루어져 있다.]
입력이 몇 개가 있다라고 알려주지 않았는데, 어떻게 해야 할까?
while(scanf("%d",&x) == 1)
{
  //소스코드 작성
}
를 사용하면 된다. 그리고, 
//소스코드 작성 부분에는 return 문이 있으면 안 되는 점을 유의해야 한다.
*/
