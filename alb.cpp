#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include <cstdlib>

using namespace std;

static vector<string> program;
void read(string fileName);
void run(string fileName);

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

void read(string fileName){
	ifstream source;
	string actualLine;

	source.open(fileName.c_str(), ios::in);

	while(!source.eof()){
		while(getline(source,actualLine)){
			if(actualLine[0]!='/' && actualLine[1]!='/'){
				actualLine.erase(remove(actualLine.begin(), actualLine.end(), '\t'), actualLine.end());
				stringstream ss(actualLine);
				if(actualLine.find(" ")!=string::npos){
					while(getline(ss,actualLine,' ')){
						program.push_back(actualLine);
					}
				}
				else{
					program.push_back(actualLine);
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
}

void run(string fileName){
	bool began=false;
	int index=0;
	int loopRepeats=0;
	for(int i=0;i<=program.size();i++){
		if(program[i]=="BEGIN" && !began){
			began=true;
		}
		else if(program[i]=="END" && began){
			began=false;
		}
		else if(began){
			if(program[i]=="BEGIN"){
				cout<<"In "<<fileName<<", ERROR 001: 'BEGIN' cannot be used inside another."<<endl;
				exit(0);
			}
			else if(program[i]=="repeat"){
				i++;
				if(program[i]=="infinity"){
					while(true){
						for(index=i+1;program[index]!="ENDLOOP";index++){
							if(program[index]=="out"){
								while(program[index]!=";"){
									index++;
									if(program[index]=="NEWL"){
										cout<<endl;
									}
									else if(program[index]!=";"){
										cout<<program[index]<<" ";
									}
								}
							}
						}
					}
				}
				else{
					loopRepeats = stoi(program[i]);
					for(int j=0;j<loopRepeats;j++){
						index=i+1;
						for(index;program[index]!="ENDLOOP";index++){
							if(program[index]=="out"){
								while(program[index]!=";"){
									index++;
									if(program[index]=="NEWL"){
										cout<<endl;
									}
									else if(program[index]!=";"){
										cout<<program[index]<<" ";
									}
								}
							}
						}
					}
					i=index+1;
				}
			}
			else if(program[i]=="out"){
				while(program[i]!=";"){
					i++;
					if(program[i]=="NEWL"){
						cout<<endl;
					}
					else if(program[i]!=";"){
						cout<<program[i]<<" ";
					}
				}
			}
		}
		else{
			if(program[i]=="END"){
				cout<<"In "<<fileName<<", ERROR 002: 'END' cannot be used before a 'BEGIN' statement."<<endl;
				exit(0);
			}
		}
	}
}