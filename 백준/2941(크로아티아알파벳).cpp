#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	string alpha[8] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};
	int Len[8] = {2,2,3,2,2,2,2,2};

	string word;
	cin >> word;

	int L = word.length();
	int index = 0;
	int cnt = 0; //출력할 문자의 수
	while(1)
	{
		int flag = 1;
		for(int i=0 ; i<8 ; i++) //특수한 8개의 문자인지를 우선 판별해야
		{
			if(word.substr(index,Len[i]) == alpha[i])
			{
				cnt++;
				index += Len[i];
				flag = 0;
				break;
			}
		}

		if(flag)
		{
			cnt++;
			index++;
		}

		if(index >= L)
			break;
	}

	cout << cnt;


	return 0;//Your program should return 0 on normal termination.
}

/*
예를 들어, ljes=njak은 크로아티아 알파벳 6개(lj, e, š, nj, a, k)로 이루어져 있다. 
단어가 주어졌을 때, 몇 개의 크로아티아 알파벳으로 이루어져 있는지 출력한다.
dž는 무조건 하나의 알파벳으로 쓰이고, d와 ž가 분리된 것으로 보지 않는다. lj와 nj도 마찬가지이다. 
위 목록에 없는 알파벳은 한 글자씩 센다.

우선, 주어진 표에 8개의 알파벳은 예외처리를 해야함을 느낌,
string alpha[8] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};
int Len[8] = {2,2,3,2,2,2,2,2};
string 배열로 만들었다,,
-> 그런 후 2단 논리를 while문 안에서 가져감,

1) if(word.substr(index,Len[i]) == alpha[i])
즉, 해당 위치에서, 예외처리하는 8개의 알파벳에 속하는지, 일단 점검,
속한다면 -> cnt++, 즉 카운트는 1개를 세지만, index는 1개를 늘리는 것이 아닌, 
index += Len[i]; 만큼 해줘야 한다!
2) 1)에서 if문에 걸리면 flag = 0으로 설정!, 이유는 flag = 1일 때의 의미 부여,
의미 : 예외처리하는 8개의 알파벳에 속하지 않음, 
즉, 위 목록에 없는 알파벳은 한 글자씩 센다.는 조건을 처리하기 위해서임. 
이때는 노말하게 cnt++, index++을 해줌.
*/
