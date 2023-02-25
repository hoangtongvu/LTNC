#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;




int main()
{
	string input;
	cin >> input;
	int n = input.length();

	for (int i = 0; i < n; i++)
	{
		
		for (int j = 0; j < n; j++)
		{
			cout << input[i] << input[j] << " ";
			for (int k = 0; k < n; k++)
			{
				cout << input[i] << input[j] << input[k] << " ";
			}
		}
	}



	return 0;
}
