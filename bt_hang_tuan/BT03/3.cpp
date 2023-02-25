#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;





int main()
{
	

	int A, B;
	cin >> A >> B;
	int counter = 0;
	for (int i = A; i <= B; i++)
	{
		
		
		string tempString = to_string(i);
		int n = tempString.length();
		bool check = true;
		for (int j = 0; j < n / 2; j++)
		{
			if (tempString[j] != tempString[n - j - 1])
			{
				check = false;
			}
		}
		if (check)
		{
			counter++;
		}
	}
	

	cout << counter;

	return 0;
}
