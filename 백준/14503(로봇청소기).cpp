#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
	int r, c; //로봇의 현재 위치
	int rd; //로봇이 바라보는 방향
	int map[50][50]; //청소할 구역
	int N, M; //세로, 가로 크기


	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &r, &c, &rd);
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < M; k++)
		{
			scanf("%d", &map[i][k]);
		}
	}
	
	int cnt = 1; //해당 위치는 무조건 청소하는 것이므로 1로 시작
	int flag0 = 1; //청소 공간이 있으면 1로 바꾼다.
	int flag1 = 1;
	int flag2 = 1;
	int flag3 = 1;
	while (1)
	{
		map[r][c] = 2; //1.현재 위치를 청소한다.
		//2.현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
		//a.왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 
		//그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
		int tr = r;
		int tc = c;
		if (rd == 0) //북쪽이면 c--
		{
			tc--;
			if (tc > 0 && map[tr][tc] == 0) //청소할 수 있는 공간이면 좌표 이동
			{
				c = tc;  cnt++; flag0 = 1;
			}
			else
			{
				tc++; flag0 = 0;
			}
			rd = 3; //서쪽으로 (a, b 두경우 모두 방향은 바꿔야함)
		}
		else if (rd == 1) //동쪽이면 r--
		{
			tr--;
			if (tr > 0 && map[tr][tc] == 0) //청소할 수 있는 공간이면 좌표 이동
			{
				r = tr; cnt++; flag1 = 1;
			}
			else
			{
				tr++; flag1 = 0;
			}
			rd = 0; //북쪽으로
		}
		else if (rd == 2) //남쪽이면 c++
		{
			tc++;
			if (tc < M-1 && map[tr][tc] == 0) //청소할 수 있는 공간이면 좌표 이동
			{
				c = tc; cnt++; flag2 = 1;
			}
			else
			{
				tc--; flag2 = 0;
			}
			rd = 1; //동쪽으로
		}
		else if (rd == 3) //서쪽이면 r++
		{
			tr++;
			if (tr < N-1 && map[tr][tc] == 0) //청소할 수 있는 공간이면 좌표 이동
			{
				r = tr; cnt++; flag3 = 1;
			}
			else
			{
				tr--; flag3 = 0;
			}
			rd = 2; //남쪽으로
		}
		
		if(flag0==0 && flag1==0 && flag2==0 && flag3==0) //c.네 방향 모두 청소가 이미 되어있거는 경우
		{
			if (rd == 0) //북쪽이면
			{
				tr++;
				if (tr < N - 1 && map[tr][tc] != 1) //후진할 수 있으면 후진
				{
					r = tr; flag0 = flag1 = flag2 = flag3 = 1;
				}
				else //d. 후진도 못하는 경우 -> 작동을 멈춘다.
					break;
			}
			else if (rd == 1) //동쪽이면
			{
				tc--;
				if (tc > 0 && map[tr][tc] != 1)
				{
					c = tc; flag0 = flag1 = flag2 = flag3 = 1;
				}
				else
					break;
			}
			else if (rd == 2) //남쪽이면
			{
				tr--;
				if (tr > 0 && map[tr][tc] != 1)
				{
					r = tr; flag0 = flag1 = flag2 = flag3 = 1;
				}
				else
					break;
			}
			else if (rd == 3) //서쪽이면
			{
				tc++;
				if (tc < M - 1 && map[tr][tc] != 1)
				{
					c = tc; flag0 = flag1 = flag2 = flag3 = 1;
				}
				else
					break;
			}
		}
	}

	printf("%d\n", cnt);


	return 0;//Your program should return 0 on normal termination.
}


/*
우선 논리 구조는 while문으로 반복하게 하였고, 더 이상 갈 수 없으면(네 방향;동,서,남,북 모두 청소 or 벽) 
break;를 하여 while문을 빠져나가도록 하였다. 
그리고 while문 안에서는, 네 방향(사실은 문제에서 언급은 하지 않았지만, 
우선순위가 자신이 바라보는 방향의 왼쪽이므로, 반시계방향이다.)으로 

2-a. 왼쪽으로 갈 수 있으면 방향을 틀어 한칸을 가고, 
2-b.못간다면 왼쪽으로 방향만 틀고, 
2-c.네방향 다 못가면 후진할 수 있는지 여부를 체크해 후진하고, 
2-d.후진도 못한다면 break; 

이슈사항) 2-b와 2-c를 어떻게 구분할 것인가 (문제 파악)
사실 b와 c 모두 ‘못’가면이므로, 구분할 필요가 있다. 
다른점은 b는 네방향 중 한 방향에는 갈 수 있는 것, 즉 상하좌우중 청소가 안된 곳이 있는 경우다.
반면 c는 네방향 모두 청소가 되어있는 경우다. 
즉 현재 바라보고있는 곳에서 후진을 해야 한다. 
(이때 후진을 할 수 있는 경우가 c이고, 후진을 할 수 없는 경우가 d인 것이다.
현재 바라보고있는 방향에서 한칸 뒤로 갔을 때, 그곳이 벽이 아닌 경우다. 반면 d는 한칸 뒤로갔을 때 벽인 경우다.)
따라서 b에는 특별히 줄 조건은 없지만, c에는‘네방향 모두’ 청소가 되었는지 여부를 판단해야 하므로, flag를 두기로 하였다.

이슈사항2) flag 활용법
처음에는 flag를 하나만 두었더니‘네방향 모두’를 체크할 수 없어, 무한루프에 걸렸다. 
이에 flag를 flag0, flag1, flag2, flag3으로 두어, 지금 위치로부터 네방향 모두 청소를 했다면 
즉, if(flag0==0 && flag1==0 && flag2==0 && flag3==0)  //c.네 방향 모두 청소가 이미 되어있거는 경우 
이렇게 주어, 모두 0인 경우는 청소가 된 상황으로 설정하였다. 
이 if문 안에서 c와 d를 구분하였다.
*/
