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
};
const static std::vector<pair<string,string> > level_minus = {
	{"END","primary_end"},
	{"ENDLOOP","loop_end"},
	{"FI","control_end"}
};
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
	source.close();
}

void Program::print(const string fileName){
	for(int i=0;i<statements.size();i++){
		cout<<statements[i].st<<endl;
	}
	cout<<"File: "<<fileName<<endl;
	cout<<"ST.\t\t\tLEVEL\t\tBEGIN INDEX\tTYPE"<<endl;
	for(int i=0;i<statements.size();i++){
		cout<<statements[i].st<<"\t\t";
		cout<<statements[i].level<<"\t\t";
		cout<<statements[i].begin_index<<"\t\t\t";
		cout<<statements[i].type<<endl;
	}
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
int main(int argc, char const *argv[]){;
	const string fileName=argv[1];
	Program program;
	program.read(fileName);
	program.print(fileName);
	return 0;
}
