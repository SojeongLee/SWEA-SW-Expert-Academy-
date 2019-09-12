#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
	int color[4] = {0}; //R,B,Y,G
	int num[10] = {0}; //1~9
	vector<int> number;

	char c;
	int n;
	for(int i=0 ; i<5 ; i++)
	{
		cin >> c >> n;
		switch(c)
		{
		case 'R' : color[0] += 1; break;
		case 'B' : color[1] += 1; break;
		case 'Y' : color[2] += 1; break;
		case 'G' : color[3] += 1; break;
		}
		num[n] += 1;
		number.push_back(n);
	}
	sort(number.begin(),number.end());

	int flag1 = 0; //모두 같은 색
	for(int i=0 ; i<4 ; i++)
	{
		if(color[i] == 5)
		{
			flag1 = 1;
			break;
		}
	}
	
	int flag2 = 1; //숫자 연속
	for(int i=1 ; i<5 ; i++)
	{
		if(number[i] != number[i-1]+1)
		{
			flag2 = 0;
			break;
		}
	}

	int flag3 = 0; //4장 숫자 같음
	int same_num3;
	int flag4 = 0; //3장 숫자 같음
	int same_num4;
	int flag5 = 0; //2장 숫자 같음
	int same_num5;
	int flag6 = 0; //또 2장 숫자 같음
	int same_num6;
	for(int i=1 ; i<=9 ; i++)
	{
		if(num[i] == 4)
		{
			flag3 = 1;
			same_num3 = i;
		}
		else if(num[i] == 3)
		{
			flag4 = 1;
			same_num4 = i;
		}
		else if(num[i] == 2)
		{
			if(flag5 == 0)
			{
				flag5 = 1;
				same_num5 = i;
				continue;
			}
			else
			{
				flag6 = 1;
				same_num6 = i;
			}
		}
	}

	int score = 0;
	int temp;
	//점수계산1~9
	if(flag1 && flag2)
	{
		temp = number[4] + 900;
		if(score < temp) score = temp;
	}
	if(flag3)
	{
		temp = same_num3 + 800;
		if(score < temp) score = temp;
	}
	if(flag4 && flag5)
	{
		temp = same_num4*10 + same_num5 + 700;
		if(score < temp) score = temp;
	}
	if(flag1)
	{
		temp = number[4] + 600;
		if(score < temp) score = temp;
	}
	if(flag2)
	{
		temp = number[4] + 500;
		if(score < temp) score = temp;
	}
	if(flag4)
	{
		temp = same_num4 + 400;
		if(score < temp) score = temp;
	}
	if(flag5 && flag6)
	{
		temp = same_num6*10 + same_num5 + 300;
		if(score < temp) score = temp;
	}
	if(flag5)
	{
		temp = same_num5 + 200;
		if(score < temp) score = temp;
	}
	temp = number[4] + 100;
	if(score < temp) score = temp;


	printf("%d\n",score);

	return 0;
}

/*
flag 변수에, 모든 조건에 대해서, 만족하면 1을, 아니면 0을 저장하였다.
그 다음, flag가 켜진 것에 따라서, 점수계산을 했는데, 
이 때, 여러 조건을 만족했을 수 있고, 이에 여러 점수가 나올 수 있으므로, 점수계산 후 최댓값이면 업데이트하였다.
*/
