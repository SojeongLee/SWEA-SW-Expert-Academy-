#include <iostream>
#include <string>
#include <cstdio>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
	int N;
	cin >> N;

	string word[100];

	for(int i=0 ; i<N; i++)
	{
		cin >> word[i];
	}

	int cnt = 0; //그룹단어 개수
	for(int i=0 ; i<N ; i++)
	{
		int flag = 1; //일단 그룹단어로
		int abc[27] = {0};
		int L = word[i].length();

		abc[word[i].at(0) - 'a'] = 1;
		int prev = word[i].at(0);

		for(int k=1 ; k<L ; k++)
		{
			int now = word[i].at(k);

			if(now == prev) 
				continue;
			else if(abc[now - 'a'] == 1) //이미 체크된 문자 -> 그룹단어가 아님
			{
				flag = 0;
				break;
			}
			else
			{
				abc[now - 'a'] = 1;
				prev = now;
			}
		}

		if(flag) cnt++;
	}

	return 0;//Your program should return 0 on normal termination.
}


/*
1316. 그룹 단어 체커 단계7(문자열 사용하기)-5
그룹 단어란 단어에 존재하는 모든 문자에 대해서, 각 문자가 연속해서 나타나는 경우만을 말한다. 
예를 들면, ccazzzzbb는 c, a, z, b가 모두 연속해서 나타나고, kin도 k, i, n이 연속해서 나타나기 때문에 그룹 단어이지만, 
aabbbccb는 b가 떨어져서 나타나기 때문에 그룹 단어가 아니다.
-> 논리는 3단 구조로,
1) 앞 문자와 같으면 continue
2) 다르고 아직 체크 안되있는 문자면 check
3) 다른데 이미 체크되어있는 거면 flag = 0;
flag = 1인 것의 cnt++;
cout << cnt;

이슈사항) 없음
*/
