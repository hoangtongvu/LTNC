#include <iostream>
#include <math.h>
#include <string.h>


using namespace std;

int main()
{
    string f0 = "a";
    string f1 = "b";
    cout << f0 << endl << f1  << endl;
    for (int i = 0; i < 8; i++)
    {
        f0 = f1 + f0;
        cout << f0 << endl;
        string temp = f1;
        f1 = f0;
        f0 = temp;

    }




    return 0;
}
