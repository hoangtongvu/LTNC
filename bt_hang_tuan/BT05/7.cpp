#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;




void PrintStar(int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		cout << " ";
	}
	for (int i = 0; i < n; i++)
	{
		cout << "*";
	}
	cout << endl;
}




int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		PrintStar(n - i - 1, i * 2 + 1);
	}





	return 0;
}



