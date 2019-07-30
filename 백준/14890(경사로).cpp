#include <iostream>
#include <queue>

using namespace std;


int main(int argc, char** argv)
{
	int N, L;
	scanf("%d %d", &N, &L);

	int map[100][100];
	for (int i=0 ; i<N ; i++)
	{
		for (int k = 0; k < N; k++)
		{
			scanf("%d", &map[i][k]);
		}
	}

	
	int cnt = 0; //지나갈 수 있는 길의 개수

	//가로줄 경로를 체크한다.
	for (int i = 0; i < N; i++) 
	{
		int temp[100] = { 0 }; //경사로를 설치하면 1로
		int p1 = 0;
		int p2 = 1;
		
		int road = 1; //지나갈 수 있는지 최종 여부
		while (p2 <= N-1)
		{
			if (map[i][p1] == map[i][p2]) //그냥 지나갈 수 있는 경우
			{
				p1++; p2++;
			}
			//그냥 이동할 수 없는 경우
			else
			{
				if (map[i][p1] - map[i][p2] == 1) //내려가는 경사로를 설치할 수 있는 경우
				{
					int flag = 1; //경사로를 설치할 수 있는 경우가 1
					for (int l = 1; l < L; l++)
					{
						if (map[i][p2] != map[i][p2 + l])
						{
							flag = 0;
						}
					}
					if (flag) //경사로 설치
					{
						for (int t = 0; t < L; t++)
						{
							if (temp[p2 + t] != 1) //아직 설치되어 있지 않은 곳이면 설치
							{
								temp[p2 + t] = 1;
							}
							else //이미 경사로가 설치되어 있는 곳이면 설치할 수 없다 -> 지나갈 수 없음이 확정됨
							{
								road = 0;  break;
							}
						}
						p1 += L; p2 += L;
					}
					else //경사로 설치 불가 -> 지나갈 수 없음이 확정됨
					{
						road = 0;  break;
					}
				}
				else if (map[i][p1] - map[i][p2] == -1) //올라가는 경사로를 설치할 수 있는 경우
				{
					int flag = 1; //경사로를 설치할 수 있는 경우가 1
					for (int l = 1; l < L; l++)
					{
						if (map[i][p1] != map[i][p1 - l])
						{
							flag = 0;
						}
					}
					if (flag) //경사로 설치
					{
						for (int t = 0; t < L; t++)
						{
							if (temp[p1 - t] != 1) //아직 설치되어 있지 않은 곳이면 설치
							{
								temp[p1 - t] = 1;
							}
							else //이미 경사로가 설치되어 있는 곳이면 설치할 수 없다 -> 지나갈 수 없음이 확정됨
							{
								road = 0;  break;
							}
						}
						p1 ++; p2 ++;
					}
					else //경사로 설치 불가 -> 지나갈 수 없음이 확정됨
					{
						road = 0;  break;
					}
				}
				else //경사로도 설치할 수 없는 경우 -> 지나갈 수 없음이 확정됨
				{
					road = 0;  break;
				}
			}

		}

		if (road) 
		{ 
			cnt++; 
			//printf("i = %d\n", i); 
		}
	}


	//세로줄 경로를 체크한다.
	for (int i = 0; i < N; i++)
	{
		int temp[100] = { 0 }; //경사로를 설치하면 1로
		int p1 = 0;
		int p2 = 1;

		int road = 1; //지나갈 수 있는지 최종 여부
		while (p2 <= N - 1)
		{
			if (map[p1][i] == map[p2][i]) //그냥 지나갈 수 있는 경우
			{
				p1++; p2++;
			}
			//그냥 이동할 수 없는 경우
			else
			{
				if (map[p1][i] - map[p2][i] == 1) //내려가는 경사로를 설치할 수 있는 경우
				{
					int flag = 1; //경사로를 설치할 수 있는 경우가 1
					for (int l = 1; l < L; l++)
					{
						if (map[p2][i] != map[p2 + l][i])
						{
							flag = 0;
						}
					}
					if (flag) //경사로 설치
					{
						for (int t = 0; t < L; t++)
						{
							if (temp[p2 + t] != 1) //아직 설치되어 있지 않은 곳이면 설치
							{
								temp[p2 + t] = 1;
							}
							else //이미 경사로가 설치되어 있는 곳이면 설치할 수 없다 -> 지나갈 수 없음이 확정됨
							{
								road = 0;  break;
							}
						}
						p1 += L; p2 += L;
					}
					else //경사로 설치 불가 -> 지나갈 수 없음이 확정됨
					{
						road = 0;  break;
					}
				}
				else if (map[p1][i] - map[p2][i] == -1) //올라가는 경사로를 설치할 수 있는 경우
				{
					int flag = 1; //경사로를 설치할 수 있는 경우가 1
					for (int l = 1; l < L; l++)
					{
						if (map[p1][i] != map[p1 - l][i])
						{
							flag = 0;
						}
					}
					if (flag) //경사로 설치
					{
						for (int t = 0; t < L; t++)
						{
							if (temp[p1 - t] != 1) //아직 설치되어 있지 않은 곳이면 설치
							{
								temp[p1 - t] = 1;
							}
							else //이미 경사로가 설치되어 있는 곳이면 설치할 수 없다 -> 지나갈 수 없음이 확정됨
							{
								road = 0;  break;
							}
						}
						p1++; p2++;
					}
					else //경사로 설치 불가 -> 지나갈 수 없음이 확정됨
					{
						road = 0;  break;
					}
				}
				else //경사로도 설치할 수 없는 경우 -> 지나갈 수 없음이 확정됨
				{
					road = 0;  break;
				}
			}

		}

		if (road)
		{
			cnt++;
			//printf("i = %d\n", i); 
		}
	}

	printf("%d\n", cnt);


	return 0;//Your program should return 0 on normal termination.
}

/*
우선 2가지 상황 + 3가지 경우로 분류하였다. 한 칸을 이동했을 때,
1) 높이가 같아서 이동할 수 있는 경우.
2) 높이가 같지 않아 바로는 이동할 수 없는 경우.
이 때, 2)같은 경우는 사다리 설치 가능 여부를 따져봐야 이동할 수 있는지 알 수 있다.
   1) 내려가는 사다리를 설치할 수 있는 경우
   2) 올라가는 사다리를 설치할 수 있는 경우
   3) 사다리를 설치할 수 없는 경우
로 나눌 수 있으며, 1)번과 2)번에서도, 설치할 수 있을지라도, 이전에 이미 설치하였으면, 새롭게 설치할 수는 없다.
따라서, 사다리를 설치하면 설치했다고 표시할 배열이 따로 필요하다. 이 점을 생각하여,  다소 쉽게 접근할 수 있었다.
+ ) 경로는 가로줄과 세로줄이 있다. 
따라서 가로줄만 먼저 코드를 작성하고, 이를 복붙하여 세로줄도 검사할 수 있는 형식으로 작성하였다.
*/
