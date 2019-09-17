#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
	int N;
	scanf("%d",&N);

	int hit[51][10]; //1이닝~50이닝, 1번~9번 결과
	for(int i=1 ; i<=N ; i++)
	{
		for(int k=1 ; k<=9 ; k++)
			scanf("%d",&hit[i][k]);
	}

	vector<int> v; //타순(1번 제외, 1번은 무조건 4번이므로)
	for(int i=2 ; i<=9 ; i++)
		v.push_back(i); //8명 => 순열

	int lineup[10] = {0,  0,0,0,1,0,0,0,0,0};
	int score = 0;
	do
	{
		for(int i=0 ; i<=2 ; i++)
			lineup[i+1] = v[i];
		for(int i=3 ; i<=7 ; i++)
			lineup[i+2] = v[i];
		/*for(int i=1 ; i<=9 ; i++)
			printf("%d ",lineup[i]);
		printf("\n");*/

		int cnt = 0;
		int ind = 1; //현재 타자의 인덱스, 1번부터 시작
		for(int inning=1 ; inning<=N ; inning++)
		{
			//printf("%d이닝\n",inning);
		    int out = 0;
			int base[4] = {0}; //1루~3루
			while(1)
			{
				int x = lineup[ind]; //현재 타자 (등)번호
				int result = hit[inning][x];
				switch(result)
				{
				case 0: //out
					out++; 
					break;
				case 1: //1루타
					if(base[3] == 1) //3루주자 득점
					{
						cnt++;
						base[3] = 0;
					}
					for(int i=2 ; i>=1 ; i--)
					{
						if(base[i] == 1)
						{
							base[i+1] = 1;
							base[i] = 0;
						}
					}
					base[1] = 1;
					break;
				case 2: //2루타
					for(int i=2 ; i<=3 ; i++) //2,3루주자 득점
					{
						if(base[i] == 1)
						{
							cnt++;
							base[i] = 0;
						}
					}
					if(base[1] == 1)
					{
						base[3] = 1;
						base[1] = 0;
					}
					base[2] = 1;
					break;
				case 3: //3루타
					for(int i=1 ; i<=3 ; i++) //주자는 모두 득점
					{
						if(base[i] == 1)
						{
							cnt++;
							base[i] = 0;
						}
					}
					base[3] = 1; //타자주자 3루까지 진루
					break;
				case 4: //홈런
					for(int i=1 ; i<=3 ; i++) //1루~3루 확인
					{
						if(base[i] == 1)
						{
							cnt++;
							base[i] = 0;
						}
					}
					cnt++; //본인도 들어옴
					break;
				}
				ind++;
				if(ind == 10)
					ind = 1;

				if(out == 3)
					break;
			}
		}
		if(score < cnt)
			score = cnt;
		//printf("score : %d, cnt : %d\n",score,cnt);

	}while(next_permutation(v.begin(), v.end()));


	printf("%d\n",score);


	return 0;
}

/*
1번 선수는 4번 타자로 확정이 되었으므로, 2번부터 9번 선수를 넥스퍼뮤테이션 함수를 이용해서, 순열을 생성한다. 
순열에서의 순서대로 1번~3번, 5번~9번 타자로 배정한 후, 시뮬레이션을 한다.

이슈사항) 런타임에러
야구는 9이닝까지 있어서, hit 배열을 [10]개 선언했지만, 런타임에러가 발생했다.
문제를 다시 읽어보니, 이닝이 50까지 있을 수 있으므로, [51]을 선언하여 런타임에러를 해결하였다.
*/
