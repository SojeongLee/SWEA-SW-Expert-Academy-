#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	int ABC[26] = {1,2,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}; //구멍 수

	int T;
	scanf("%d",&T);
	for(int test_case = 1 ; test_case <= T ; test_case++)
	{
		string s1, s2;
		cin >> s1 >> s2;

		int len1 = s1.length();
		int len2 = s2.length();
		if(len1 != len2)
		{
			printf("#%d DIFF\n",test_case);
			continue;
		}

		int flag = 1;
		for(int i=0 ; i<len1 ; i++)
		{
			if(ABC[s1[i]-'A'] != ABC[s2[i]-'A'])
			{
				flag = 0;
				break;
			}
		}
		if(flag) printf("#%d SAME\n",test_case);
		else printf("#%d DIFF\n",test_case);
	}

	return 0;
}

/*
우선 크게 2가지로 경우를 나누었다.
1) 글자 수가 다르면 바로 DIFF를 출력하고 다음 케이스로 넘어가도록 했다.

2) 글자 수가 같은 경우는, 문자열의 첫 번째 문자부터 같은 문자로 인식하는지를 판별해 나갔다.
int ABC[26] = {1,2,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}; //구멍 수
를 미리 정의해 두었고,
if(ABC[s1[i]-'A'] != ABC[s2[i]-'A'])
로 같은 값이 아니면, DIFF를, 문자열의 끝까지 같은 값을 가지면 SAME을 출력하게 했다.
*/
