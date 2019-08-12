#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	int N;
	string note;
	scanf("%d", &N);
	cin >> note;

	int dx[4] = {0,1,0,-1}; //동->남->서->북(시계방향 ; 오른쪽 회전)
	int dy[4] = {1,0,-1,0};
	int dir = 1; //초기방향은 남쪽

	char maze[100][100]; 

	//미로 초기화
	for (int i = 0; i < 100; i++)
	{
		for (int k = 0; k < 100; k++)
		{
			maze[i][k] = '#';
		}
	}
	
	int x = 49, y = 49; //start point
	maze[x][y] = '.';

	int start_x=49, end_x=49;
	int start_y=49, end_y=49;
	//시뮬레이션 시작
	for (int i = 0; i < note.size(); i++)
	{
		switch (note[i])
		{
		case 'F':
			x += dx[dir]; 	y += dy[dir];
			maze[x][y] = '.';

			if (start_x > x) start_x = x;
			if (end_x < x) end_x = x;
			if (start_y > y) start_y = y;
			if (end_y < y) end_y = y;
			break;
		case 'L':
			dir--;
			if (dir < 0) dir += 4;
			break;
		case 'R':
			dir++;
			if (dir >= 4) dir -= 4;
			break;
		}
	}

	//미로출력
	for (int i = start_x; i <= end_x; i++)
	{
		for (int k = start_y; k <= end_y; k++)
		{
			printf("%c", maze[i][k]);
		}
		printf("\n");
	}

	return 0;//Your program should return 0 on normal termination.
}

/*
크게 3가지 포인트로 풀었다.
1) 우선 선언할 미로의 크기를 결정해야 했다. 
홍준이가 적은 내용의 길이가 50보다는 작으므로, 미로의 중앙에서 시작한다고 했을 때, 한쪽으로 쭉 가는 경우가 인덱스가 최대가 된다. 
따라서 maze[100][100]을 선언하고, 시작점을 [49][49]로 정하였다.

2) dx[4], dy[4], dir 변수를 선언하여, 쪽지에 적힌 방향/이동대로 시뮬레이션 하였다.

3)(이슈사항) 출력해야 할 미로의 범위
처음에는 시뮬레이션을 다 하고 범위를 구하려고 하였으나, maze를 0,0부터 다 탐색해나가야 하므로, 비효율적이라고 생각하였다.
따라서, 2)에서 시뮬레이션을 할 때마다, 
현재 위치의 인덱스가 미로의 범위(start/end)보다 작거나/크면 업데이트 해나가는 방식으로 미로의 범위를 구하였다.
*/
