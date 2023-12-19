#include <iostream>
using namespace std;
#define size 20

template<class T>
class mystack
{
T arr[size];
int top;

public:
mystack()
{
//arr=new T[size];
top=-1;
}

void push(T x)
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

T Top()
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
};

int precedence(char c)
{
int a=0;
if(c=='^')
{
a=3;
}
else if(c=='*' || c=='/')
{
a=2;
}
else if(c=='+' || c=='-')
{
a=1;
}
return a;
}

string infixtopost(string infix)
{
mystack<char> s1;
string a="";
int n=infix.length();
for(int i=0;i<n;i++)
{
char d=infix[i];
if(d=='(')
{
s1.push(d);
}
else if(d=='+' || d=='-' || d=='*' || d=='/')
{
char c=s1.Top();
if(c=='+' || c=='-' || c=='*' || c=='/')
{
while(precedence(c)>=precedence(d) && s1.empty()!=true && c!='(')
{
c=s1.Top();
a+=c;
s1.pop();
}
s1.push(d);
}
else
{
s1.push(d);
}
}
else if(d==')')
{
char c=s1.Top();
while(c!='(')
{
a+=c;
s1.pop();
c=s1.Top();
}
s1.pop();
}
else
{
a+=d;
}
}
while(s1.empty()!=true)
{
char c=s1.Top();
a+=c;
s1.pop();
}
return a;
}

int evaluation(string s)
{
mystack<int> s2;
int ans=0;
int n=s.length();
for(int i=0;i<n;i++)
{
char e=s[i];
if(e>='0' && e<='9')
{
int a=e-48;
// cout<<a<<"\n";
s2.push(a);
}
else
{
int b=s2.Top();
s2.pop();
int c=s2.Top();
s2.pop();
if(e=='*')
{
int d=b*c;
s2.push(d);
}
else if(e=='/')
{
int d=c/b;
s2.push(d);
}
else if(e=='+')
{
int d=b+c;
s2.push(d);
}
else if(e=='-')
{
int d=c-b;
s2.push(d);
}
else if(e=='^')
{
int d=c^b;
s2.push(d);
}
}
}
ans=s2.Top();
return ans;
}

int main() {
char ch;
do {
string s,d;
int e;
cout << "\nEnter the expression :" << endl;
cin >> s;
d = infixtopost(s);
cout << "\nThe postfix expression is : "<< endl;
cout << d << endl;
e = evaluation(d);
cout << "\nThe evaluation is :" <<endl;
cout << e << endl;
cout << "\nDo you want to continue(y/n) :" << endl;
cin >> ch;
} while (ch == 'y' || ch == 'Y');
return 0;
}
