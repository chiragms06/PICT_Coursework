#include<iostream>
using namespace std;

class Complex{
private:
	float real,imag;

public:
	//Default constructor
	Complex(){
		real = 0;
		imag = 0;
	}

	//Overload + operator
	Complex operator + (Complex comp){
		comp.real += real;
		comp.imag += imag;
		return comp;
	}

	//Overload * operator
	Complex operator * (Complex comp){
		comp.real *= real;
		comp.imag *= imag;
		return comp;
	}

	//Overload << operator
	friend ostream &operator<<(ostream &os, Complex &c){
		os << c.real << " +i" << c.imag;
		return os;
	}

	//Overload >> operator
	friend istream &operator>>(istream &is, Complex &c){
		is >> c.real >> c.imag;
		return is;
	}
};

int main()
{
	Complex c1,c2,c3;
	int option;
	char ch;
	do
	{
		cout << "This is a Complex Calculator"
				 << "\nOptions Menu :"
				 << "\n1. Addition"
				 << "\n2. Product"
				 << "\nPlease enter your option :";
			cin >> option;

			switch(option)
				{
				case 1 : //Addition
					cout << "Please enter the real and imaginary part of first complex number.\n";
						cin >> c1;
						cout << "Please enter the real and imaginary part of second complex number.\n";
						cin >> c2;
						c3 = c1 + c2;
						cout << "The addition of both complex numbers is :" << c3;
						break;


				case 2: //Product
					cout << "Please enter the real and imaginary part of first complex number.\n";
						cin >> c1;
						cout << "Please enter the real and imaginary part of second complex number.\n";
						cin >> c2;
						c3 = c1 * c2;
						cout << "The product of both complex numbers is :" << c3;
						break;

				default :
					cout << "\nOOPS!!Invalid option";
					break;
				}
			cout << "\nDo you want to continue?(Y/N)\n";
			cin >> ch;
	}while (ch == 'Y' || ch == 'y');
	return 0;
}





