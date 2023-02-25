#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;




void swapNum(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int n;
	cin >> n;

	int* arrNam = new int[n];
	int* arrNu = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> arrNam[i] >> arrNu[i];
	}

	//Ascending sort

	bool haveSwap = false;
	//Nam
	for (int i = 0; i < n - 1; i++) 
	{

		haveSwap = false;


		for (int j = 0; j < n - i - 1; j++) 
		{
			if (arrNam[j] > arrNam[j + 1]) 
			{
				swapNum(arrNam[j], arrNam[j + 1]);
				haveSwap = true;
			}
		}


		if (haveSwap == false) 
		{
			break;
		}
	}

	//Nu
	for (int i = 0; i < n - 1; i++) 
	{

		haveSwap = false;


		for (int j = 0; j < n - i - 1; j++) 
		{
			if (arrNu[j] > arrNu[j + 1]) 
			{
				swapNum(arrNu[j], arrNu[j + 1]);
				haveSwap = true;
			}
		}


		if (haveSwap == false) 
		{
			break;
		}
	}

	bool check = true;
	for (int i = 0; i < n; i++)
	{
		if (arrNam[i] < arrNu[i])
		{
			check = false;
		}
	}
	
	if (check)
	{
		cout << "yes";
	}
	else
	{
		cout << "no";
	}


	return 0;
}



