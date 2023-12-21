#include<iostream>
using namespace std;

class SeatNode{

	int seatno;
	bool booking_status;
	SeatNode *next , *prev;
	friend class CineMax;

public:

	SeatNode(){

		seatno=0;
		booking_status=false;
		next=NULL;
		prev=NULL;

	}

	SeatNode(int x){

		seatno=x;
		booking_status=false;
		next=NULL;
		prev=NULL;
	}

	SeatNode(int x,bool s){

		seatno=x;
		booking_status=s;
		next=NULL;
		prev=NULL;
	}

};

class CineMax{

	SeatNode* header[10];

public:

	CineMax(){

		for(int i=0;i<=9;i++){

			header[i]=NULL;
		}

	}

	void createTheater(){

		for(int i=0;i<10;i++){

			SeatNode* ns=new SeatNode(i*7+1);

			header[i]=ns;
			ns->next=ns;
			ns->prev=header[i];
			SeatNode* prevseat=ns;

			for(int j=1;j<7;j++){

				SeatNode* ns1=new SeatNode(i*7+j+1);
				ns1->prev=prevseat;
				prevseat->next=ns1;
				prevseat=ns1;
			}


		}
	}

	void display(){

		for(int i=0;i<10;i++){

			SeatNode *temp=header[i];

			while(temp->next != NULL){

				cout<<temp->seatno<<" "<<temp->booking_status<<"  ";
				temp=temp->next;
			}
			cout<<temp->seatno<<" "<<temp->booking_status<<"  ";
			cout<<"\n";

		}
	}

	void booking(int n1){

		if(n1>70){

			cout<<"\nINVALID\n";
		}

		else{

			int row;
			int col;

			row=n1/7;
			col=n1%7;

			SeatNode* ns=header[row];

			while(col>1)
			{
				col--;
				ns=ns->next;

			}

			if(ns->booking_status==true){

				cout<<"\nAlready Booked\n"<<endl;
			}

			else{

				ns->booking_status=true;
				cout<<"\nSeat Booked\n"<<endl;
			}

		}
	}

	void cancelling(int n2){

		if(n2>70){

			cout<<"\nINVALID\n";
		}

		else{

			int row;
			int col;

			row=n2/7;
			col=n2%7;

			SeatNode* ns=header[row];

			while(col>1)
			{
				col--;
				ns=ns->next;

			}

			if(ns->booking_status==true){

				cout<<"\nSeat Cancled\n"<<endl;
				ns->booking_status=false;

			}

			else{

				ns->booking_status=false;
				cout<<"\nAlready Cancled\n"<<endl;
			}

		}
	}

};

int main(){

	CineMax x;
	x.createTheater();
	x.display();

	int flag=1,in;

	while(flag==1){

		cout<<"\nPress 1 for Booking of tickets or Press 2 for cancelation of tickets\n"<<endl;
		cin>>in;

		if(in==1){

			int n1,seat_no1;

			cout<<"\nEnter no. of seats you want to book: ";
			cin>>n1;

			for(int i=0;i<n1;i++){

				cout<<"\nEnter the seat no. you have to book: ";
				cin>>seat_no1;

				x.booking(seat_no1);
				x.display();
			}


		}

		else if(in==2){

			int n2,seat_no2;

			cout<<"\nEnter no. of seats you want to cancel: ";
			cin>>n2;

			for(int i=0;i<n2;i++){

				cout<<"\nEnter the seat no. you have to cancel: ";
				cin>>seat_no2;

				x.cancelling(seat_no2);
				x.display();
			}

		}

		else{

			cout<<"\nInvalid Input\n";
		}


	}

	return 0;
}
