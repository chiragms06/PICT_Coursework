#include <iostream>
using namespace std;
class node
{
private:
	int data;
	node *next;

	node()
	{
		data = 0;
		next = NULL;
	}
	node(int x)
	{
		data = x;
		next = NULL;
	}
	friend class set;
};

class set
{
private:
	node *start;
	node *last;
public:
	set()
	{
		start = NULL;
		last = NULL;
	}

private:
	void insertrear(int rollnum)
	{
		if (start == NULL)
		{
			node *insert = new node(rollnum);
			start = last = insert;
		}
		else
		{
			node *insert = new node(rollnum);
			last->next = insert;
			last = insert;
		}
	}

public:
	void createset()
	{
		int n = 0;
		cout << "How many elements do you want ?";
		cin >> n;
		int rollnum = 0;
		for (int i = 0; i < n; i++)
		{
			cout << "Roll num >";
			cin >> rollnum;
			if (start == NULL)
			{
				insertrear(rollnum);
			}
			else
			{
				node *temp = start;
				bool present = false;
				while (temp != NULL)
				{
					if (rollnum == temp->data)
					{
						present = true;
						break;
					}
					temp = temp->next;
				}
				if (present == false)
				{
					insertrear(rollnum);
				}
			}
		}
	}

	void createset(set &uni){
		int count =0;

		createset();
		node *temp2 = this->start;
		while(temp2!=NULL){
			bool present = false;
			node *temp1  = uni.start;
			while(temp1!=NULL){
				if(temp2->data == temp1->data){
					present = true;
					break;
				}
				else{
					temp1 = temp1->next;
				}
			}
			if(present == false){
				uni.insertrear(temp2->data);
				count++;
			}
			temp2=temp2->next;
		}
		if(count!=0){
			cout<<endl;
			cout<<count<<" values were updated in universal"<<endl;
			cout<<"Universal = ";
			uni.print();
			cout<<endl;
		}
	}

	set intersection(set s)
	{
		set result;
		node *temp = start;
		while (temp != NULL)
		{
			node *temp1 = s.start;
			bool unioun = false;
			while (temp1 != NULL)
			{
				if (temp->data == temp1->data)
				{
					unioun = true;
					break;
				}
				temp1 = temp1->next;
			}
			if (unioun == true)
			{
				result.insertrear(temp->data);
			}
			temp = temp->next;
		}
		return result;
	}

	set unioun(set s)
	{
		set result;
		node *temp = start;
		node *temp1 = s.start;
		while (temp != NULL)
		{
			result.insertrear(temp->data);
			temp = temp->next;
		}
		while (temp1 != NULL)
		{
			node *temp2 = result.start;
			bool present = false;
			while (temp2 != NULL)
			{
				if (temp1->data == temp2->data)
				{
					present = true;
					break;
				}
				temp2 = temp2->next;
			}
			if (present == false)
			{
				result.insertrear(temp1->data);
			}
			temp1 = temp1->next;
		}
		return result;
	}

	set custom(set s, set uni)
	{
		set intersection = this->intersection(s);
		node *temp = uni.start;
		set result;
		while (temp != NULL)
		{
			bool present = false;
			node *temp1 = intersection.start;
			while (temp1 != NULL)
			{
				if (temp->data == temp1->data)
				{
					present = true;
					break;
				}
				temp1 = temp1->next;
			}
			if (present == false)
			{
				result.insertrear(temp->data);
			}
			temp = temp->next;
		}
		return result;
	}

	set complement_unioun(set s, set uni)
	{
		set unioun = this->unioun(s);
		set result;
		node *temp = uni.start;

		while (temp != NULL)
		{
			bool present = false;
			node *temp1 = unioun.start;
			while (temp1 != NULL)
			{
				if (temp->data == temp1->data)
				{
					present = true;
					break;
				}
				temp1 = temp1->next;
			}
			if (present == false)
			{
				result.insertrear(temp->data);
			}
			temp = temp->next;
		}
		return result;
	}

	void deleteset(){
		node *temp = start;
		if(temp==NULL){
			return;
		}
		else{
			while(temp!=NULL){
				start = temp->next;
				delete(temp);
				temp = start;
			}
		}
	}

	int count(){
		node *temp = start;
		int count=0;
		while(temp!=NULL){
			count++;
			temp = temp->next;
		}
		return count;
	}

	void print()
	{
		node *temp = start;
		cout<<"[";
		while (temp != NULL)
		{
			cout << temp->data<<" ";
			temp = temp->next;
		}
		cout<<"]";
	}
};

int main()
{
	set universal,vanilla,butters,result;
	cout<<"For UNIVERSAL SET"<<endl;
	universal.createset();
	cout<<"Universal = ";
	universal.print();
	cout<<endl;
	cout<<"For students who like VANILLA"<<endl;
	vanilla.createset(universal);
	cout<<"Vanilla = ";
	vanilla.print();
	cout<<endl;
	cout<<"For students who like BUTTERSCOTCH"<<endl;
	butters.createset(universal);
	cout<<"Butterscotch = ";
	butters.print();
	cout<<endl;
	int repeat = 1;
	do{
		int choice = 0;
		cout<<"1->Set of students who like both vanilla and butterscotch"<<endl;
		cout<<"2->Set of students who like either vanilla or butterscotch or not both"<<endl;
		cout<<"3->Number of students who like neither vanilla nor butterscotch"<<endl;
		cout<<">";
		cin>>choice;
		switch(choice){
			case 1:{
				result = vanilla.intersection(butters);
				cout<<"Result = ";result.print();
				cout<<endl;
				result.deleteset();
				break;
			}
			case 2:{
				result = vanilla.custom(butters,universal);
				cout<<"Result = ";result.print();
				cout<<endl;
				result.deleteset();
				break;
			}
			case 3:{
				result = vanilla.complement_unioun(butters,universal);
				cout<<"Result = ";result.print();
				cout<<"\nNumber of students are :"<<result.count();
				cout<<endl;
				result.deleteset();
				break;
			}
		}
		cout<<"\nEnter 1 to repeat :";
		cin>>repeat;
		cout<<endl;
	}while(repeat==1);
}



