/*
	The official ALB language interpreter
	Version 0.0.4
	Latest update: March 17th 2019
	17032019 0954A
*/

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
using namespace std;

// RECOGNISED KEYWORDS
const static std::vector<pair<string,string> > level_plus = {
	{"BEGIN","primary"},
	{"repeat","loop"},
	{"if","control"},
	{"elif","control"},
	{"else","control"}
}
const static std::vector<pair<string,string> > level_minus = {
	{"END","primary_end"},
	{"ENDLOOP","loop_end"},
	{"FI","control_end"}
}
/*
// TYPES
const std::map<string,string> level_plus_type = {
	{"BEGIN","primary"},
	{"repeat","loop"},
	{"if","control"},
	{"elif","control"},
	{"else","control"}
};
const std::map<string,string> level_minus_type = {
	{"END","primary_end"},
	{"ENDLOOP","loop_end"},
	{"FI","control_end"}
};
*/

//DEFINITION OF STATEMENT
struct Statement{
	string st; // Statement
	int level; // Number of 'tabs' that has before
	int begin_index; // Index of the beginning of the structure
	string type; // Conditional, loop, primary...

	Statement(string,int,int,string); // Constructor
};
Statement::Statement(string st_,int level_,int begin_index_,string type_){
	st=st_;
	level=level_;
	begin_index=begin_index_;
	type=type_;
}

class Program{
	private:
		std::vector<Statement> statements;
	public:
		Program(); // Constructor (void)

		void read(const string fileName);
		void run(const string fileName);
		//void push_vec(string actual_statement);
		void print(const string fileName);

		int loop(std::vector<Statement> statements, int curr_index);
		int stdout(std::vector<Statement> statements, int curr_index);
};
Program::Program(){
	statements.push_back(Statement(" ",0,0," "));
}

void Program::read(const string fileName){
	ifstream source;
	string actual_statement;
	string type;
	int level=0;
	int curr_index=0;
	std::vector<int> begin_index;
	bool gotCoincidence=false;

	source.open(fileName.c_str(),ios::in);

	while(!source.eof()){ // While not finished
		while(getline(source,actual_statement)){
			cout<<"index "<<curr_index<<": "<<actual_statement<<endl;
			if(actual_statement[0]!='/' && actual_statement[1]!='/'){ // If not a comment, then store it
				boost::algorithm::erase_all(actual_statement,"\t");
				stringstream ss(actual_statement);

				if(actual_statement.find(" ")!=string::npos){ // If spaces found
					while(getline(ss,actual_statement,' ')){
						for(int i=0;i<level_plus.size();i++){
							if(actual_statement==level_plus[i].first){ // If keyword in level_plus cat
								begin_index.push_back(curr_index);
								type=level_plus[i].second;
								statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
								level++;
								gotCoincidence=true;
							}
						}
						if(!gotCoincidence){
							for(int i=0;i<level_minus.size();i++){
								if(actual_statement==level_minus[i].first){ // If key in level_minus cat
									type=level_minus[i].second;
									level--;
									statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
									begin_index.pop_back();
									gotCoincidence=true;
								}
							}
							if(!gotCoincidence){ // If not any of the past two, it must be of general type
								type="general";
								statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
							}
						}
						curr_index++;
						gotCoincidence=false;
					}
				}
				else{
					for(int i=0;i<level_plus.size();i++){
						if(actual_statement==level_plus[i].first){ // If keyword in level_plus cat
							begin_index.push_back(curr_index);
							type=level_plus[i].second;
							statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
							level++;
							gotCoincidence=true;
						}
					}
					if(!gotCoincidence){
						for(int i=0;i<level_minus.size();i++){
							if(actual_statement==level_minus[i].first){ // If key in level_minus cat
								type=level_minus[i].second;
								level--;
								statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
								begin_index.pop_back();
								gotCoincidence=true;
							}
						}
						if(!gotCoincidence){ // If not any of the past two, it must be of general type
							type="general";
							statements.push_back(Statement(actual_statement,level,begin_index[begin_index.size()-1],type));
						}
					}
					curr_index++;
					gotCoincidence=false;
				}
			}
		}
	}
	source.close();
}

void Program::print(const string fileName){
	for(int i=0;i<statements.size();i++){
		cout<<statements[i].st<<endl;
	}
	cout<<"File: "<<fileName<<endl;
	cout<<"ST.\t\tLEVEL\tBEGIN INDEX\tTYPE"<<endl;
	for(int i=0;i<statements.size();i++){
		cout<<statements[i].st<<"\t\t";
		cout<<statements[i].level<<"\t\t";
		cout<<statements[i].begin_index<<"\t";
		cout<<statements[i].type<<endl;
	}
	cout<<endl;
	for(int i=0;i<statements.size();i++){
		cout<<statements[i].st<<" ";
	}
	cout<<endl;
}
/*
void Program::run(const string fileName){
	bool began=false;
	int index=0;
	int loopRepeats=0;
	for(int i=0;i<=statements.size();i++){
		if(statements[i]=="BEGIN" && !began){
			began=true;
		}
		else if(statements[i]=="END" && began){
			began=false;
		}
		else if(began){
			if(statements[i]=="BEGIN"){
				cout<<"In "<<fileName<<", ERROR 001: 'BEGIN' cannot be used inside another."<<endl;
				exit(0);
			}
			else if(statements[i]=="repeat"){
				i++;
				if(statements[i]=="infinity"){
					while(true){
						for(index=i+1;statements[index]!="ENDLOOP";index++){
							if(statements[index]=="out"){
								while(statements[index]!=";"){
									index++;
									if(statements[index]=="NEWL"){
										cout<<endl;
									}
									else if(statements[index]!=";"){
										cout<<statements[index]<<" ";
									}
								}
							}
						}
					}
				}
				else{
					loopRepeats = stoi(statements[i]);
					for(int j=0;j<loopRepeats;j++){
						index=i+1;
						for(index;statements[index]!="ENDLOOP";index++){
							if(statements[index]=="out"){
								while(statements[index]!=";"){
									index++;
									if(statements[index]=="NEWL"){
										cout<<endl;
									}
									else if(statements[index]!=";"){
										cout<<statements[index]<<" ";
									}
								}
							}
						}
					}
					i=index+1;
				}
			}
			else if(statements[i]=="out"){
				while(statements[i]!=";"){
					i++;
					if(statements[i]=="NEWL"){
						cout<<endl;
					}
					else if(statements[i]!=";"){
						cout<<statements[i]<<" ";
					}
				}
			}
		}
		else{
			if(statements[i]=="END"){
				cout<<"In "<<fileName<<", ERROR 002: 'END' cannot be used before a 'BEGIN' statement."<<endl;
				exit(0);
			}
		}
	}
}
*/
int Program::loop(std::vector<Statement> statements, int curr_index){
	int i=0;
	int iterationNum=0;
	string actualString;
	if(statements[curr_index+1].st=="infinity"){
		while(true){
			for(i=curr_index+2;statements[i].st!="ENDLOOP";i++){
				/*switch(statements[i].st){
					case "repeat": i=loop(statements,i); break;
					case "out": i=stdout(statements,i); break;
				}*/
				if(statements[i].st=="repeat") i=this->loop(statements,i);
				else if(statements[i].st=="out") i=this->stdout(statements,i);
			}
		}
	}
	else{
		actualString=statements[curr_index+1].st;
		for(int j=0;j<actualString.length();j++){
			iterationNum+=actualString[j]-'0';
		}
		for(iterationNum;iterationNum>0;iterationNum--){
			for(i=curr_index+2;statements[i].st!="ENDLOOP";i++){
				/*switch(statements[i].st){
					case "repeat": i=loop(statements,i); break;
					case "out": i=stdout(statements,i); break;
				}*/
				if(statements[i].st=="repeat") i=this->loop(statements,i);
				else if(statements[i].st=="out") i=this->stdout(statements,i);
			}
		}
	}
	return i;
}/*
int Program::stdout(std::vector<Statement> statements,int curr_index){
	int i=0;
	int totali=0;
	float totalf=0.0;

	string actualString;

	if(statements[curr_index]=="out{" || statements[curr_index+1]=="{"){
		for(i=curr_index+2;statements[i]!="}";i++){
			if(statements[i]==":string"){
				i++;
				actualString=statements[i];
				while(actualString[actualString.length()-1]!="\""){
					if(actualString[0]=="\""){
						for(int j=1;j<actualString.length();j++){
							cout<<actualString[j];
						}
						cout<<" ";

					}
					if(actualString=="NEWL") cout<<endl;
					if(actualString==";") break;
					i++;
				}
			}/*
			else if(statements[i]==":int"){
				i++;
				actualString=statements[i];
				while(actualString[actualString.length()-1]!=";"){
					if(actualString[0]!=";"){
						cout<<std::stoi(actualString);
						if(totali==0){
							if(actualString=="+"){
								total+=(std::stoi(statements[i-1])+std::stoi(statements[i+1]));
							}
							if(actualString=="-"){
								total-=(std::stoi(statements[i-1])-std::stoi(statements[i+1]));
							}
							if(actualString=="*"){
								total*=(std::stoi(statements[i-1])*std::stoi(statements[i+1]));
							}
							if(actualString=="/"){
								total/=(std::stoi(statements[i-1])/std::stoi(statements[i+1]));
							}
						}
					}
					if(actualString=="NEWL") cout<<endl;
					if(actualString==";") break;
					i++;
				}
			}
			else if(statements[i]==":float"){
				i++;
				actualString=statements[i];
				while(actualString[actualString.length()-1]!=";"){
					if(actualString[0]!=";"){
						cout<<std::stof(actualString);
						if(total==0){
							if(actualString=="+"){
								total+=(std::stoi(statements[i-1])+std::stoi(statements[i+1]));
							}
							if(actualString=="-"){
								total-=(std::stoi(statements[i-1])-std::stoi(statements[i+1]));
							}
							if(actualString=="*"){
								total*=(std::stoi(statements[i-1])*std::stoi(statements[i+1]));
							}
							if(actualString=="/"){
								total/=(std::stoi(statements[i-1])/std::stoi(statements[i+1]));
							}
						}
					}
					if(actualString=="NEWL") cout<<endl;
					if(actualString==";") break;
					i++;
				}
			}
			else if(statements[i].st==":int"){
				i++;
				actualString=statements[i].st;
				while(actualString[actualString.length()-1]!=";"){
					if(statements[i+1].st!=";"){
						if(totali==0){
							switch(statements[i+1].st){
								case '+':
									i++;
									totali+=std::stoi(statements[i-1])+std::stoi(statements[i+1]);
									break;
								case '-':
									i++;
									totali-=std::stoi(statements[i-1])-std::stoi(statements[i+1]);
									break;
								case '*':
									i++;
									totali*=std::stoi(statements[i-1])*std::stoi(statements[i+1]);
									break;
								case '/':
									i++;
									totali/=std::stoi(statements[i-1])/std::stoi(statements[i-1]);
									break;
								default:
									totali=std::stoi(statements[i]);
									break;
							}
						}
						else{
							switch(statements[i+1]){
								case '+':
									i++;
									totali+=std::stoi(statements[i+1]);
									break;
								case '-':
									i++;
									totali-=std::stoi(statements[i+1]);
									break;
								case '*':
									i++;
									totali*=std::stoi(statements[i+1]);
									break;
								case '/':
									i++;
									totali/=std::stoi(statements[i-1]);
									break;
								default:
									totali=std::stoi(statements[i]);
									break;
							}
						}
					}
					else break;
					i++;
				}
				cout<<totali;
			}
		}
	}
	return i;
}*/
void Program::run(const string fileName){
	bool began=false;
	int index=0;
	for(int i=0;i<statements.size();i++){
		if(statements[i].st=="BEGIN" && !began) began=true;
		else if(statements[i].st=="END" && began) began=false;
		else if(began){
			if(statements[i].st=="BEGIN"){
				cout<<error(fileName,1)<<endl;
				exit(0);
			}
			else if(statements[i]=="repeat") i=loop(statements,i);
		}
	}
}
int main(int argc, char const *argv[]){;
	const string fileName=argv[1];
	Program program;
	program.read(fileName);
	program.print(fileName);
	return 0;
}
