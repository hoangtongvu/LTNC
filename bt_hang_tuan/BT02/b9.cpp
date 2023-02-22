#include <iostream>
#include <math.h>


using namespace std;

int main()
{
	int inputNum;
	cin >> inputNum;

	int sum = 0;

	int temp = inputNum;

	while (temp != 0)
	{
		sum += temp % 10;
		temp /= 10;
	}

	cout << sum;




	return 0;
}

