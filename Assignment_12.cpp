#include <iostream>
using namespace std;

#define size 5

class Job
{
int p_id,priority;

public:
friend class PrioQueue;

Job()
{
p_id=0;
priority=0;
}

Job(int x,int y)
{
p_id=x;
priority=y;
}

int getp_id()
{
return p_id;
}

int getprio()
{
return priority;
}
};

class PrioQueue
{
Job q[size];
int rear,front;

public:
PrioQueue()
{
front=-1;
rear=-1;
}

void insert(int p_id,int priority)
{
Job j1(p_id,priority);
int j;
if(rear==size-1)
{
cout << "Overflow" << endl;
}
if(front==-1)
{
front=0;
rear=0;
q[rear]=j1;
}
else
{
rear++;
j=rear-1;
}
while(q[j].getprio() < j1.getprio() && j>=0)
{
q[j+1]=q[j];
j=j-1;
}
q[j+1]=j1;
}

void display()
{
cout << "\n-------------------------------\n";
cout << '\t' << "P-ID" << '\t' << "PRIORITY" << endl;
cout << '\n';
for(int i=front;i<=rear;i++)
{
cout <<'\t' << q[i].getp_id() << '\t' << q[i].getprio() <<endl;
}
cout << "\n-------------------------------\n";
}
};

int main()
{
int p_id1,priority1;
PrioQueue p;
int n;
cout << "Enter n :" << endl;
cin >> n;
for(int i=0;i<n;i++)
{
cout << "Enter process ID :" << endl;
cin >> p_id1;
cout << "Enter priority :" << endl;
cin >> priority1;
p.insert(p_id1,priority1);
}
p.display();
return 0;
}
