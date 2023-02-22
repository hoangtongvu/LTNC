#include <iostream>
#include <math.h>


using namespace std;

int main()
{
	int inputNum;
	cin >> inputNum;
	bool isPrime = true;
	if (inputNum >= 2)
	{
		for (int i = 2; i <= sqrt(inputNum); i++)
		{
			if (inputNum % i == 0)
			{
				isPrime = false;
			}
		}

	}
	else
	{
		isPrime = false;
	}


	if (isPrime)
	{
		cout << "yes";
	}
	else
	{
		cout << "no";
	}
}

