#include <iostream>
#include <math.h>
#include <string.h>


using namespace std;

int main()
{
    int amount;
    cin >> amount;
    int Array[amount];
    cin >> Array[0];
    int maxValue = Array[0];
    int minValue = Array[0];
    double sum = Array[0];
    for (int i = 1; i < amount; i++)
    {
        cin >> Array[i];
        if (maxValue < Array[i])
            maxValue = Array[i];
        if (minValue > Array[i])
            minValue = Array[i];
        sum += Array[i];
    }
    cout << sum / amount << endl;
    cout << maxValue << endl;
    cout << minValue << endl;




    return 0;
}
