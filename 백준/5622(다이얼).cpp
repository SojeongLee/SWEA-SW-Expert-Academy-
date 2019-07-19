#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	int abc[26] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};

	string word;
	cin >> word;

	int time = 0;
	int L = word.length();
	for(int i=0 ; i<L ; i++)
	{
		time += abc[word.at(i) - 'A'];
	}
	time += L;

	cout << time;


	return 0;//Your program should return 0 on normal termination.
}


/*
일단 숫자 1과 0은 해당 문자가 없으므로,
포함되지 않는다고 가정하고 풀었고, 이것이 맞는듯,,
뭔가 문제가 좀 이상?하다 느낌,, 너무 1차원 적이라 이게 맞을까?했는데 맞음,,
int abc[26] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
다이얼 문자에 해당하는 수를 미리 정의해서,, 예를들어, 2는 A,B,C에 해당하는 수임,
for(int i=0 ; i<L ; i++)
{
	time += abc[word.at(i) - 'A'];
}
time += L;
우선, 해당 문자에 대응하는 수를 time 변수에 더해감,,
숫자 1을 걸려면 총 2초가 필요하다. 1보다 큰 수를 거는데 걸리는 시간은 이보다 더 걸리며, 
한 칸 옆에 있는 숫자를 걸기 위해선 1초씩 더 걸린다.
따라서, 2는 3초가, 3은 4초가 걸리는 것, 따라서 time 변수에 해당 문자열의 자릿수만큼 더해주어야 함,,!
*/
