#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "OrderBook.h"
#include "Utilities.h"
#include "RedBlackTree.h"


using namespace std;


int main()
{


    int a;
    cout<<"Which type of Data Structure you want to Use:\n "
        <<"For Heap please enter 1\n For Treap please enter 2 \n For Red-Black Tree please enter 3 \n "<<endl;
    cin>>a;
    if(a<1 || a>3)
    {
         cout<<"None of three types selected"<<endl;
         return 0;
    }
    OrderBook* OB = new OrderBook(a);
    OB->ReadFile();
    delete OB;
    return 0;
}
