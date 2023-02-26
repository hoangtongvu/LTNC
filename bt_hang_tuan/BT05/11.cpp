#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;




string ThapPhan_NhiPhan(int n)
{
	string s;
	while (n != 0)
	{
		int r = n % 2;
		s += to_string(r);
		n /= 2;
	}
	s += to_string(n);
	n = s.length();
	for (int i = 0; i < n / 2; i++)
	{
		char temp = s[i];
		s[i] = s[n - i - 1];
		s[n - i - 1] = temp;
	}
	return s;
}



int main()
{
	int n;
	cin >> n;

	cout << ThapPhan_NhiPhan(n);





	return 0;
}



