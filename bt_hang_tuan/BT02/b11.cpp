#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main()
{
	int min, max, stepSize;
	cin >> min >> max >> stepSize;

	cout << "Fahrenheit     Celsius     Absolute Value" << endl;
	for (int i = min; i <= max; i += stepSize)
	{
		cout << setw(10) << i << "     ";
		cout << setw(7) << setprecision(1) << fixed << (float)(i - 32) * 5 / 9 << "     ";
		cout << setw(14) << setprecision(1) << fixed << (float)(i - 32) * 5 / 9 + 273.15 << endl;

	}
	





	return 0;
}

