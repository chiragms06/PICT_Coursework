#include <iostream>
using namespace std;

#define size 10

class mystack
{
char* arr;
int top;

public:
mystack()
{
arr=new char[size];
top=-1;
}

void push(char x)
{
if(top==size-1)
{
cout << "Stack overflow" << endl;
}
else
{
top++;
arr[top]=x;
}
}

void pop()
{
if(top==-1)
{
cout << "No element to pop" << endl;
}
else
{
top--;
}
}

char Top()
{
if(top==-1)
{
cout << "No element in stack" << endl;
return -1;
}
else
{
return arr[top];
}
}

bool empty()
{
return top==-1;
}

void display()
{
for(int i=top;i>=0;i--)
{
cout << arr[i] << " ";
}
}

bool check(string exp)
{
mystack s1;
for(int i=0;i<=top;i++)
{
if(exp[i]=='{' || exp[i]=='(' || exp[i]=='[')
{
s1.push(exp[i]);
continue;
}
else if(exp[i]=='}' || exp[i]==')' || exp[i]==']')
{
switch(exp[i])
{
case '}':
if(exp[i]!='{')
{
return false;
}
else
{
s1.pop();
}
break;

case ')':
if(exp[i]!='(')
{
return false;
}
else
{
s1.pop();
}
break;

case ']':
if(exp[i]!='[')
{
return false;
}
else
{
s1.pop();
}
break;
}
}
}
return s1.empty();
}
};

int main()
{
string exp;
char ans;
mystack s;

while(true)
{
cout << "\nEnter the expression :" << endl;
cin >> exp;
if(s.check(exp))
{
cout << "Well parenthesized" << endl;
}
else
{
cout << "Not well parenthesized" << endl;
}
cout << "\nDo you want to continue?(y/n) :" << endl;
cin >> ans;
if(ans=='y' || ans=='Y')
{
continue;
}
else
{
break;
}
}

return 0;
}
