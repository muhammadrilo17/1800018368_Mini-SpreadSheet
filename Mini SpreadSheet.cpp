#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <fstream>
using namespace std;

ofstream myfile;
ifstream ifile;
	
void cls(){system("cls");}
void gotoxy(int x, int y){
	COORD coord;
	coord.X =x;
	coord.Y =y+1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void header(string title){
	cls();
	cout<<"===================================================================================================================="<<endl;
	cout<<"===================================================================================================================="<<endl;
	cout<<"                                           MINI SPREADSHEET         "<<endl;
	cout<<"                                 LAST PROJECT ALGORITHM AND PROGRAMMING                                            "<<endl;
	cout<<"                             INTERNATIONAL CLASS OF INFORMATICS ENGINEERING                                        "<<endl;
	cout<<"===================================================================================================================="<<endl;
	cout<<"                                             "<<title<<endl;
	cout<<"                             	      Not Allowed to using space  "<<endl;
	cout<<"===================================================================================================================="<<endl;
}
void readvalue(int a[10][10]){
	myfile.open("value.txt");
	for(int i=0;i<10;i++){
		for(int c=0;c<10;c++){
			myfile<<a[i][c]<<endl;
		}
	}
	myfile.close();
}
void read(int a[10][10]){
	char column='A';
	myfile.open("spreadsheet.txt");
		for(int i=0;i<10;i++){
			if(i==0)myfile<<setw(10)<<column;
			else myfile<<setw(5)<<column;
			column++;
		}
		myfile<<endl;
		myfile<<"_____________________________________________________________";
		myfile<<endl<<"     |"<<endl;
		for(int i=0;i<10;i++){
			myfile<<setw(2)<<i+1<<"   | ";
			for(int c=0;c<10;c++){
				if(c==0){
					myfile<<setw(3)<<a[i][c];
				}
				else{
					myfile<<setw(5)<<a[i][c];
				}
			}
			myfile<<endl;
			myfile<<"     |"<<endl;
		}
	myfile.close();
}
void result(int a[10][10]){
	char column = 'A';
	for(int i=0;i<10;i++){
		if(i==0)cout<<setw(10)<<column;
		else cout<<setw(5)<<column;
		column++;
	}
	cout<<endl;
	cout<<"_____________________________________________________________";
	cout<<endl<<"     |"<<endl;
	for(int i=0;i<10;i++){
		cout<<setw(2)<<i+1<<"   | ";
		for(int c=0;c<10;c++){
			if(c==0){
				cout<<setw(3)<<a[i][c];
			}
			else{
				cout<<setw(5)<<a[i][c];
			}
		}
		cout<<endl;
		cout<<"     |"<<endl;
	}
}
int main(int argc, char** argv) {
	system("mode con cols=120 lines=40");
	
	int b, indexcode, maxlength, indexkoma, fixcolumn, fixcolumn1, fixrow, fixrow1,fixvalue;
	int nilai[10][10], sortindex, temp, key;
	string pil, Action, instructions, instructionsvalue,findrow,findcolumn,findvalue;
	char column;
	bool found, calculate;
	
	for(int i=0;i<10;i++){
		for(int c=0;c<10;c++){
			nilai[i][c]=0;
		}
	}
	int y;
	string kata;
	ifstream ifile;
	ifile.open("value.txt");
	for(int i=0;i<10;i++){
		for(int c=0;c<10;c++){
			getline(ifile,kata);
			y = atoi(kata.c_str());
			nilai[i][c] = y;
		}
	}
	myfile.close();
	do{
		try{
			header("    HOME");
			cout<<"Menu"<<endl;
			cout<<"1. View Sheet"<<endl;
			cout<<"2. Print Sheet"<<endl;
			cout<<"3. Functions"<<endl;
			cout<<"Choose       : ";cin>>pil;
			if(pil=="1"){
				readvalue(nilai);
				read(nilai);
				header(" View Sheet");
				cout<<endl;
				result(nilai);
			}
			else if(pil=="2"){
				readvalue(nilai);
				read(nilai);
				header(" Print Sheet");
				cout<<endl;
				result(nilai);
				system("spreadsheet.txt");
			}
			else if(pil=="3"){
				do{
					header("  Functions");
					cout<<endl;
					result(nilai);
					gotoxy(62,9);cout<<"Function          Instruction            Example"<<endl;
					gotoxy(62,11);cout<<"Insert Value      set(cell,value)        set(A3,10)"<<endl;
					gotoxy(62,12);cout<<"Delete Value      del(cell)              del(B4)"<<endl;
					gotoxy(62,13);cout<<"Addition          sum(firstcell          sum(A1,A10)"<<endl;
					gotoxy(62,14);cout<<"                  ,secondcell)                     "<<endl;
					gotoxy(62,15);cout<<"Searching Data    search(value)          search(10)"<<endl;
					gotoxy(62,16);cout<<"Sorting           sort(column/row,1/0)   sort(A,1)"<<endl;
					gotoxy(62,17);cout<<"(1 for Ascending, 		       sort(10,0)"<<endl;
					gotoxy(62,18);cout<<"0 for Descending)									"<<endl;
					gotoxy(62,19);cout<<"Average           mean(column/row)       mean(A)/mean(2)"<<endl;
					gotoxy(62,20);cout<<"Min Value         min(column/row)        min(A)/min(8)"<<endl;
					gotoxy(62,21);cout<<"Max Value         max(column/row)        max(C)/max(8)"<<endl;
					try{
						gotoxy(62,23);cout<<"Input Instruction : ";cin>>Action;
						found = false; calculate = false;
						for(int i=0;(i<7 && !found);i++){
							if(Action.at(i)=='('){
								indexcode = i;
								found = true;
							}
						}
						for(int i=0;i<Action.length();i++){
							Action.at(i) = toupper(Action.at(i));   //set(d2,10)     //del(c9)
						}											//search(d1,45)
						instructions = Action.substr(0,indexcode); //search
						for(int i=0;i<instructions.length();i++){
							instructions.at(i) = tolower(instructions.at(i));
						}
						indexkoma=0;		
						found=false;
						maxlength = (Action.length()-(indexcode+1))-1;
						instructionsvalue=Action.substr(indexcode+1,maxlength);
						if(instructions=="set"){
							for(int i=0;i<instructionsvalue.length()&&!found;i++){
								if(instructionsvalue.at(i)==','){
									indexkoma = i;
									found = true;
								}
							}	
							findcolumn = toupper(instructionsvalue.at(0));
							findrow = instructionsvalue.substr(1,indexkoma-1);
							findvalue = instructionsvalue.substr(indexkoma+1);
							column='A';
							for(int i=0;i<10;i++){
								if(findcolumn.at(0)==column){
									fixcolumn = i;
								}	
								column++;	
							}
							fixrow = atoi(findrow.c_str());
							fixrow = fixrow-1;
							fixvalue = atoi(findvalue.c_str());
							nilai[fixrow][fixcolumn] = fixvalue;
						}
						else if(instructions=="del"){
							instructionsvalue = Action.substr(indexcode+1,maxlength);
							findcolumn = toupper(instructionsvalue.at(0));
							findrow = instructionsvalue.substr(1,indexkoma-1);
							column='A';
							for(int i=0;i<10;i++){
								if(findcolumn.at(0)==column){
									fixcolumn = i;
								}
								column++;
							}
							fixrow = atoi(findrow.c_str());
							fixrow = fixrow-1;
							nilai[fixrow][fixcolumn]=0;
						}
						else if(instructions=="sum"){
							int result;
							string firstinstructions, lastinstructions;
							for(int i=0;i<instructionsvalue.length()&&!found;i++){
								if(instructionsvalue.at(i)==','){
									indexkoma = i;
									found = true;
								}
							}
							firstinstructions = instructionsvalue.substr(0,indexkoma);
							lastinstructions = instructionsvalue.substr(indexkoma+1);
							gotoxy(62,24);cout<<"Addition from "<<firstinstructions<<" until "<<lastinstructions<<endl;
							found = false;
							if(firstinstructions.at(0)==lastinstructions.at(0)){
								column='A';
								for(int i=0;i<10&&!found;i++){
									if(column==firstinstructions.at(0)){
										sortindex = i;
										found = true;
									}
									column++;
								}
								firstinstructions = firstinstructions.substr(1);
								lastinstructions = lastinstructions.substr(1);
							}
							result = 0;
							if(found){
								fixrow=atoi(firstinstructions.c_str());
								fixrow1=atoi(lastinstructions.c_str());
								if(fixrow<fixrow1){
									for(int i=fixrow1-1;i>=fixrow-1;i--){
										result += nilai[i][sortindex];
									}
								}
								else if(fixrow>fixrow1){
									for(int i=fixrow-1;i>=fixrow1-1;i--){
										result += nilai[i][sortindex];
									}
								}
								gotoxy(62,25);cout<<"is "<<result;
							}
							else{
								found = false;
								column = 'A';
								for(int i=0;i<10&&!found;i++){
									if(column==firstinstructions.at(0)){
										fixcolumn = i;
										found = true;
									}
									column++;
								}
								found = false;
								column = 'A';
								for(int i=0;i<10&&!found;i++){
									if(column==lastinstructions.at(0)){
										fixcolumn1 = i;
										found = true;
									}
									column++;
								}
								result = 0;
								firstinstructions = firstinstructions.substr(1);
								lastinstructions = lastinstructions.substr(1);
								if(firstinstructions==lastinstructions){
									sortindex = atoi(firstinstructions.c_str())-1;
									if(fixcolumn<fixcolumn1){
										for(int i=fixcolumn1;i>=fixcolumn;i--){
											result += nilai[sortindex][i];
										}
									}
									else if(fixcolumn>fixcolumn1){
										for(int i=fixcolumn;i>=fixcolumn1;i--){
											result += nilai[sortindex][i];
										}
									}
									gotoxy(62,25);cout<<"is "<<result;
								}
								else{
									gotoxy(62,25);cout<<"First row and last row not same"<<endl;
								}
							}
						}
						else if(instructions=="search"){
							findvalue = instructionsvalue;
							fixvalue = atoi(findvalue.c_str());
							found = false;
							int position = 1;
							for(int i=0;i<10;i++){
							column='A';
								for(int c=0;c<10;c++){
									if(fixvalue==nilai[i][c]){
										gotoxy(54+(++position*4),26);cout<<column<<i+1<<endl;
										found = true;
									}
									column++;
								}
							}
							if(!found){
								gotoxy(62,25);cout<<"The number not found"<<endl;
							}
							else{
								gotoxy(62,25);cout<<"The number is found in"<<endl;
							}
						}
						else if(instructions=="sort"){
							for(int i=0;i<instructionsvalue.length()&&!found;i++){
								if(instructionsvalue.at(i)==','){
									indexkoma = i;
									found = true;
								}
							}
							found = false;
							if(instructionsvalue.at(0)>='A'&&instructionsvalue.at(0)<='J'){	
							findcolumn = instructionsvalue.at(0);
							column = 'A';
								for(int i=0;i<10&&!found;i++){
									if(column==instructionsvalue.at(0)){
										sortindex = i;
										found=true;
									}
									column++;
								}
								if(instructionsvalue.at(indexkoma+1)=='1'){
									for(int i=1;i<10;i++){
										key=nilai[i][sortindex];
										int j = i-1;
										while(j>=0 && nilai[j][sortindex]>key){
											nilai[j+1][sortindex]=nilai[j][sortindex];
											j=j-1;
										}
										nilai[j+1][sortindex] = key;
									}				
								}
								else if(instructionsvalue.at(indexkoma+1)=='0'){
									for(int i=1;i<10;i++){
										key=nilai[i][sortindex];
										int j = i-1;
											while(j>=0 && nilai[j][sortindex]<key){
											nilai[j+1][sortindex]=nilai[j][sortindex];
											j=j-1;
										}
										nilai[j+1][sortindex] = key;
									}
								}			
							}
							else if(instructionsvalue.at(0)>='1'&&instructionsvalue.at(0)<='9'){
								findrow = instructionsvalue.substr(0,indexkoma);
								fixrow=atoi(findrow.c_str())-1;
								if(instructionsvalue.at(indexkoma+1)=='1'){
									for(int i=1;i<10;i++){
										key=nilai[fixrow][i];
										int j = i-1;
										while(j>=0 && nilai[fixrow][j]>key){
											nilai[fixrow][j+1]=nilai[fixrow][j];
											j=j-1;
										}
										nilai[fixrow][j+1] = key;
									}
								}
								else if(instructionsvalue.at(indexkoma+1)=='0'){
									for(int i=1;i<10;i++){
										key=nilai[fixrow][i];
										int j = i-1;
										while(j>=0 && nilai[fixrow][j]<key){
											nilai[fixrow][j+1]=nilai[fixrow][j];
												j=j-1;
										}
										nilai[fixrow][j+1] = key;
									}
								}
							}			
								
						}		
						else if(instructions=="mean"){
							float mean;
							if(instructionsvalue.at(0)>='A'&&instructionsvalue.at(0)<='J'){	
								column = 'A';
								for(int i=0;i<10&&!found;i++){
									if(column==instructionsvalue.at(0)){
										sortindex = i;
										found=true;
									}
									column++;
								}
								mean=0;
								for(int i=0;i<10;i++){	
									mean += nilai[i][sortindex];	
								}
								mean = mean/10;
								gotoxy(62,25);cout<<"Average of column "<<instructionsvalue<<" is "<<mean;
							}
							else if(instructionsvalue.at(0)>='1'&&instructionsvalue.at(0)<='9'){
								mean=0;
								findrow = instructionsvalue;
								fixrow = atoi(findrow.c_str())-1;
								for(int i=0;i<10;i++){
									mean += nilai[fixrow][i];
								}
								mean = mean/10;
								gotoxy(62,25);cout<<"Average of row "<<instructionsvalue<<" is "<<mean;
							}
						}	
						else if(instructions=="min"){
							int min;
							if(instructionsvalue.at(0)>='A'&&instructionsvalue.at(0)<='J'){	
								column = 'A';
								for(int i=0;i<10&&!found;i++){
									if(column==instructionsvalue.at(0)){
										sortindex = i;
										found=true;
									}
									column++;
								}
								min = nilai[0][sortindex];
								for(int i=0;i<10;i++){
									if(min>nilai[i][sortindex]){
										min = nilai[i][sortindex];
									}
								}
								gotoxy(62,25);cout<<"Min number in row "<<instructionsvalue<<" is "<<min;
							}
							else if(instructionsvalue.at(0)>='1'&&instructionsvalue.at(0)<='9'){	
								findrow = instructionsvalue;
								fixrow = atoi(findrow.c_str())-1;
								min = nilai[fixrow][0];
								for(int i=0;i<10;i++){
									if(min>nilai[fixrow][i]){
										min = nilai[fixrow][i];
									}
								}
								gotoxy(62,25);cout<<"Min number in row "<<instructionsvalue<<" is "<<min;
							}
						}				
						else if(instructions=="max"){
							int max;
							if(instructionsvalue.at(0)>='A'&&instructionsvalue.at(0)<='J'){	
								column = 'A';
								for(int i=0;i<10&&!found;i++){
									if(column==instructionsvalue.at(0)){
										sortindex = i;
										found=true;
									}
									column++;
								}
								max = nilai[0][sortindex];
								for(int i=0;i<10;i++){
									if(max<nilai[i][sortindex]){
										max = nilai[i][sortindex];
									}
								}
								gotoxy(62,25);cout<<"Max number in row "<<instructionsvalue<<" is "<<max;
							}
							else if(instructionsvalue.at(0)>='1'&&instructionsvalue.at(0)<='9'){	
								findrow = instructionsvalue;
								fixrow = atoi(findrow.c_str())-1;
								max = nilai[fixrow][0];
								for(int i=0;i<10;i++){
									if(max<nilai[fixrow][i]){
										max = nilai[fixrow][i];
									}
								}
								gotoxy(62,25);cout<<"Max number in row "<<instructionsvalue<<" is "<<max;
							}
						}	
						else{
							gotoxy(62,29);cout<<"My Apologize, the program does'nt have "<<instructions<<" function"<<endl;
						}
						gotoxy(0,9);result(nilai);	
					}
					catch(...){
						gotoxy(62,24);cout<<"CHECK YOUR INPUT"<<endl;
					}
					readvalue(nilai);
					read(nilai);
					gotoxy(62,30);cout<<"Do you want to input again? Y/N";gotoxy(62,31);cin>>pil;
				}while(pil=="y"||pil=="Y");
			}
			else{
				cout<<"Not Choice"<<endl;
			}		
		}
		catch(...){
			gotoxy(62,24);cout<<"CHECK YOUR INPUT"<<endl;
		}
		gotoxy(62,33);cout<<"Do you want to back home again? Y/N"<<endl;gotoxy(62,34);cin>>pil;
	}while(pil=="y"||pil=="Y");
	return 0;
}
