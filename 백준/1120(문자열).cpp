#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	string X, Y;
	cin >> X;
	cin >> Y;

	int lenX = X.length();
	int lenY = Y.length();
	int diff = 50;

	for (int i = 0; i <= lenY - lenX; i++)
	{
		int temp_diff = 0;
		
		for (int k = 0; k < lenX; k++)
		{
			if (X[k] != Y[k + i])
				temp_diff++;
		}

		if (temp_diff < diff)
		{
			diff = temp_diff;
		}
	}	

	printf("%d\n", diff);

	return 0;//Your program should return 0 on normal termination.
}

/*
우선 B가 A보다 길거나 같다는 조건에 주목했다.

같은 경우) 같은 인덱스 위치에 같은 문자가 왔는지 비교만 하면 된다.
다른 경우) 예를 들어, A가 5글자이고, B가 6글자인 경우, 같은 경우) 에서 비교한 프로세스를 두 번 반복하면 된다. 
즉, B의 인덱스0~4와 A의 인덱스0~4를 비교하고, 그 다음으로는 B의 인덱스1~5와 A의 인덱스0~4를 비교하면 된다. 
A의 인덱스는 항상 0~4가 된다. 
즉 A문자열이 B문자열의 처음부터 비교하여, 한 칸씩 옮겨가며 비교하는 형상이 된다. 

(문제에서 A의 앞 / 뒤에 아무 알파벳이나 추가한다. 라는 조건은, 
결국은 주어진 A문자열과 B와의 특정 구간에서의 비교만을 하면 됨을 둘러서 얘기하고 있는 것이다.)
*/
