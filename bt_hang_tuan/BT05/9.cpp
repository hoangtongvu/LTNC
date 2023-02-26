#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;




int RandomNum(int n)
{
	return rand() % n;
}




int main()
{
	int n;
	cin >> n;

	cout << RandomNum(n);





	return 0;
}



