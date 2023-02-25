#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;




void swapNum(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int n;
	cin >> n;
	string* arr = new string[n];
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}


	for (int i = 0; i < n - 1; i++)
	{
		int firstLength = arr[i].length();
		for (int j = i + 1; j < n; j++)
		{
			int secondLength = arr[j].length();
			if (firstLength == secondLength)
			{
				bool check = true;
				for (int k = 0; k < firstLength; k++)
				{
					if (arr[i][k] != arr[j][firstLength - k - 1])
					{
						check = false;
					}
				}
				if (check)
				{
					cout << firstLength << " " << arr[i][firstLength / 2];
				}
			}
		}
	}





	return 0;
}



