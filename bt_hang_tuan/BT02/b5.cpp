#include <iostream>
#include <math.h>


using namespace std;

int main()
{
	int x, y;
	cin >> x >> y;
	
	int ucln = x;
	
	for (int i = ucln; i >= 1; i--)
	{
		if (x % i == 0 && y % i == 0)
		{
			ucln = i;
			break;
		}
	}

	cout << ucln;









	return 0;
}

