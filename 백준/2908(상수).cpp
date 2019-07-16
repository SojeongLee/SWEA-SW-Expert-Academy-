#include <iostream>
#include <string>
#include <cstdio>


using namespace std;


int main(int argc, char** argv)
{
	string num1, num2;
	cin >> num1 >> num2;

	for(int i=2 ; i>=0 ; i--)
	{
		if(num1.at(i) < num2.at(i))
		{
			for(int k=2 ; k>=0 ; k--)
				cout << num2.at(k);
			break;
		}
		else if(num1.at(i) > num2.at(i))
		{
			for(int k=2 ; k>=0 ; k--)
				cout << num1.at(k);
			break;
		}
	}


	return 0;//Your program should return 0 on normal termination.
}



/*
input) 734 893 -> output) 437
논리 구조를 그냥 1단으로 함,, : 734와 893을 뒤집지 않고, 맨 뒤부터, 즉 [2]부터 비교,
4와 3을 비교하게 되고, 4가 더 크므로 437을 출력해야 함!
이때도 뒤집지 않고, [2] [1] [0] 순으로, for문으로 한자리씩 출력!
이슈사항) 없음
*/
