#include <iostream>
#include <thread>
#include <chrono>



using namespace std;

void RenderGame()
{
	//cout << "ngu";
    int i = 0;
    while (i < 100)
    {

        cout << i++ << " ";
        this_thread::sleep_for(chrono::milliseconds(500));
    }

}