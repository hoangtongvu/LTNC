#include <iostream>
#include <math.h>


using namespace std;

int main()
{
	int inputNum;
	cin >> inputNum;
	
	for (int y = 0; y < inputNum; y++)
	{
		for (int x = 1 - inputNum; x <= inputNum - 1; x++)
		{
			if ( (x > y - inputNum) && (x < inputNum - y) )
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}












	return 0;
}

