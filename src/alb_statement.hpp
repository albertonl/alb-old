/*
  Statement structure
  ALB Programming language

  Alberto Navalon Lillo (C) April 2019
  This software is under the GNU General Public License
  https://github.com/albertonl/alb/blob/master/LICENSE
*/

#ifndef ALB_STATEMENT_HPP
#define ALB_STATEMENT_HPP

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
#include "alb_keywords.hpp" // ALB recognised keywords
#include "alb_error.hpp" // Exception handler
using namespace std;
using namespace alb_program;

namespace alb_statement{
  // DEFINITION OF STATEMENT
  struct Statement{
    string st; // Statament
    int level; // "Number of tabs that has before"
    int begin_index; // Index of the beginning of the structure where the statement is located
    string type; // Conditional, loop, primary...

    Statement(string,int,int,string); // Constructor
  }

  Statement::Statement(string st_,int level_,int begin_index_,string type_){
    st=st_;
    level=level_;
    begin_index=begin_index_;
    type=type_;
  }
} // namespace alb_statement

#endif // ALB_STATEMENT_HPP
