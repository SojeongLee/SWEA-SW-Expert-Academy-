#include <iostream>
#include <string>
#include <cstdio>
#include <queue>

using namespace std;



int main(int argc, char** argv)
{
	int T, test_case;

	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{
		int N;
		cin >> N;

		string name[110];

		for(int i=0 ; i<=N ; i++) //name[1]~[N]까지,, 왜 [0]은 안들어 가는거지??
		{
			getline(cin, name[i], '\n');
		}

		int max = 0;
		int index = 0;
		for(int i=1 ; i<=N ; i++)
		{
			int abc[26] = {0};
			for(int k=0 ; k<name[i].length() ; k++)
			{
				abc[name[i].at(k) - 'A'] = 1;
			}

			int cnt = 0;
			for(int l=0 ; l<26 ; l++)
			{
				if(abc[l] == 1) cnt++;
			}

			if(max < cnt)
			{
				max = cnt;
				index = i;
			}
			else if(max == cnt) //사전순으로 앞선 사람이 반장이 됨,,
			{
				int l1 = name[index].length();
				int l2 = name[i].length();
				int L = (l1>l2)? l2 : l1;

				for(int m=0 ; m<L ; m++)
				{
					if(name[index].at(m) < name[i].at(m))
					{
						break;
					}
					else if(name[index].at(m) > name[i].at(m))
					{
						index = i;
						break;
					}
				}
			}
		}
		

		// Print the answer to standard output(screen).
		cout << "#" << test_case+1 << " " << name[index] << endl;
		
	}

	return 0;//Your program should return 0 on normal termination.
}


/*
이슈사항1)
int N;
cin >> N;

string name[110];

for(int i=0 ; i<=N ; i++) //name[1]~[N]까지,, 왜 [0]은 안들어 가는거지??
{
	getline(cin, name[i], '\n');
}
여기서
BBIBBI
DEAD BEEF
ABCDDCBA
이렇게 공백문자를 포함한 하나의 문자열로 받으려고 getline 함수를 썼다.
근데, 첫번째 문자열에는 ‘\n’이 들어가는지, name[1]부터 BBIBBI가 입력되었다,,
그래서 for문도 0부터 <N 이 아니라, <=N 으로 하였다,,

이슈사항2)
if(name[index].at(m) < name[i].at(m))
{
	break;
}
else if(name[index].at(m) > name[i].at(m))
{
	index = i;
	break;
}
사전순으로 앞선다는 것은, (A<B 이므로) 더 작은 값이라는 것!

이슈사항3) 조건을 잘 확인하자!
첫 번째 줄에 테스트 케이스의 수 T(1 ≤ T ≤ 100)가 주어진다.
각 테스트 케이스의 첫 번째 줄에는 학생 수 N(1 ≤ N ≤ 100)이 주어진다.
-> string name[110]; 으로 한 이유,, 아까 [1]부터 스트링을 받았으므로 100보다 커야함!
이름은 대문자 알파벳과 ‘ ’(space)로 이루어져 있다.
-> abc[name[i].at(k) - 'A'] = 1; 여기서 ‘a’로 했었다,, 정신 차리자!
*/
