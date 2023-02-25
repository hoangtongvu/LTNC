#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;




int main()
{
	int n;
	cin >> n;
	
	int* arr = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	for (int i = 0; i <= 9; i++)
	{
		int countNum = 0;
		for (int j = 0; j < n; j++)
		{
			if (arr[j] == i)
			{
				countNum++;
			}
		}
		cout << i << ": " << countNum << endl;
		countNum = 0;

	}



	return 0;
}
