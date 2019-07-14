#include <iostream>
#include <string>
#include <cstdio>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
	string word;
	cin >> word;

	int abc[26] = {0};
	int L = word.length();

	for(int i=0 ; i<L ; i++)
	{
		char temp = word.at(i);

		if(temp >= 'a' && temp <= 'z')
		{
			abc[temp - 'a']++;
		}
		else if(temp >= 'A' && temp <= 'Z')
		{
			abc[temp - 'A']++;
		}
	}

	int cnt = 0; //가장 많이 사용된 알파벳의 개수(1이어야 출력, 아니면 ?출력)
	int max = abc[0];
	int index = 0;
	for(int i=1 ; i<26 ; i++) //우선 최댓값을 구해야! (그 다음 중복검사를 해야됨)
	{
		if(max < abc[i])
		{
			max = abc[i];
			index = i;
		}
	}

	for(int i=0 ; i<26 ; i++) //여기서 중복검사
	{
		if(max == abc[i])
			cnt++;
	}

	char result = 'A'+index;

	if(cnt == 1) cout << result;
	else cout << '?';

	return 0;//Your program should return 0 on normal termination.
}


/*
알파벳 대소문자로 된 단어가 주어지면, 이 단어에서 가장 많이 사용된 알파벳이 무엇인지 알아내는 프로그램을 작성하시오. 
단, 대문자와 소문자를 구분하지 않는다.
우선 abc[] 에 각 단어 사용 개수를 카운트
첫째 줄에 이 단어에서 가장 많이 사용된 알파벳을 대문자로 출력한다. 
단, 가장 많이 사용된 알파벳이 여러 개 존재하는 경우에는 ?를 출력한다.

이슈사항) 논리는 2단 구조로 (처음엔 1단으로 했으나, 나눠야 함을 인지)
1) 우선 최댓값을 구해야!
2) 그 다음 중복검사를 해야한다.
문제의 조건은 가장 많이 사용된 알파벳이 여러 개 존재하는 경우를 예외처리 하는 것임.
근데, 1단처리로 하다보면, 최댓값을 찾기도 전에, 중복검사를 해버려서 오류,,
따라서 단계적으로 세분화하는 능력을 기를 것!
*/
