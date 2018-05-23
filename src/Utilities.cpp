#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>





double toDouble(std::string const &str, std::size_t const p)
{
  std::stringstream sstrm;
  sstrm << std::setprecision(p) << std::fixed << str << std::endl;

  double d;
  sstrm >> d;

  return d;
}


void toTime (const std::string& DT, Time& T)
{
    using namespace std;
    size_t start= DT.find("T");
    size_t end= DT.find("Z");
    std::string token = DT.substr(start+1, end-start-1);
    size_t ht = token.find(":");
    std::string hour = token.substr(0, ht);
    token = token.substr(ht + 1);
    ht = token.find(":");
    std::string minute = token.substr(0, ht);
    token = token.substr(ht + 1);
    ht = token.find(".");
    std::string second = token.substr(0, ht);
    std::string milisecond = token.substr(ht+1);

    T.hour = atoi(hour.c_str());
    T.minute = atoi(minute.c_str());
    T.second = atoi(second.c_str());
    T.milisecond = atoi(milisecond.c_str());
}

int Time::Difference (const Time& time)
{
  /*  int dh = hour-time.hour;
    int dm = minute-time.minute;
    int ds = second-time.second;
    return 3600*dh + 60*dm + ds;
    */
    return second - time.second;
}




