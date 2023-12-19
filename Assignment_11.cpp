#include <iostream>
using namespace std;

#define size 10

class Queue
{
int rear,front;
int q[size];
public:
Queue()
{
rear=-1;
front=-1;
}

void insert(int x)
{
if(rear==size-1)
{
cout << "Overflow" << endl;
}
else
{
if(front==-1)
{
front=0;
}
rear++;
q[rear]=x;
}
}

void deletion()
{
if(front==-1 || front==rear+1)
{
cout << "Underflow" << endl;
}
else
{
// int x=q[front];
front++;
}
// return x;
}

void display()
{
for(int i=front;i<=rear;i++)
{
cout << q[i] << " ";
}
}
};

int main() {
int ele,n,op;
char ch;
Queue obj;
do
{
cout << "\n\n-----MENU----\n\n";
cout << "Your options are :" << endl;
cout << "\n1.INSERTION\n2.DISPLAY\n3.DELETION\n";
cout << "Enter your choice :" << endl;
cin >> op;

switch(op)
{
case 1:
cout << "Enter the number of elements :" << endl;
cin >> n;
for(int i=0;i<n;i++)
{
cout << "Enter the element :" << endl;
cin >> ele;
obj.insert(ele);
}
break;

case 2:
cout << "\nThe queue is :" << endl;
obj.display();
break;

case 3:
cout << "After deleting first element the queue becomes :" << endl;
obj.deletion();
obj.display();
break;

default:
cout << "\nINVALID CHOICE" << endl;
break;
}
cout << "\nDo you want to continue?(y/n) :" << endl;
cin >> ch;
}while(ch=='y' || ch=='Y');
cout << "\n\n----THANK YOU----\n\n";
return 0;
}
