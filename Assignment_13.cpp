#include <iostream>
using namespace std;

#define size 10

class Deque
{
    int rear,front,d[size];
   
    public:
   
        Deque()
        {
            rear=-1;
            front=-1;
        }
       
        void insert_front(int x)
        {
            if(front==0)
            {
                cout << "Cannot insert" << endl;
            }
            else
            {
                if(front==-1)
                {
                    front=0;
                    rear=0;
                }
                else
                {
                    front--;
                }
                d[front]=x;
            }
        }
       
        void insert_rear(int x)
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
                d[rear]=x;
            }
        }
       
        void deletion_front()
        {
            if(front==-1 || front==rear+1)
            {
                cout << "Underflow" << endl;
            }
            else
            {
                front++;
            }
        }
       
        void deletion_rear()
        {
            if(front==-1 || front==rear+1)
            {
                cout << "Underflow" << endl;
            }
            else
            {
                rear--;
            }
        }
   
       
        void display()
        {
            for(int i=front;i<=rear;i++)
            {
                cout << d[i] << " ";
            }
            cout << "\n";
        }
};
   
int main()
{
    Deque obj;
    int n,ele,op;
    char ch;
    do
    {
        cout << "\n\n-----MENU-----\n\n";
        cout << "Your options are :" << endl;
        cout << "\n1.Insert at rear\n2.Delete from front\n3.Insert at front\n4.Delete from rear\n";
        cout << "\nEnter your choice :" << endl;
        cin >> op;
       
        switch(op)
        {
            case 1:
            cout << "\nEnter the number of elements :" << endl;
            cin >> n;
            for(int i=0;i<n;i++)
            {
                cout << "Enter the element :" << endl;
                cin >> ele;
                obj.insert_rear(ele);
            }
            cout << "\nThe queue is :" << endl;
            obj.display();
            break;
           
            case 2:
            cout << "\nAfter deleting first element the queue becomes :" << endl;
            obj.deletion_front();
            obj.display();
            break;
           
            case 3:
            cout << "\nEnter the element to be inserted at front :" << endl;
            cin >> ele;
            cout << "\nAfter inserting element at front the queue becomes :" << endl;
            obj.insert_front(ele);
            obj.display();
            break;
       
            case 4:
            cout << "\nAfter deleting last element the queue becomes :" << endl;
            obj.deletion_rear();
            obj.display();
            break;

            default:
            cout << "\nINVALID CHOICE" << endl;
            break;
        }
        cout << "\nDo you want to continue?(y/n) :" << endl;
        cin >> ch;
    }while(ch=='y' || ch=='Y');
   
    cout << "\n\n-----THANK YOU-----\n\n";

    return 0;
}
