#include <iostream>
#include <string>
#include <list>

using namespace std;


int main(int argc, char** argv)
{
	int N;
	scanf("%d",&N);

	for(int loop=0 ; loop<N ; loop++)
	{
		string s;
		cin >> s;

		list<char> pw;
		list<char>::iterator it = pw.begin();

		for(int i=0 ; i<s.size() ; i++)
		{
			char temp = s[i];
			switch(temp)
			{
			case '<' :
				if(it != pw.begin())
					it--;
				break;
			case '>' :
				if(it != pw.end())
					it++;
				break;
			case '-' :
				if(it != pw.begin())
				{
					it--;
					it = pw.erase(it); //it에 다시 대입해줘야!
				}
				break;
			default :
				pw.insert(it, temp);
			}
		}

		for(it = pw.begin() ; it!=pw.end() ; it++)
			printf("%c",*it);
		printf("\n");
	}

	return 0;
}

/*
처음에는 벡터로 했지만, 시간초과가 발생했다. 
이유는 벡터는 메모리를 연속적인 공간에 할당하여, 배열과 마찬가지로, 
삽입/삭제 연산이 일어날 때, 원소들의 이동이 하나하나씩 일어나기 때문이다.
따라서 이 문제에서는 리스트를 사용하였다.
리스트는 각 원소들이 포인터로 가리키며 연결되어있기 때문에, 삽입/삭제 시 매우 빠르다는 장점이 있다.

이슈사항1) 리스트에 insert 함수
list<char>::iterator it = pw.begin();

pw.insert(it, temp);
insert함수는 it이 가리키는 곳에 temp값을 갖는 원소를 삽입한다. 
그 후, it은 삽입 후 다음 위치를 가리키므로, 따로 ++을 해 줄 필요가 없다.

이슈사항2) 리스트에 erase 함수
it = pw.erase(it); //it에 다시 대입해줘야!
erase함수는 해당 위치의 원소를 삭제 후, 그 위치를 반환한다. 따라서 반환값을 다시 it 이터레이터에 받아와야 한다.
*/
