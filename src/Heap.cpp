#include "Heap.h"

 int Heap:: getSize()
{
  return storage.size();
}

void Heap:: getTitle()
{
    std::cout<<"Heap\n\n"<<std::endl;
}

void Heap::swap(int child, int parent)
{
  Data temp;
  temp = storage[child];
  storage[child] = storage[parent];
  storage[parent] = temp;
}


int Heap:: getParent(int child)
{
  if (child % 2 == 0)
	return (child /2 ) -1;
  else
	return child/2;

}


int Heap:: getLeftChild(int parent)
{
  return 2*parent +1;
}


int Heap:: getRightChild(int parent)
{
  return 2 * parent + 2;
}


void Heap:: insert(Data value)
{
  storage.push_back(value);
  bubbleUp();
}

void Heap:: update(Data old_d, Data new_d)
{
    remove(old_d);
    insert(new_d);
}

Data Heap:: getTop()
{
    return storage[0];
}

int Heap :: find(const Data& d)
{
    size_t i;
    for(i=0; i<storage.size(); i++)
    {
        if (d==storage[i])
        {
             break;
        }

    }
    if(i!=storage.size())
    {
        return i;
    }
    else
    {
        return -1;
    }

}

 void Heap:: bubbleDownFD(const Data& d, int i)
{
int parent = i;
  while (1)
    {
        int left = getLeftChild(parent);
        int right = getRightChild(parent);
        int length = storage.size();
        int largest = parent;



        if (left < length && storage[left] > storage[largest])
          largest = left;
        if (right < length && storage[right] > storage[largest])
          largest = right;
        if (largest != parent) {
          swap(largest, parent);
          parent = largest;
        }
        else
          break;
    }
}

void Heap:: remove(const Data& d)
{
        int i = find(d);
        if(i != -1)
        {
          int last = storage.size()  - 1;
          swap(last, i);
          storage.pop_back();
          bubbleDownFD(d, i);
        }

}


void MaxHeap :: bubbleUp()
{
  int child = storage.size() - 1;

  int parent = getParent(child);

  while (child >=0 && parent >= 0 && storage[child] > storage[parent] )
    {
        swap(child, parent);
        child = parent;
        parent = getParent(child);
    }
}


void MaxHeap:: bubbleDown()
{
  int parent = 0;

  while (1)
    {
        int left = getLeftChild(parent);
        int right = getRightChild(parent);
        int length = storage.size();
        int largest = parent;



        if (left < length && storage[left] > storage[largest])
          largest = left;
        if (right < length && storage[right] > storage[largest])
          largest = right;
        if (largest != parent) {
          swap(largest, parent);
          parent = largest;
        }
        else
          break;


    }
}

Data MaxHeap :: getMax()
{
    return getTop();
}


void MinHeap :: bubbleUp()
{
  int child = storage.size() - 1;
  int parent = getParent(child);

  while (child >=0 && parent >= 0 && storage[child] < storage[parent] )
    {
        swap(child, parent);
        child = parent;
        parent = getParent(child);

    }
}


void MinHeap:: bubbleDown()
{
  int parent = 0;

  while (1)
    {
        int left = getLeftChild(parent);
        int right = getRightChild(parent);
        int length = storage.size();
        int largest = parent;



        if (left > length && storage[left] < storage[largest])
          largest = left;
        if (right > length && storage[right] < storage[largest])
          largest = right;
        if (largest != parent) {
          swap(largest, parent);
          parent = largest;
        }
        else
          break;


    }
}

Data MinHeap :: getMin()
{
    return getTop();
}


