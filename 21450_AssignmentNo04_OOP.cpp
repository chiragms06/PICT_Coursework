//============================================================================
// Name        : file.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

class Student{
	string name;
	int roll_no;

public:
	void getdata(){
		fstream f;
		f.open("std.txt",ios :: app);

		if(!f){
			 cout << "Error in file !!" << endl;
		 }

		cout << "Enter the name :" << endl;
		cin >> name;
		cout << "\nEnter the roll no :" << endl;
		cin >> roll_no;

		f <<"\nHello :" << name << endl << "Roll :" << roll_no << endl;
		f.close();
	}

	void display(){
		fstream f;
		f.open("std.txt",ios :: in);
		string myFile;
		if(!f){
			 cout << "Error in file !!" << endl;
		 }
		while (getline (f, myFile)) {
		   cout << myFile << endl;
		 }

		f.close();
	}
};

int main() {
	 Student s;
	 s.getdata();
	 s.display();
	 return 0;
}
