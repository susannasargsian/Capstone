#ifndef BASE_H
#define BASE_H

#include "Data.h"


class Base
{
    public:
        Base();
        virtual ~Base();
        virtual void insert(Data)=0;
        virtual void remove(const Data& d)=0;
        virtual void update(Data,Data)=0;
        virtual void getTitle()=0;
        virtual Data getMin(){return Data();}
        virtual Data getMax(){return Data();}


    protected:

    private:
};

#endif // BASE_H
