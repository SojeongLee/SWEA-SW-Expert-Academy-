#include <iostream>
#include <math.h>

using namespace std;



int main(int argc, char** argv)
{
	int N, A, B;
	cin >> N >> A >> B;

	int R = 1;

	while(1)
	{
		int group = pow(2.0, R); //cout << R << " " << group << endl;
		int flag = 0; //김지민과 김한수가 같은 그룹에 속하게되면 1로 set

		for(int i=1 ; ; i+=group)
		{
			if(i<=A && A<=i+group-1)
			{
				if(i<=B && B<=i+group-1)
				{
					flag = 1; //cout << "flag" << endl;
					break;
				}
				else
				{
					R++;
					break;
				}
			}
		}

		if(flag)
			break;
	}

	cout << R;

	return 0;//Your program should return 0 on normal termination.
}

/*
시간초과 떴었는데,, 이유는
이슈사항) 무한루프
for(int i=1 ; ; i+=group) 
이부분에 N-group+1이란 조건을 넣었는데, 사실 N보다 group이 더 큰 수가 될 수 있으므로,, 무한루프에 빠졌었다,,
ex) 11 8 9 일때,, group이 16이 되므로 계속 R = 4가 되었을 때, for문이 실행이 안되어서, 
이중if문에 걸릴 수 있음에도 못걸림,, 그래서 flag가 1로 바뀌지 않아서,, flag가 0이어서 전체 while문을 못 탈출함,,
어짜피 조건을 두지 않아도, 결국에는 같은 그룹에 속하게 되어있으므로,,!

문제) 첫째 줄에 김지민과 임한수가 대결하는 라운드 번호를 출력한다. 만약 서로 대결하지 않을 때는 -1을 출력한다.

서로 대결하지 않는 경우는 없다,,! 즉, 문제에 훼이크가 있는 것,, 낚이지 말 것!
내가 사용한 grouping 방법으로 하면, 홀수/짝수 여부도 상관 없다,,
*/
