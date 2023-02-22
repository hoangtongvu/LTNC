#include <iostream>
#include <math.h>


using namespace std;

int main()
{
	int x, y;
	cin >> x >> y;
	
	int bcnn = x;
	while (bcnn % x != 0 || bcnn % y != 0)
	{
		bcnn++;

	}
	cout << bcnn;









	return 0;
}

