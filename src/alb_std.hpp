/*
  Standard Library
  ALB Programming language

  Alberto Navalon Lillo (C) April 2019
  This software is under the GNU General Public License
  https://github.com/albertonl/alb/blob/master/LICENSE
*/

#ifndef ALB_STD_HPP
#define ALB_STD_HPP

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
#include "alb_program.hpp" // Program class
#include "alb_keywords.hpp" // ALB recognised keywords
#include "alb_error.hpp" // Exception handler
using namespace std;
using namespace alb_statement;
using namespace alb_program;

// That's stupid
const char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'}; // For outi use

namespace alb_std{
  int Program::stdout(std::vector<Statement> statements,int curr_index){
  	int i=0;
  	int aux=0;
  	int totali=0;
  	float totalf=0.0;

  	bool broken=false;
  	bool opened=false;
  	bool nospace=false;

  	string actualString;

  	if(statements[curr_index].st=="out{" || statements[curr_index+1].st=="{"){
  		if(statements[curr_index+1].st=="{" && statements[curr_index].st!="out{") curr_index++;
  		for(i=curr_index+1;statements[i].st!="}";i++){
        // String option
  			if(statements[i].st==":string" || statements[i].st==":str"){
  				i++;
  				for(aux=i;broken==false;aux++){
  					actualString=statements[aux].st;
  					if(actualString=="NEWL") cout<<endl;
  					else if(actualString==";") broken=true;
  					else if(actualString[0]=='\"' && !opened){
  						opened=true;
  						for(int j=1;j<actualString.length();j++){
  							if(actualString[j]=='\"'){
  								nospace=true;
  								break;
  							}
  							cout<<actualString[j];
  						}
  						if(!nospace) cout<<" ";
  					}
  					else if(actualString[actualString.length()-1]=='\"' && opened){
  						for(int j=0;j<actualString.length()-1;j++){
  							if(actualString[j]=='\"') break;
  							cout<<actualString[j];
  						}
  						opened=false;
  					}
  					else if(opened){
  						for(int j=0;j<actualString.length();j++){
  							if(actualString[j]=='\"') break;
  							cout<<actualString[j];
  						}
  						cout<<" ";
  					}
  				}
  			}
        // Integer option
  			else if(statements[i].st==":int"){
  				i++;
  				actualString=statements[i].st;
  				while(actualString!=";"){
  					if(actualString==";") break;
  					else if(totali==0){
  						totali=std::stoi(actualString);
  					}
  					else{
  						if(actualString=="+") totali+=std::stoi(statements[i+1].st);
  						else if(actualString=="-") totali-=std::stoi(statements[i+1].st);
  						else if(actualString=="*") totali*=std::stoi(statements[i+1].st);
  						else if(actualString=="/") totali/=std::stoi(statements[i+1].st);
  						i++;
  					}
  					i++;
  					actualString=statements[i].st;
  				}
  				cout<<totali;
  			}
        // Float option
  			else if(statements[i].st==":float"){
  				i++;
  				actualString=statements[i].st;
  				while(actualString!=";"){
  					if(actualString==";") break;
  					else if(totali==0){
  						totali=std::stof(actualString);
  					}
  					else{
  						if(actualString=="+") totalf+=std::stof(statements[i+1].st);
  						else if(actualString=="-") totalf-=std::stof(statements[i+1].st);
  						else if(actualString=="*") totalf*=std::stof(statements[i+1].st);
  						else if(actualString=="/") totalf/=std::stof(statements[i+1].st);
  						i++;
  					}
  					i++;
  					actualString=statements[i].st;
  				}
  				cout<<totalf;
  			}
        // Character option
  			else if(statements[i].st==":char"){
  				i++;
  				actualString=statements[i].st;
  				if(actualString.length()==3){
  					if(actualString[0]=='\'' && actualString[2]=='\''){
  						cout<<actualString[1];
  					}
  				}
  			}
        // Newline option
        // (Substitute to ':str NEWL ;')
  			else if(statements[i].st==":newline" || statements[i].st==":newl"){
  				cout<<endl;
  			}
  			// Variable re-initialization
  			totali=0;
  			totalf=0.0;
  			aux=0;

  			actualString="";

  			broken=false;
  			opened=false;
  			nospace=false;
  		}
  	}
  	return i;
  } // stdout()

  // Specific outputs
  int sstdout(std::vector<Statement> statements,int curr_index){
    string type_out=statements[curr_index].st; // General use
    string actualString; // General use
    int aux=0; // General use
    bool broken=false; // General use
    bool toBreak=false; // General use
    bool opened=false; // String out use

      // Integer out use variables
    std::vector<string> broken_statement;
    int totali=0;

    // String out
    if(type_out=="outs"){
        for(int i=curr_index+1;!broken;i++){
            actualString=statements[i].st;
            if(!opened){
                if(actualString[0]=='\"'){
                    opened=true;
                    if(actualString[actualString.length()-1]==';'){
                        if(actualString[actualString.length()-2]=='\"'){
                            actualString.pop_back();
                            toBreak=true;
                            for(int j=1;j<actualString.length()-1;j++) cout<<actualString[j];
                            opened=false;
                        }
                        else{
                            for(int j=1;j<actualString.length();j++) cout<<actualString[j];
                        }
                    }
                    else{
                        for(int j=1;j<actualString.length();j++) cout<<actualString[j];
                        cout<<" ";
                    }
                }
                else{
                    if(actualString[actualString.length()-1]==';'){
                        actualString.pop_back();
                        toBreak=true;
                    }
                    if(actualString=="NEWL") cout<<endl; // New line
                    else if(actualString=="BSPACE") cout<<" "; // Blank space
                    else if(actualString=="BTAB") cout<<"   "; // Blank tab
                }
            }
            else{
                if(actualString[actualString.length()-1]==';'){
                    if(actualString[actualString.length()-2]=='\"'){
                        actualString.pop_back();
                        toBreak=true;
                        for(int j=0;j<actualString.length()-1;j++) cout<<actualString[j];
                        opened=false;
                    }
                    else cout<<actualString<<" ";
                }
                else{
                    if(actualString[actualString.length()-1]=='\"'){
                        for(int j=0;j<actualString.length()-1;j++) cout<<actualString[j];
                        opened=false;
                    }
                    else{
                        cout<<actualString<<" ";
                    }
                }
            }

            if(toBreak) broken=true;
        }
    } // if(type_out=="outs")
    else if(type_out=="outc"){
      actualString=statements[curr_index+1].st;
      if(actualString[0]=='\'' && actualString[2]=='\''){
        if(actualString[1]=='\\' && actualString.length()>3){
          if(actualString[4]=='\'') cout<<'\'';
        }
        else cout<<actualString[1];
      }

      if(actualString[actualString.length()-1]!=';') alb_error::error(14);
      /*
        ERROR INFO:
          - CAT: 1 (general)
          - ERRNO: 4
          - MSG: "ALB General Error: expected semicolon"
      */
    } // else if(type_out=="outc")

    else if(type_out=="outi"){
      broken_statement.push_back("");
      actualString=statements[curr_index+1].st;
      if(statements[curr_index+2].st==";" || actualString[actualString.length()-1]==';'){
        // TO FILL broken_statement
        for(int j=0;j<actualString.length();j++){
          if(actualString[j]>=48 && <=57){
            // If it is a number
            if(broken_statement[broken_statement.size()-1]=='+' ||
              broken_statement[broken_statement.size()-1]=='-' ||
              broken_statement[broken_statement.size()-1]=='*' ||
              broken_statement[broken_statement.size()-1]=='/' ||
              broken_statement[broken_statement.size()-1]=='(' ||
              broken_statement[broken_statement.size()-1]==')'){
              broken_statement.push_back("");
            }
            broken_statement[broken_statement.size()-1]+=actualString[j];
          }
          else{
            switch(actualString[j]){
              case '+':
                broken_statement.push_back("");
                broken_statement[broken_statement.size()-1]+=actualString[j];
                break;
              case '-':
                broken_statement.push_back("");                      
                broken_statement[broken_statement.size()-1]+=actualString[j];
                break;
              case '*':
                broken_statement.push_back("");                      
                broken_statement[broken_statement.size()-1]+=actualString[j];
                break;
              case '/':
                broken_statement.push_back("");                      
                broken_statement[broken_statement.size()-1]+=actualString[j];
                break;
              case '(':
                broken_statement.push_back("");                      
                broken_statement[broken_statement.size()-1]+=actualString[j];
                break;
              case ')':
                broken_statement.push_back("");                      
                broken_statement[broken_statement.size()-1]+=actualString[j];
                break;
              default:
                alb_error::error(13);
                /*
                  ERROR INFO:
                    - CAT: 1 (general)
                    - ERRNO: 3
                    - MSG: "ALB General Error: unexpected character inside numeric statement"
                */
                break;
            }
          }
        }

        // GET RESULTS
        for(int j=0;j<broken_statement.size();j++){
          if(broken_statement[j]=="+"){
            totali+=std::stoi(broken_statement[j+1]);
            j++;
          }
          else if(broken_statement[j]=="-"){
            totali-=std::stoi(broken_statement[j+1]);
            j++;
          }
          else if(broken_statement[j]=="*"){
            totali*=std::stoi(broken_statement[j+1]);
            j++;
          }
          else if(broken_statement[j]=="/"){
            totali/=std::stoi(broken_statement[j+1]);
            j++;
          }
          else if(broken_statement[j]=="(" || broken_statement[j]==")") j++;
          else totali=std::stoi(broken_statement[j]);
        }
      } // if(statements[curr_index+2].st==";" || actualString[actualString.length()-1]==';')
      else{
        for(int i=curr_index+1;!broken;i++){
          actualString=statements[i].st;
          
          if(actualString==";") broken=true;
          else if(actualString=="+"){
            actualString+=std::stoi(statements[i+1].st);
            i++;
          }
          else if(actualString=="-"){
            actualString-=std::stoi(statements[i+1].st);
            i++;
          }
          else if(actualString=="*"){
            actualString*=std::stoi(statements[i+1].st);
            i++;
          }
          else if(actualString=="/"){
            actualString/=std::stoi(statements[i+1].st);
            i++
          }
          else if(actualString=="(" || actualString==")") i++;
          else totali=std::stoi(statements[i].st);
        }
      }
      cout<<totali;
    } // else if(type_out=="outi")

    return 
  }

} // namespace alb_std

#endif // ALB_STD_HPP
