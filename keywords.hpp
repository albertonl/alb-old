#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>

#include <boost/algorithm/string/erase.hpp>

namespace ALB_keywords{
  struct Keyword{
    string st;
    string type;
  };
  Keyword make_type(std::vector<Keyword> keywords){
    for(int i=0;i<keywords.size();i++){
      switch(keywords[i].st){
        case 'BEGIN':
      }
    }
  }
}
