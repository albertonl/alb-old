#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

static vector<string> program;
void read(string fileName);
void run(string fileName);

int main(){
	string fileName;
	cout<<"File name: ";
	cin>>fileName;
	cout<<endl;

	read(fileName);
	run(fileName);

	return 0;
}

void read(string fileName){
	ifstream source;
	string actualLine;
	source.open(fileName.c_str(), ios::out);

	while(!source.eof()){
		cin>>actualLine;
		program.push_back(actualLine);
	}
	source.close();
}

void run(string fileName){
	bool began=false;
	int index=0;
	int loopRepeats=0;
	for(int i=0;i<program.size();i++){
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
						index=i+1;
						for(index;program[index]!="ENDLOOP";index++){
							if(program[index]=="out"){
								while(program[index]!=";"){
									if(program[index]=="NEWLN"){
										cout<<endl;
									}
									else{
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
									if(program[index]=="NEWLN"){
										cout<<endl;
									}
									else{
										cout<<program[index]<<" ";
									}
								}
							}
						}
					}
					i=index+1;
				}
			}
			if(program[i]=="out"){
				while(program[i]!=";"){
					if(program[i]=="NEWLN"){
						cout<<endl;
					}
					else{
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