#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
	//int N = 12, M = 6;
	string map[12];
	for(int i=0 ; i<12 ; i++)
	{
		cin >> map[i];
	}

	int cnt = 0; //몇 연쇄가 일어나는지
	int flag = 1; //더이상 터질 것이 없으면 0으로
	while(flag)
	{
		flag = 0;

		int visited[12][6] = {0};
		int dx[4] = {1,-1,0,0};
		int dy[4] = {0,0,1,-1};
		for(int i=0 ; i<12 ; i++)
		{
			for(int k=0 ; k<6 ; k++)
			{
				if(map[i][k] != '.' && visited[i][k] == 0) //알파벳인데 아직 방문을 안했다면
				{
					queue<pair<int,int> > puyo;
					queue<pair<int,int> > temp;
					visited[i][k] = 1;

					puyo.push(pair<int,int>(i,k));
					temp.push(pair<int,int>(i,k));

					while(!temp.empty())
					{
						int x = temp.front().first;
						int y = temp.front().second;

						temp.pop();
						char tp = map[i][k];
						for(int q=0 ; q<4 ; q++)
						{
							int tx = x + dx[q];
							int ty = y + dy[q];
							if(tx<0 || tx>=12 || ty<0 || ty>=6)
								continue;

							if(map[tx][ty] == tp && visited[tx][ty] == 0) //같은색이고 아직 방문을 안했다면
							{
								visited[tx][ty] = 1;
								puyo.push(pair<int,int>(tx,ty));
								temp.push(pair<int,int>(tx,ty));
							}
						}
					}
					//cout << "뿌요 사이즈 : " << puyo.size() << endl;
					if(puyo.size() >= 4) //4개이상 모이면 터진다
					{ 
						flag = 1;
						while(!puyo.empty())
						{
							int tx = puyo.front().first;
							int ty = puyo.front().second;
							puyo.pop();
							//cout << "터지는 색 : " << map[tx][ty];
							//cout << " / 위치 : " << tx << ", " << ty << endl;
							map[tx][ty] = '.';
						}//cout << endl;
					}
				}
			}
		}

		if(flag) //터지고, 맵을 재정비해야
		{
			cnt++;

			for(int b=0 ; b<6 ; b++)
			{
				string temp_array;
				for(int a=11 ; a>=0 ; a--)
				{
					if(map[a][b] != '.')
					{
						temp_array.push_back(map[a][b]);
					}
				}
				int temp_ind = 0;
				for(int a=11 ; a>11-temp_array.size() ; a--)
				{
					map[a][b] = temp_array[temp_ind];
					temp_ind++;
				}
				for(int a=11-temp_array.size() ; a>=0 ; a--)
				{
					map[a][b] = '.';
				}
			}
			/*cout << "cnt : " << cnt << endl;
			for(int a=0 ; a<12 ; a++)
			{
				cout << map[a] << endl;
			}cout << endl;*/
		}

	}

	cout << cnt << endl;

	return 0;//Your program should return 0 on normal termination.
}

/*
뿌요 4개가 뭉쳐져 있는지를 확인해야 하는 BFS 문제이다.
크게 3단계로 생각했다.
1) 뿌요가 뭉쳐져 있는 개수를 찾는다. => BFS
2) 뿌요가 4개이상이 모여있다면 터뜨린다.
3) 터뜨렸으면, 맵을 재정비한다.

이슈사항) for문에 큐의 사이즈를 이용하는 것은 위험
for(int i =0 ; i<puyo.size() ; i++) puyo.pop(); 과 같이 사용하면,, 팝되는데 큐의 사이즈가 고정적이지가 않다! 
따라서 처음에 원하는 만큼 for문이 실행되지 않는다,,
while(!puyo.empty()) puyo.pop();
과 같이 써야 큐의 원소만큼 실행되게 된다.
*/
