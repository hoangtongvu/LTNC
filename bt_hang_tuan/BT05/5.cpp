#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;


int IsPrime(int n)
{
	if (n == 1)
	{
		return 0;
	}
	int check = 1;
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			check = 0;
		}
	}
	return check;
}


int main()
{
	int n;
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		if (IsPrime(i) == 1)
		{
			cout << i << " ";
		}
	}





	return 0;
}



