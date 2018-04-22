#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "OrderBook.h"

using namespace std;


int main()
{
    int start_s=clock();
    OrderBook OB;
    OB.ReadFile();
    int stop_s=clock();
    cout << "Execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)<< endl;

    return 0;
}
