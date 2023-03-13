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


void delete_char(char* a, char c)
{
	int length = 0;
	for (int i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != c)
		{
			length++;
		}
	}
	char* b = new char[length + 1];
	int count = 0;
	for (int i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != c)
		{
			*(b + count) = a[i];
			count++;
		}
	}
	
	for (int i = 0; i < count; i++)
	{
		*(a + i) = *(b + i);
	}
	a[count] = '\0';
	delete[] b;
	
}




int main()
{
	char a[] = "abcasd";
	char c = 'a';
	int length = sizeof(a) / sizeof(a[0]);
	cout << a << endl;

	delete_char(a, c);
	cout << a << endl;


	return 0;

}



