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
	int* arrB = new int[n];
	
	//arr = { 1, 2, 3, 4, 5 };


	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		arrB[i] = 0;
	}

	int k = 0;
	bool check = false;

	for (int i = 0; i < n; i++)
	{
		bool checkSeen = false;
		for (int j = 0; j < n; j++)
		{
			if (arr[i] == arrB[j])
			{
				checkSeen = true;
				check = true;
				cout << "yes";
				break;
			}		
		}

		if (!checkSeen)
		{
			arrB[k] = arr[i];
			k++;
		}
	}

	if (!check)
	{
		cout << "no";
	}

	return 0;
}
