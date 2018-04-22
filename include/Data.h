#ifndef DATA_H
#define DATA_H
#include <string>
class Data
{
    public:
        Data(){};
        virtual ~Data(){};
        Data(double p, double s, std::string o): price(p), size(s), order_id(o){}

        bool operator < (const Data& d)const;


        bool operator > (const Data& d)const;


        bool operator == (const Data& d)const;


        bool operator <= (const Data& d)const;


        bool operator >= (const Data& d)const;

    public:
        double price;
        double size;
        std::string order_id;
};


#endif // DATA_H
