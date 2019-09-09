#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	int N, K;
	scanf("%d %d",&N,&K);

	if(K < 5) //읽을 수 없음
	{
		printf("0\n");
		return 0;
	}

	vector<char> word; //배워야할 단어(a,c,i,n,t => 5개 빼고)
	string *s = new string[N];
	for(int n=0 ; n<N ; n++)
	{
		cin >> s[n];

		for(int i=4 ; i<s[n].size()-4 ; i++)
		{
			if(s[n][i]!='a' && s[n][i]!='c' && s[n][i]!='i' && s[n][i]!='n' && s[n][i]!='t')
			{
				for(int j=0 ; j<word.size() ; j++) //중복이 안되게
				{
					if(s[n][i] == word[j])
						goto A;
				}
				word.push_back(s[n][i]);
			}
			A: ;
		}
	}

	int word_size = word.size();
	if(word_size <= K-5) //다 읽을 수 있음
	{
		printf("%d\n",N);
		return 0;
	}

	/*for(int i=0 ; i<word.size() ; i++)
		printf("%c ",word[i]);
	printf("\n");*/

	vector<int> ind;
	for(int i=1 ; i<=K-5 ; i++)
		ind.push_back(1);
	for(int i=1 ; i<=word_size-(K-5) ; i++)
		ind.push_back(2);

	int CNT = 0; //읽을 수 있는 단어의 개수 (최대)
	do
	{
		/*for(int i=0 ; i<ind.size() ; i++)
			printf("%d ",ind[i]);
		printf("\n");*/

		int abc[26] = {1,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0}; //해당 단어를 읽을 수 있는지 여부
		for(int i=0 ; i<word_size ; i++)
		{
			if(ind[i] == 1)
			{
				abc[word[i]-'a'] = 1; //읽을 수 있으면 1로
				//printf("i : %d, word[i]-'a' : %d\n",i,word[i]-'a');
			}
		}
		int cnt = 0;
		for(int n=0 ; n<N ; n++) //N개의 단어
		{
			for(int k=0 ; k<s[n].size() ; k++)
			{
				if(abc[s[n][k]-'a'] == 0)
					goto B;
			}
			cnt++;
			B: ;
		}
		if(CNT < cnt)
			CNT = cnt;

	}while(next_permutation(ind.begin(),ind.end()));


	printf("%d\n",CNT);


	return 0;
}

/*
26개의 알파벳 중, anta 와 tica 에 해당하는 a, c, i, n, t 이 5개는 필수로 배워야 하는 알파벳이다.
1) 따라서, 배우는 알파벳 수 K가 5보다 작다면, 단어를 아예 배울 수 없으므로 0을 출력하고 종료했다.
2) 배울 수 있는 알파벳이 5개 이상이면, 넥스트퍼뮤테이션 함수를 이용해, 조합을 만들어내고, 해당 조합으로 배울 수 있는 단어의 개수를 카운트한다.
이를 위해, 위 5개의 알파벳을 제외하고 각 단어마다 배워야 하는 알파벳을 체크했다. 예를 들어,
anta rc tica     => r 을 배워야 한다.
anta hello tica  => e, h, l, o를 배워야 한다. 
anta car tica    => r 을 배워야 한다.
새로 배워야 하는 알파벳을 벡터에 넣고, 조합을 만들었고, 해당 조합으로 읽을 수 있는 단어의 개수를 최댓값이 되도록 업데이트 해나갔다.
*/
