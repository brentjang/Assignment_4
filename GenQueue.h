#include "GenDDL.h"
#include <iostream>

using namespace std;

template <class T>
class GenQueue
{
    public:
        GenQueue();
        GenQueue(int maxSize);
        ~GenQueue();
        void insert(T d);
        T remove();
        T front();
        bool isEmpty();
        int getSize();

        int numElements;
        GenDDL<T> *myQueue;
};

template <class T>
GenQueue<T>::GenQueue()
{
    myQueue = new GenDDL<T>();
    numElements = 0;
}

template <class T>
GenQueue<T>::~GenQueue()
{
    delete myQueue;
}

template <class T>
void GenQueue<T>::insert(T d)
{
    myQueue->insertBack(d);
    ++numElements;
}

template <class T>
T GenQueue<T>::remove()
{
    if(!isEmpty())
    {
        T c = myQueue->removeFront();
        numElements--;
        return c;
    }
    else
    {
        cout << "Queue is Empty";
    }
}

template <class T>
T GenQueue<T>::front()
{
    return myQueue->front->data;
}

template <class T>
bool GenQueue<T>::isEmpty()
{
    return (numElements == 0);
}

template <class T>
int GenQueue<T>::getSize()
{
    return numElements;
}
