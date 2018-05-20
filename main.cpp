#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "OrderBook.h"
#include "Utilities.h"

using namespace std;
int main()
{

    int a;
    cout<<"Which type of Data Structure you want to Use:\n For Heap please enter 1\n For Treap please enter 2 \n For Red_Black Tree please enter 3"<<endl;
    cin>>a;
    if(a<1 || a>3)
    {
         cout<<"None of three types selected"<<endl;
         return 0;
    }
    int start_s=clock();
    OrderBook* OB = new OrderBook(a);
    OB->ReadFile();
    int stop_s=clock();
    cout << "Execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)<< endl;

    delete OB;
    return 0;
}
