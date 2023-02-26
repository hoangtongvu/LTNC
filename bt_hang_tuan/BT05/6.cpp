#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;


int UCLN(int a, int b)
{
	while (b != 0)
	{
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}





int main()
{
	int a, b;
	cin >> a >> b;

	if (UCLN(a, b) == 1)
	{
		cout << a << " va " << b << " la 2 so nguyen to cung nhau";
	}
	else
	{
		cout << a << " va " << b << " khong la 2 so nguyen to cung nhau";

	}
	





	return 0;
}



