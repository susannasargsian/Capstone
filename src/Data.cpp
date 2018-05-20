#include "Data.h"

bool Data:: operator < (const Data& d)const
{
    if(price < d.price)
    {
        return true;
    }

    if(price == d.price && order_id < d.order_id)
    {
        return true;
    }

    return false;
}

bool Data:: operator > (const Data& d)const
{
    if(price > d.price)
    {
        return true;
    }

    if(price == d.price && order_id > d.order_id)
    {
        return true;
    }

    return false;

}

bool Data:: operator == (const Data& d)const
{

    if(price == d.price && order_id == d.order_id)
    {
        return true;
    }

    return false;

}

bool Data:: operator <= (const Data& d)const
{
    return (*this < d) || (*this == d);

}

bool Data:: operator >= (const Data& d)const
{
    return (*this > d) || (*this == d);

}

void Data:: operator = (const Data& d)
{
    price = d.price;
    size = d.size;
    order_id = d.order_id;
}



