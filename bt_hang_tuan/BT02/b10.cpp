#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main()
{
	int inputNum;
	cin >> inputNum;

	cout << "Fahrenheit     Celsius     Absolute Value" << endl;
	cout << setw(10) << inputNum << "     ";
	cout << setw(7) << setprecision(1) << fixed << (float)(inputNum - 32) * 5 / 9 << "     ";
	cout << setw(14) << setprecision(1) << fixed << (float)(inputNum - 32) * 5 / 9 + 273.15;
	





	return 0;
}

