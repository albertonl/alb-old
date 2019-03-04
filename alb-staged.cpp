#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include <cstdlib>

using namespace std;

const static std::vector<string> level_plus = {"BEGIN","VAR","repeat","if","else","elif"};
const static std::vector<string> level_minus = {"END","ENDVAR","ENDLOOP","COND_END"};

struct Statement{
		string statement;
		int level;
		int index_on_level;
		//int type;

		Statement(string,int,int);
		//void identify();
};

Statement::Statement(string statement_, int level_, int index_on_level_){
	statement=statement_;
	level=level_;
	index_on_level=index_on_level_;
	//type=type_;
}
/*
void Statement::identify(){
	switch(statement){
		// Control statements
		case "BEGIN": type=1; break;
		case "END": type=2; break;
		default:
			type=0;
			break;
	}
}
*/
class Program{
	private:
		vector<Statement> program;
	public:
		void read(string fileName);
		void run(string fileName);
};

void Program::read(string fileName){
	ifstream source;
	string actualLine;
	std::vector<string> tmp_program;

	int level=0;
	std::vector<int> index_on_level(1,0);
	bool gotCoincidence=false;

	source.open(fileName.c_str(), ios::in);

	while(!source.eof()){
		while(getline(source,actualLine)){
			if(actualLine[0]!='/' && actualLine[1]!='/'){
				actualLine.erase(remove(actualLine.begin(), actualLine.end(), '\t'), actualLine.end());
				stringstream ss(actualLine);
				if(actualLine.find(" ")!=string::npos){
					while(getline(ss,actualLine,' ')){
						tmp_program.push_back(actualLine);
					}
				}
				else{
					tmp_program.push_back(actualLine);
				}
			}
		}
/*		if(actualLine.find(" ")!=string::npos){
			while(!actualLine.eof()){
				getline(actualLine,actualSegment,' ');
				program.push_back(actualSegment);
			}
		}
*/
	}
	source.close();

	for(int i=0;i<tmp_program.size();i++){
		for(int j=0;j<level_plus.size();j++){
			if(tmp_program[i]==level_plus[j]){
				try{
					program.push_back(Statement(tmp_program[i],level,index_on_level[level]));
					level++; index_on_level[level-1]++;
				}
				catch(std::out_of_range e){
					index_on_level.push_back(1);
					program.push_back(Statement(tmp_program[i],level,index_on_level[level]));
					level++;
				}
				gotCoincidence=true;
			}
		}
		for(int j=0;j<level_minus.size();j++){
			if(tmp_program[i]==level_minus[j]){
				level--; index_on_level[level]--;
				program.push_back(Statement(tmp_program[i],level,index_on_level[level]));
				gotCoincidence=true;
			}
		}
		if(!gotCoincidence){
			program.push_back(Statement(tmp_program[i],level,index_on_level[level]));
			gotCoincidence=false;
		}
	}
}

int main(int argc, char *argv[]){
	string curr_program = argv[0];
	string fileName = argv[1];
/*
	cout<<"File name: ";
	cin>>fileName;
	cout<<endl;
*/
	read(fileName);
/*	for(int i=0;i<program.size();i++){
		cout<<program[i]<<endl;
	}
*/
	run(fileName);

	return 0;
}