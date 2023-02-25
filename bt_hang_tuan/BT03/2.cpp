#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>

using namespace std;





int main()
{
	string inputString;
	cin >> inputString;

	int n = inputString.length();
	bool check = true;
	for (int i = 0; i < n / 2; i++)
	{
		if (inputString[i] != inputString[n - i - 1])
		{
			check = false;
		}
	}
	if (check)
	{
		cout << "yes";
	}
	else
	{
		cout << "no";
	}




	return 0;
}
