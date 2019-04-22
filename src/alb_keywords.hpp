/*
  Keywords
  ALB Programming language

  Alberto Navalon Lillo (C) April 2019
  This software is under the GNU General Public License
  https://github.com/albertonl/alb/blob/master/LICENSE
*/

#ifndef ALB_KEYWORDS_HPP
#define ALB_KEYWORDS_HPP

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <boost/algorithm/string/erase.hpp>

#include "alb_std.hpp" // Standard ALB library
#include "alb_program.hpp" // Program class
#include "alb_statement.hpp" // Statement structure
#include "alb_error.hpp" // Exception handler
using namespace std;
using namespace alb_statement;
using namespace alb_program;

namespace alb_keywords{

  // RECOGNISED KEYWORDS
  // Level Plus (level++)
  const static std::vector<pair<string,string> > level_plus{
    {"BEGIN","primary"},
    {"repeat","loop"},
    {"if","control"},
    {"elif","control"},
    {"else","control"}
  };
  // Level Minus (level--)
  const static std::vector<pair<string,string> > level_minus = {
    {"END","primary_end"},
    {"ENDLOOP","loop_end"},
    {"FI","control_end"}
  };

} // namespace alb_keywords

#endif // ALB_KEYWORDS_HPP
