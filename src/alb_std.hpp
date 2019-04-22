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
    string type_out=statements[curr_index].st;
    // String out
    if(type_out=="outs"){
      
    }
  }
} // namespace alb_std

#endif // ALB_STD_HPP
