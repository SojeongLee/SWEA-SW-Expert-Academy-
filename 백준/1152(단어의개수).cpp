#include <iostream>
#include <string>
#include <cstdio>
#include <queue>

using namespace std;


int main(int argc, char** argv)
{
	string word;
	getline(cin, word, '\n');

	int cnt = 1;
	int L = word.length();

	for (int i = 0; i < L; i++)
	{
		if (word.at(i) == ' ')
		{
			cnt++;
		}
	}

	//문자열의 앞과 뒤에는 공백이 있을 수도 있다. (이 경우는 cnt-- 해줘야함)
	if (word.at(0) == ' ') cnt--;
	if (word.at(L - 1) == ' ') cnt--;

	cout << cnt;

	return 0;//Your program should return 0 on normal termination.
}



/*
단어는 띄어쓰기 한 개로 구분되며, 공백이 연속해서 나오는 경우는 없다. 
또한 문자열의 앞과 뒤에는 공백이 있을 수도 있다.
이 부분 때문에, 정답률이 낮은듯,,
-> 논리는 2단 구조로
1) cnt=1로 초기화, 공백의 개수를 센다

이슈사항)
2) //문자열의 앞과 뒤에는 공백이 있을 수도 있다. (이 경우는 cnt-- 해줘야함)
if(word.at(0) == ' ') cnt--;
if(word.at(L-1) == ' ') cnt--;
이 부분을 안해주면, 위에 조건인 앞, 뒤에 공백이 있을경우, 단어가 더 있다고 판단한다,,
따라서 맨 앞 [0] 과 맨 뒤 [L-1]에 공백이 있는지 검사하고, 있으면 cnt-- 해줘야 한다!
*/
