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

void Program::read(const string fileName){
ifstream source;
string actual_statement;
string type;
int level=0;
int curr_index=0;
std::vector<int> begin_index;
bool gotCoincidence=false;
// string aux_statement;

source.open(fileName.c_str(), ios::in);

while(!source.eof()){ // While not finished
while(getline(source,actual_statement)){
cout<<"index "<<curr_index<<": "<<actual_statement<<endl;
if(actual_statement[0]!='/' and actual_statement[1]!='/'){ // if not a comment, then store it
// actual_statement.erase(remove(actual_statement.begin(), actual_statement.end(), '\t'), actual_statement.end()); // Remove all tabs
boost::algorithm::erase_all(actual_statement,"\t"); // Remove all tabs
stringstream ss(actual_statement);
// aux_statement=actual_statement;
if(actual_statement.find(" ")!=string::npos){ // If spaces found
while(getline(ss,actual_statement,' ')){
/*for(int i=0;i<level_plus.size();i++){
if(actual_statement==level_plus[i]){ // If keyword in level_plus cat
begin_index.push_back(curr_index);
//type=level_plus[actual_statement];
/*
switch(actual_statement){
case "BEGIN": type="primary"; break;
case "repeat": type="loop"; break;
case "if": type="control"; break;
case "elif": type="control"; break;
case "else": type="control"; break;
}

/*if(actual_statement=="BEGIN") type="primary";
if(actual_statement=="repeat") type="loop";
if(actual_statement=="if") type="control";
if(actual_statement=="elif") type="control";
if(actual_statement=="else") type="control";
for(int j=0;j<level_plus.size();j++){
if(statemes)
}

statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
level++;
gotCoincidence=true;
curr_index++;
}*/
for(int i=0;i<level_plus.size();i++){
if(actual_statement==level_plus[i].first){ // If keyword in level_plus cat
begin_index.push_back(curr_index);
type=level_plus[i].second;
statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
level++;
gotCoincidence=true;
curr_index++;
}
}
for(int i=0;i<level_minus.size() and !gotCoincidence;i++){
if(actual_statement==level_minus[i].first){
type=level_minus[i].second;
/*
switch(actual_statement){
case "END": type="primary_end"; break;
case "ENDLOOP": type="loop_end"; break;
case "FI": type="control_end"; break;
}
*/
/*
if(actual_statement=="END") type="primary_end";
if(actual_statement=="ENDLOOP") type="loop_end";
if(actual_statement=="FI") type="control_end";
*/

level--;
statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
begin_index.pop_back();
gotCoincidence=true;
curr_index++;
}
}
if(!gotCoincidence){
type="general";
statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
curr_index++;
}
}

}
else{
for(int i=0;i<level_plus.size();i++){
if(actual_statement==level_plus[i]){ // If keyword in level_plus cat
begin_index.push_back(curr_index);
//type=level_plus[actual_statement];
/*
switch(actual_statement){
case "BEGIN": type="primary"; break;
case "repeat": type="loop"; break;
case "if": type="control"; break;
case "elif": type="control"; break;
case "else": type="control"; break;
}
*/
if(actual_statement=="BEGIN") type="primary";
if(actual_statement=="repeat") type="loop";
if(actual_statement=="if") type="control";
if(actual_statement=="elif") type="control";
if(actual_statement=="else") type="control";

statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
level++;
gotCoincidence=true;
curr_index++;
}
}
for(int i=0;i<level_minus.size() and !gotCoincidence;i++){
if(actual_statement==level_minus[i]){
// type=level_minus[actual_statement];
/*
switch(actual_statement){
case "END": type="primary_end"; break;
case "ENDLOOP": type="loop_end"; break;
case "FI": type="control_end"; break;
}
*/
if(actual_statement=="END") type="primary_end";
if(actual_statement=="ENDLOOP") type="loop_end";
if(actual_statement=="FI") type="control_end";

level--;
statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
begin_index.pop_back();
gotCoincidence=true;
curr_index++;
}
}
if(!gotCoincidence){
type="general";
statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
curr_index++;
}
}
gotCoincidence=false;
}

}
}
}
source.close();
}
