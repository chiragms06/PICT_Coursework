//============================================================================
// Name        : maps.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <iterator>
using namespace std;

int main() {
	string state;
	long pop;
	char ans;
	int ch;
	map <string,long> mymap;
	map<string,long>::iterator i;

	do{
		cout << "\n-----MENU-----\n";
		cout << "1.Insert\n2.Display\n3.Search\n";
		cout << "Enter your choice :";
		cin >> ch;

		switch(ch){

		case 1:
			cout << "\nEnter the state's name :";
			cin >> state;
			cout << "\nEnter the population :";
			cin >> pop;
			mymap.insert(pair<string,long>(state,pop));
			break;

		case 2:
			cout << "\tSTATE\tPOPULATION" << '\n';
			for(i = mymap.begin(); i != mymap.end(); i++){
				cout << '\t' << i->first << '\t' << i->second << '\n';
			}
			break;

		case 3:
			cout << "\nEnter the state's name for searching its population :";
			cin >> state;

			if(mymap.count(state) == 0){
				cout << "\nState is not present in the list" << endl;
			}
			else{
				cout << "\nPopulation is :" << mymap.find(state)->second;
			}
			break;
		}
		cout << "\nDo you want to continue?(y/n) :";
		cin >> ans;
	}while(ans == 'y' || ans == 'Y');
	cout << "\nThanks for using this program!!";
	return 0;
}
