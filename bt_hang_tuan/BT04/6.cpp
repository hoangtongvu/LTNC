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
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}


	for (int i = 0; i < n - 2; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (i < j && j < k)
				{
					if (arr[i] + arr[j] + arr[k] == 0)
					{
						cout << arr[i] << " " << arr[j] << " " << arr[k] << endl;
					}
				}

			}
		}
	}




	return 0;
}



