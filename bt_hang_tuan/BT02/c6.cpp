#include <iostream>
#include <math.h>


using namespace std;

int main()
{
	int inputNum;
	cin >> inputNum;
	
	for (int i = 1; i <= inputNum; i++)
	{
		for (int j = i; j <= inputNum; j++)
		{
			cout << j << " ";
		}
		for (int j = 1; j <= i - 1; j++)
		{
			cout << j << " ";
		}
		cout << endl;
	}











	return 0;
}

