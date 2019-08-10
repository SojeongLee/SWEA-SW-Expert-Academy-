#include <iostream>
#include <string>
#include <queue>

using namespace std;


int main(int argc, char** argv)
{
	int R, C;
	scanf("%d %d", &R, &C);

	string *map = new string[R];
	for (int i = 0; i < R; i++)
	{
		cin >> map[i];
	}

	//고슴도치(S)와 물(*)의 위치 구하기
	int visited_water[50][50] = {0};
	int visited_area[50][50] = {0};

	queue<pair<int,int> > water;
	int xS, yS;
	for (int i = 0; i < R; i++)
	{
		for (int k = 0; k < C; k++)
		{
			if (map[i][k] == 'S') //고슴도치
			{
				xS = i, yS = k;
				map[i][k] = '.'; //고슴도치가 표시될 필요는 없다.
				visited_area[i][k] = 1;
			}
			else if(map[i][k] == '*') //물
			{
				water.push(pair<int,int>(i,k));
				visited_water[i][k] = 1;
			}
		}
	}
	queue<pair<int,int> > root;
	root.push(pair<int,int>(xS,yS));

	//로직 시작
	int cnt = 0; //고슴도치의 이동횟수
	while (!root.empty())
	{
		int dx[4] = { 1,-1,0,0 };
		int dy[4] = { 0,0,1,-1 };
		//물이 한칸 퍼진다.
		int num = water.size();		
		for(int i=0 ; i<num ; i++)
		{
			int x = water.front().first;
			int y = water.front().second;
			water.pop();
			for (int dir = 0; dir < 4; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];

				if (tx < 0 || tx >= R || ty < 0 || ty >= C)
					continue;
				if (map[tx][ty] == '.' && visited_water[tx][ty] == 0) //방문처리 해야!
				{
					visited_water[tx][ty] = 1;
					map[tx][ty] = '*';
					water.push(pair<int,int>(tx,ty));
				}
			}
		}

		//고슴도치를 한칸 이동
		int size = root.size();
		cnt++;
		for(int i=0 ; i<size ; i++)
		{
			int x = root.front().first;
			int y = root.front().second;
			root.pop();
			for (int dir = 0; dir < 4; dir++)
			{
				int tx = x + dx[dir];
				int ty = y + dy[dir];
				if (tx < 0 || tx >= R || ty < 0 || ty >= C)
					continue;
				if(map[tx][ty] == 'D') //비버의 굴에 도착
				{
					printf("%d\n", cnt);
					return 0;
				}
				if(map[tx][ty] == '.' && visited_area[tx][ty] == 0) //방문처리 해야!
				{
					visited_area[tx][ty] = 1;
					root.push(pair<int,int>(tx,ty)); //다음에 갈 수 있는 칸들을 저장해둠
				}
			}
		}

	}

	printf("KAKTUS\n");


	return 0;//Your program should return 0 on normal termination.
}

/*
BFS를 이용해, 크게 3단계로 풀었다.
1) 물이 먼저 한 칸 퍼진다.(BFS)
2) 고슴도치가 도달할 수 있는 영역도 한 length 늘어난다.(BFS)
3) 고슴도치가 비버의 굴에 도착했다면 끝!

이슈사항) 여기서 BFS를 사용했는데, 꼭 방문처리를 해줘야 한다! 안그러면 메모리초과가 난다.
*/
