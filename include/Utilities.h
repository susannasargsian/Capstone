#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#include <string>

class Time
{
public:
    Time(): hour(0), minute(0), second(0), milisecond(0){}
    Time(int h, int m, int s, int ms): hour(h), minute(m), second(s), milisecond(ms){}
 //   Time(const std::string& tm);
    int Difference(const Time& time);

public:
    int hour;
    int minute;
    int second;
    int milisecond;


};


double toDouble(std::string const &str, std::size_t const p);
void toTime (const std::string& DT, Time& time);



#endif // UTILITIES_H_INCLUDED
