/*
  Program class
  ALB Programming language

  Alberto Navalon Lillo (C) April 2019
  This software is under the GNU General Public License
  https://github.com/albertonl/alb/blob/master/LICENSE
*/

#ifndef ALB_PROGRAM_HPP
#define ALB_PROGRAM_HPP

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
#include "alb_statement.hpp" // Statement structure
#include "alb_keywords.hpp" // ALB recognised keywords
#include "alb_error.hpp" // Exception handler
using namespace std;
using namespace alb_statement;

namespace alb_program{
  class Program{
    private:
      std::vector<Statement> statements;
    public:
      Program(); // Constructor (void)

      void read(const string fileName); // Read file
      void run(const string fileName); // Identify type of statement and redirect to its corresponding function
  }

  void Program::read(const string fileName){
    ifstream source; // File
    string actual_statement; // Aux holder

    string type;
    int level=0;
    int curr_index;
    std::vector<int> begin_index;
    int aux; // Aux numeric holder

    source.open(fileName.c_str(),ios::in); // Open file in read mode

    while(!source.eof()){ // While not reached end of file
      while(getline(source,actual_statement)){ // Get values until next line
        if(actual_statement[0]!='/' && actual_statement[1]!='/'){ // If not a comment, store it
          std::replace(actual_statement.begin(),actual_statement.end(),'\t',' '); // Replace all tabs in line by blank spaces
          stringstream ss(actual_statement);
          if(actual_statement.find(" ")!=string::npos){ // If spaces found
            while(getline(ss,actual_statement,' ')){ // Get value until next space
              for(int i=0;i<actual_statement.length();i++){ // Identify unnecesary spaces
                if(actual_statement[i]==' ') aux=i;
              }
              // Remove unnecesary spaces
              if(aux!=0 && aux!=-1) actual_statement.erase(actual_statement.begin(),actual_statement.begin()+aux);
              else if(aux==0) actual_statement.erase(actual_statement.begin());

              for(int i=0;i<alb_keywords::level_plus.size();i++){
                if(actual_statement==alb_keywords::level_plus[i].first){
                  // If actual_statement is a level_plus category keyword
                  begin_index.push_back(curr_index);
                  type=alb_keywords::level_plus.second;
                  statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
                  level++;
                  gotCoincidence=true;
                }
              }
              if(!gotCoincidence){ // If has not got coincidence yet
                for(int i=0;i<alb_keywords::level_minus.size();i++){
                  if(actual_statement==alb_keywords::level_minus[i].first){
                    // If actual_statement is a level_minus category keyword
                    type=alb_keywords::level_minus[i].second;
                    level--;
                    statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
                    begin_index.pop_back();
                    gotCoincidence=true;
                  }
                }
                if(!gotCoincidence){
                  // If not any of the past two, must be a general type keyword
                  type="general";
                  statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
                }
              }
              curr_index++;
              gotCoincidence=false;
            } // while(getline(ss,actual_statement,' '))
          }
          else{ // If no spaces found
            for(int i=0;i<alb_keywords::level_plus.size();i++){
              if(actual_statement==alb_keywords::level_plus[i].first){
                // If actual_statement is a level_plus category keyword
                begin_index.push_back(curr_index);
                type=alb_keywords::level_plus.second;
                statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
                level++;
                gotCoincidence=true;
              }
            }
            if(!gotCoincidence){ // If has not got coincidence yet
              for(int i=0;i<alb_keywords::level_minus.size();i++){
                if(actual_statement==alb_keywords::level_minus[i].first){
                  // If actual_statement is a level_minus category keyword
                  type=alb_keywords::level_minus[i].second;
                  level--;
                  statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
                  begin_index.pop_back();
                  gotCoincidence=true;
                }
              }
              if(!gotCoincidence){
                // If not any of the past two, must be a general type keyword
                type="general";
                statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
              }
            }
            curr_index++;
            gotCoincidence=false;
          } // else
        }
      }
    }
  } // void Program::read(const string fileName)

  void Program::run(const string fileName){
    bool inExec=false; // In executable

    for(int i=0;i<statements.size();i++){ // Iterate through the whole vector
      if(statements[i].st=="BEGIN" && !inExec){
        // If beginning of executable found
        inExec=true; // In executable
      }
      else if(statements[i].st=="END" && inExec){
        // If end of executable found
        inExec=false; // Not in executable
      }
      else if(statements[i].st=="END" && !inExec){
        // END cannot be used before a BEGIN
        alb_error::error(2); // Throw exception 2
      }
      else if(inExec){
        // If in executable and is none of the previous two
        if(statements[i].st=="BEGIN"){
          // BEGIN cannot be used inside another BEGIN
          alb_error::error(1); // Throw exception 1
        }
        else if(statements[i].st=="repeat") i=alb_std::loop(statements,i);
        else if(statements[i].st=="out{") i=alb_std::stdout(statements,i);
        else if(statements[i].st=="out" && statements[i].st=="{") i=alb_std::stdout(statements,i);
        else if(statements[i].st=="outi") i=alb_std::sstdout(statements,i); // Specific integer out
        else if(statements[i].st=="outf") i=alb_std::sstdout(statements,i); // Specific float out
        else if(statements[i].st=="outc") i=alb_std::sstdout(statements,i); // Specific char out
        else if(statements[i].st=="outs") i=alb_std::sstdout(statements,i); // Specific string out
        else if(statements[i].st=="outv") i=alb_std::sstdout(statements,i); // Specific variable out
      }
    }
  }
} // namespace alb_program

#endif // ALB_PROGRAM_HPP
