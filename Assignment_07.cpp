#include <iostream>
using namespace std;

class Node
{
int bit;
Node* next;
Node* prev;

public:
friend class Binaryno;

Node()
{
bit=0;
next=NULL;
prev=NULL;
}
Node(int x)
{
bit=x;
next=NULL;
prev=NULL;
}
};

class Binaryno
{
int n;
Node* start;
Node* last;

public:
Binaryno()
{
n=0;
start=NULL;
last=NULL;
}

void create(int n)
{
while(n!=0)
{
Node* nn=new Node(n%2);
if(start==NULL)
{
start=nn;
last=nn;
}
else
{
nn->next=start;
start->prev=nn;
start=nn;
}
n=n/2;
}
}

void display()
{
Node* temp=start;
while(temp!=NULL)
{
cout << temp->bit << "";
temp=temp->next;
}
// cout << temp->bit << " ";
// temp=temp->next;
}

void insert_at_start(int n)
{
Node* nn=new Node(n%2);
if(start==NULL)
{;
start=nn;
last=nn;
}
else
{
nn->next=start;
start->prev=nn;
start=nn;
}
}

Binaryno comp1()
{
Binaryno b2;
Node* temp=last;
while(temp!=NULL)
{
if(temp->bit==0)
{
b2.insert_at_start(1);
}
else
{
b2.insert_at_start(0);
}
temp=temp->prev;
}
return b2;
}

Binaryno comp2()
{
Binaryno b3;
int carry = 1;
b3 = comp1();
Node * temp = b3.last;
while(temp!=NULL)
{
if(temp->bit==1 && carry == 1)
{
temp->bit= 0;
temp = temp->prev;
// continue;
}
else if(temp->bit==0 && carry == 1)
{
temp->bit= 1;
carry = 0;
break;
}
}
if(carry!=0)
{
b3.insert_at_start(1);
}
return b3;
}

Binaryno operator+(Binaryno b1)
{
Binaryno res;
Node* temp1=last;
Node* temp2=b1.last;
int sum=0,carry=0;
while(temp1!=NULL && temp2!=NULL)
{
sum=temp1->bit+temp2->bit+carry;
if(sum==0)
{
res.insert_at_start(0);
carry=0;
temp1=temp1->prev;
temp2=temp2->prev;
}
else if(sum==1)
{
res.insert_at_start(1);
carry=0;
temp1=temp1->prev;
temp2=temp2->prev;
}
else if(sum==2)
{
res.insert_at_start(0);
carry=1;
temp1=temp1->prev;
temp2=temp2->prev;
}
else if(sum==3)
{
res.insert_at_start(1);
carry=1;
temp1=temp1->prev;
temp2=temp2->prev;
}
while(temp1!=NULL)
{
if(temp1->bit==1)
{
res.insert_at_start(1);
temp1=temp1->prev;
}
else if(temp1->bit==0)
{
res.insert_at_start(0);
temp1=temp1->prev;
}
}
while(temp2!=NULL)
{
if(temp2->bit==1)
{
res.insert_at_start(1);
temp2=temp2->prev;
}
else if(temp2->bit==0)
{
res.insert_at_start(0);
temp2=temp2->prev;
}
}
}
return res;
}
};

int main()
{
int n;
Binaryno b1,b2,b3,b4;

cout << "Enter the decimal number :";
cin >> n;

cout << "\nThe binary equivalent of entered number is :";
b1.create(n);
b1.display();

cout << "\nThe 1's complement is :";
b2=b1.comp1();
b2.display();

cout << "\nThe 2's complement is :";
b3=b1.comp2();
b3.display();

b4=b1+b3;
cout << "\nThe addition is :";
b4.display();
return 0;
}
