#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>
#include "Test.h"
#include <vector>

using namespace std;



void DeQuy(string s, char res[], int sLength, int count)
{

	for (int i = 0; i < sLength; i++)
	{
		if (count < sLength)
		{
			res[count] = s[i];
			DeQuy(s, res, sLength, count + 1);
		}
		else
		{
			bool check = true;
			for (int i = 0; i < sLength - 1; i++)
			{
				for (int j = i + 1; j < sLength; j++)
				{
					if (res[i] == res[j])
					{
						check = false;
					}
				}
			}

			if (check)
			{
				for (int i = 0; i < sLength; i++)
				{
					cout << res[i];
				}
				cout << endl;
			}
		}
	}
}


void reverse(char a[])
{
	int length = 0;
	for (int i = 0; a[i] != '\0'; i++)
	{
		length++;
	}
	for (int i = 0; i < length / 2; i++)
	{
		char temp = a[i];
		a[i] = a[length - i - 1];
		a[length - i - 1] = temp;
	}

}




int main()
{
	char a[] = "abcasd";
	int length = sizeof(a) / sizeof(a[0]);
	cout << a << endl;

	reverse(a);
	cout << a << endl;


	return 0;

}



