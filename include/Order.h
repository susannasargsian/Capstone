#ifndef ORDER_H
#define ORDER_H
#include "Data.h"
#include "Utilities.h"
#include <string>


class Order
{
    public:
        Order(std::string t, std::string s, const Data& d, const Time& tm): type(t), side(s), data(d), time(tm){}
        virtual ~Order();

    protected:

    private:

    public:
        std:: string type;
        std:: string side;
        Data data;
        Data new_data;
        Time time;
};

#endif // ORDER_H
