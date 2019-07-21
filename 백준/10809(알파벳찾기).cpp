#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	string S;
	cin >> S;

	int alpha[26] = { 0 }; //알파벳이 등장하면 1로 바꾸어, 초기에만 인덱스를 저장하게,,
	int ind_alpha[26]; //각 알파벳이 처음 등장하는 인덱스 저장
	for (int i = 0; i < 26; i++)
	{
		ind_alpha[i] = -1; //우선 -1로 초기화
	}

	for (int i = 0; i < S.length(); i++)
	{
		if (alpha[S[i] - 'a'] == 0) //해당 알파벳이 처음 등장하는 것이라면
		{
			ind_alpha[S[i] - 'a'] = i;
			alpha[S[i] - 'a'] = 1; //1로 방문처리 해줘야함!!
		}
	}

	for (int i = 0; i < 26; i++)
		cout << ind_alpha[i] << " ";


	return 0;//Your program should return 0 on normal termination.
}

/*
int alpha[26] = { 0 }; //알파벳이 등장하면 1로 바꾸어, 초기에만 인덱스를 저장하게,,
int ind_alpha[26]; //각 알파벳이 처음 등장하는 인덱스 저장
우선 각 알파벳이 처음 등장하는 인덱스를 저장할 ind_alpha[] 와 
해당 알파벳이 처음 나온 인덱스만 필요하므로, 방문 체크를 할 alpha[] 배열을 선언하였다.

이슈사항)
if (alpha[S[i] - 'a'] == 0) //해당 알파벳이 처음 등장하는 것이라면
{
	ind_alpha[S[i] - 'a'] = i;
	alpha[S[i] - 'a'] = 1; //1로 방문처리 해줘야함!!
}
1로 방문처리를 해줘야, 다음에 같은 알파벳이 등장했을 때 if문의 ==0 조건에 해당하지 않게 되어, 
인덱스를 업데이트하지 않게 된다,,
*/
