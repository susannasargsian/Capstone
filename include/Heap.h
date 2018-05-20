#ifndef HEAP_H
#define HEAP_H

#include "Base.h"
#include "Data.h"
#include "Utilities.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>



class Heap: public Base
{

public:
    Heap(){};
    virtual ~Heap(){};
    void insert(Data);
    void remove(const Data&);
    void update(Data,Data);

    Data getMax(){return Data();}
    Data getMin(){return Data();}

    void bubbleDownFD(const Data& d, int f);
    std:: vector<Data> storage;
    int getSize();
    void getTitle();


protected:
    Data getTop ();
    int find(const Data& d);
    virtual void bubbleUp(){};
    virtual void bubbleDown(){};
    void swap(int child, int parent);
    int getLeftChild(int parent);
    int getRightChild(int parent);
    int getParent(int child);

};

class MaxHeap : public Heap
{

public:
    MaxHeap(): Heap(){};
    virtual ~MaxHeap(){};
    Data getMax();
private:
    virtual void bubbleUp();
    virtual void bubbleDown();


};

class MinHeap : public Heap
{

public:
    MinHeap():Heap(){};
    virtual ~MinHeap(){};
    Data getMin();
private:
    virtual void bubbleUp();
    virtual void bubbleDown();

};




#endif // HEAP_H
