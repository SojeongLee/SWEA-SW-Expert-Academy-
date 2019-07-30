#include <iostream>
#include <math.h>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	string N;
	cin >> N;

	int L = N.length(); //자리수
	
	string s4 = "4";
	string s7 = "7";
	
	string gms;
	string GMS;
	//N이하이고 가장큰 금민수를 찾는다.
	for(int i=L-1 ; i<=L ; i++)
	{
		int b = pow(2, i);
		for (int k=0 ; k<b ; k++)
		{
			gms = "";
			for (int m = i-1; m >=0 ; m--)
			{
				//cout << k << ", " << (int)pow(2, m) << " & = " << ((b - 1) & (int)pow(2, m)) << endl;
				if ((k & (int)pow(2, m)) == 0)
				{
					gms.append(s4);
				}
				else
				{
					gms.append(s7);
				}
			}

			//if (gms >= N) break; -> 구현해야,,
			if (gms.length() == L)
			{
				if (gms == N)
				{
					GMS = gms;
					break;
				}

				for (int q = 0; q < L; q++)
				{
					if (gms[q] > N[q])
					{
						//cout << (gms[q] >= N[q]) << endl;
						//flag = 0;
						goto A;
					}
					else if (gms[q] < N[q])
					{
						GMS = gms;
						break;
					}
				}
			}
			else
			{
				GMS = gms;
			}
			//cout << gms << endl;
		}

	}
	A :
	//cout << gms << endl;
	cout << GMS << endl;

	return 0;//Your program should return 0 on normal termination.
}

/*
우선 4와 7로 구성된 수를 어떻게 만들까 고민한 결과, string 헤더의 append()함수를 사용하였다.
논리구조는 3단으로 하였다.
1) 입력받은 수의 자릿수를 구한다.
   만약 3자리면, 이 수보다 작거나 같은 금민수를 찾는 것이므로, 정답이 되는 금민수는 2자리 또는 3자리가 될 것이다. 
   2자리 수 중 가장 작은 44부터 3자리 가장 큰 777까지.
2) 44부터 777까지 조합해 나갈 방법으로 비트연산을 생각했다.
   두자리 수는 00, 01, 10, 11 이 금민수에는 44, 47, 74, 77 로 대응했고,
   세자리 수는 000, 001, 010, 011, 100, 101, 110, 111 은 444, 447, 474, 477, 744, 747, 774, 777 로 대응했다.
3) 조합을 찾아나가는 와중에, 입력한 수보다 크면 break;로 for문을 빠져나간다.
   이 때, break;로 빠져나간 수는, 입력한 수보다 크므로, 문제에서 원하는 답이 아니다. 
   문제에서는 같거나 작은 수를 원하므로, gms를 조합하고 검사해나가는 변수로 설정하였고, 
   입력한 수보다 gms가 같거나 작으면 GMS에 업데이트하였다. 
   따라서 GMS가 문제에서 구하려는 답을 저장하는 변수가 된다. 
*/
