#include <iostream>
#include <string>
#include <math.h>

using namespace std;


int main(int argc, char** argv)
{
	string temp;
	cin >> temp;
	//시작 포인트
    int start_x = temp[0] - 'A' + 1;
	int start_y = temp[1] - '0';

	int map[10][10] = { 0 }; //1~6번 사용
	map[start_x][start_y] = 1; //시작포인트 방문처리

	int before_x = temp[0] - 'A' + 1;
	int before_y = temp[1] - '0';

	int temp_x;
	int temp_y;
	int diff_x, diff_y;
	//나이트경로가 맞는지 검사해나간다. + 체스판에 방문 표시
	for (int i = 1; i < 36; i++)
	{
		cin >> temp;
		temp_x = temp[0] - 'A' + 1;
		temp_y = temp[1] - '0';

		diff_x = abs(temp_x - before_x);
		diff_y = abs(temp_y - before_y);
		if ((diff_x == 1 && diff_y == 2) || (diff_x == 2 && diff_y == 1)) //나이트의 이동이 맞음 (방문처리 후 before 좌표 저장)
		{
			map[temp_x][temp_y] = 1;
			before_x = temp_x;
			before_y = temp_y;
		}
		else //나이트의 이동이 아님
		{
			printf("Invalid");
			return 0;
		}
	}

	//마지막으로 방문하는 칸에서 시작점으로 돌아올 수 있는지 검사
	diff_x = abs(start_x - before_x);
	diff_y = abs(start_y - before_y);
	if ((diff_x == 1 && diff_y == 2) || (diff_x == 2 && diff_y == 1)) //나이트의 이동이 맞음 
	{
		int flag = 1; //다 방문하지 않았을 시 0으로
		//모든 지점을 방문했는지 검사
		for (int i = 1; i <= 6; i++)
		{
			for (int k = 1; k <= 6; k++)
			{
				if (map[i][k] == 0)
				{
					flag = 0;
					break;
				}
			}
		}
		if (flag)	printf("Valid");
		else	printf("Invalid");
	}
	else //나이트의 이동이 아님
	{
		printf("Invalid");
	}
	
	return 0;//Your program should return 0 on normal termination.
}

/*
시뮬레이션으로 나이트의 경로가 맞는지 검사해나갔다.  + 체스판에 방문 표시
이 때, 나이트의 경로인지 검사하는 것을, 
diff_x = abs(temp_x - before_x);
diff_y = abs(temp_y - before_y);
if ((diff_x == 1 && diff_y == 2) || (diff_x == 2 && diff_y == 1))
로 검사하였다. 즉, 좌우로 1칸을 움직이면, 상하로 2칸을 움직여야 나이트 경로인 것이고, 
만약 좌우로 2칸을 움직였다면, 상하로는 1칸을 움직여야 나이트 경로이므로, 
if문을 ||로 구성했다.
*/
