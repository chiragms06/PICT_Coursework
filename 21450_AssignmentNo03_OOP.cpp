//============================================================================
// Name        : b.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Publication
{
protected:
	string title;
	float price;
public:
	void getdata(){
		cout << "\nEnter the name of the book :" << endl;
		cin >> title;
		cout << "\nEnter the price of the book :" << endl;
		cin >> price;
	}

	void display(){
		cout << "Title :" << title <<endl;
		try{
			if(price < 0)
				throw price;
		}
		catch(float a){
			cout << "\nError : Entered price is invalid" << endl;
		    price = 0.0;
		}

		cout << "Price :" << price << endl;
	}
};

class Book : public Publication
{
public:
	int page_count;

	void getdata2(){
		getdata();
		cout << "\nEnter the number of pages :" << endl;
		cin >> page_count;
	}

	void display2(){
		display();
		try{
			if(page_count < 0)
				throw page_count;
		}
		catch(int b){
				cout << "\nError : Entered page count is invalid" << endl;
				page_count = 0;
			}
		cout << "Number of pages :" << page_count << endl;
	}
};

class Tape : public Publication
{
public:
	float playing_time;

	void getdata3(){
		cout << "\nEnter the playing time in seconds :" << endl;
		cin >> playing_time;
	}

	void display3(){
		try{
			if(playing_time < 0)
				throw playing_time;
		}
		catch(float c){
			cout << "\nError : Entered playing time is invalid" << endl;
			playing_time = 0.0;
		}
		cout << "Playing time :" << playing_time << endl;
	}
};

int main(){
	int option;
	char choice;
	Book b;
	Tape t;

    do{

    	cout << "\n-----OPTIONS MENU-----" << endl;
    	cout << "\n1.Book" << endl;
    	cout << "\n2.Tape" << endl;
    	cout << "\nEnter your option :" << endl;
    	cin >> option;


		switch(option){
		case 1:
			b.getdata2();
			b.display2();
			break;

		case 2:
			t.getdata3();
			t.display3();
			break;

		default:
			cout << "OOPS!! Invalid choice.";
			break;
		}
		cout << "\nDo you want to continue?(Y/N)\n";
		cin >> choice;
	}while(choice == 'Y' || choice == 'y');
    cout << "Thank you! Have a nice day!";
	return 0;
}
