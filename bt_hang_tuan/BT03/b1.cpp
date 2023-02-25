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
	int max, min, sumEvenNum = 0, countOddNum = 0;
	bool initMaxMin = false;

	for (int i = 0; i < n; i++)
	{
		int input;
		cin >> input;
		if (!initMaxMin)
		{
			max = input;
			min = input;
			initMaxMin = true;
		}

		if (max < input)
		{
			max = input;
		}
		if (min > input)
		{
			min = input;
		}
		if (input % 2 == 0)
		{
			sumEvenNum += input;
		}
		else
		{
			countOddNum++;
		}
		
	}


	cout << min << " " << max << " " << sumEvenNum << " " << countOddNum;




	return 0;
}
