#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;


void DeQuy(int arr[], int n, int kOrigin, int k)
{
	//int* arr = new int[kOrigin];
	for (int i = 97; i < 97 + n; i++)
	{
		arr[k - 1] = i;
		if (k != 1)
		{
			DeQuy(arr, n, kOrigin, k - 1);

		}
		else
		{
			for (int j = 0; j < kOrigin; j++)
			{
				cout << char(arr[kOrigin - j - 1]);
			}
			cout << " ";
		}
		
	}


	

	
}




int main()
{
	int n, k;
	cin >> n >> k;
	int* arr = new int[k];
	DeQuy(arr, n, k, k);

	/*for (int i = 97; i < n + 97; i++)
	{
		cout << char(i);
		for (int j = 97; j < n + 97; j++)
		{
			cout << char(j);
			for (int k = 97; k < n + 97; k++)
			{
				cout << char(k) << " ";
			}
		}
	}*/

	


	return 0;
}



