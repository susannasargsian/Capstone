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
