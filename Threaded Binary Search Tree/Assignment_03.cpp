#include<iostream>
using namespace std;

class Node
{
    int data;
    Node *left,*right;
    int lbit,rbit;

    public:
    Node()
    {
        data=0;
        left=right=NULL;
        lbit=rbit=0;
    }

    Node(int x)
    {
        data=x;
        left=right=NULL;
        lbit=rbit=0;
    }

    void display()
    {
        cout<<lbit<<"|"<<data<<"|"<<rbit<<endl;
    }
    friend class TBST;
};

class TBST
{
    Node *root,*header;

    public:
    TBST()
    {
        root=header=NULL;
    }

    void insert(int x)
    {
        if(root==NULL)
        {
            header=new Node(-99);
            header->right=header;
            root=new Node(x);
            root->left=header;
            root->right=header;
            header->left=root;
        }
        else
        {
            Node* ptr=root;
            Node* temp=new Node(x);
            while(1)
            {
                if(ptr->data>x)
                {
                    if(ptr->lbit!=0)
                    {
                        ptr=ptr->left;
                    }
                    else
                    {
                        temp->left=ptr->left;
                        temp->right=ptr;
                        ptr->lbit=1;
                        ptr->left=temp;
                        return;
                    }
                }
                else if(ptr->data<x)
                {
                    if(ptr->rbit!=0)
                    {
                        ptr=ptr->right;
                    }
                    else
                    {
                        temp->left=ptr;
                        temp->right=ptr->right;
                        ptr->right=temp;
                        ptr->rbit=1;
                        return;
                    }
                }
                else
                {
                    cout<<"Duplicate entries not allowed"<<endl;
                    break;
                }
            }
        }
    }

    void inorder()
    {
        Node* temp=root;
        while(temp->lbit!=0)
        {
            temp=temp->left;
        }
        while(temp!=header)
        {
            temp->display();
            if(temp->rbit!=0)
            {
                temp=temp->right;
                while(temp->lbit!=0)
                {
                    temp=temp->left;
                }
            }
            else
            {
                temp=temp->right;
            }
        }
    }

    void preorder()
    {
        Node* temp=root;
        int flag=0;
        while(temp!=header)
        {
            if(flag==0)
            {
                temp->display();
            }
            if(flag==0 && temp->lbit==1)
            {
                temp=temp->left;
            }
            else
            {
                if(temp->rbit==1)
                {
                    flag=0;
                }
                else
                {
                    flag=1;
                }
                temp=temp->right;
            }
        }
    }

    bool search(int x,Node*&temp,Node*&par)
    {
        while(temp!=header)
        {
            if(temp->data==x)
            {
                return true;
            }
            else 
            {
                par=temp;
                if(temp->data>x)
                {
                    temp=temp->left;
                }
                else
                {
                    temp=temp->right;
                }
            }
        }
        return false;
    }

    void del(Node*&t,Node*&p)
    {
        if(t==root)
        {
            if(t->lbit==0 && t->rbit==0)
            {
                delete(t);
                root=NULL;
            }
            else if(t->lbit==1 && t->rbit==0)
            {
                Node* temp=t->left;
                root=temp;
                while(temp->rbit==1)
                {
                    temp=temp->right;
                }
                temp->right=header;
                delete(t);
            }
            else if(t->lbit==0 && t->rbit==1)
            {
                Node* temp=t->right;
                root=temp;
                while(temp->lbit==1)
                {
                    temp=temp->left;
                }
                temp->left=header;
                delete(t);
            }
            else if(t->lbit==1 && t->rbit==1)
            {
                Node* cs=t->right;
                p=t;
                while(cs->lbit==1)
                {
                    p=cs;
                    cs=cs->left;
                }
                t->data=cs->data;
                t=cs;
                del(t,p);
            }
        }
        else
        {
            if(t->lbit==1 && t->rbit==1)
            {
                Node* cs=t->right;
                p=t;
                while(cs->lbit==1)
                {
                    p=cs;
                    cs=cs->left;
                }
                t->data=cs->data;
                t=cs;
                del(t,p);
            }
            else if(t->lbit==0 && t->rbit==0)
            {
                if(p->left==t)
                {
                    p->left=t->left;
                    p->lbit=0;
                }
                else
                {
                    p->right=t->right;
                    p->rbit=0;
                }
                delete(t);
            }
            else if(t->lbit==1 && t->rbit==0)
            {
                Node* temp=t->left;
                if(p->left==t)
                {
                    p->left=temp;
                }
                else
                {
                    p->right=temp;
                }
                while(temp->rbit==1)
                {
                    temp=temp->right;
                }
                temp->right=t->right;
                delete(t);
            }
            else if(t->lbit==0 && t->rbit==1)
            {
                Node* temp=t->right;
                if(p->left==t)
                {
                    p->left=temp;
                }
                else
                {
                    p->right=temp;
                }
                while(temp->lbit==1)
                {
                    temp=temp->left;
                }
                temp->left=t->left;
                delete(t);
            }
            
        }
    }

    Node* getroot()
    {
        return root;
    }
};

int main()
{
	TBST t;
	int op,n,ele;
	char ans;
	do
	{
		cout<<"\n----------MENU----------\n";
		cout<<"\n1.Creation\n2.In-order Traversal\n3.Pre-order Traversal\n4.Delete a node\n";
		cout<<"\n------------------------\n";
		cout<<"Enter your choice :";
		cin>>op;

		switch(op)
		{
		case 1:
			cout<<"\nEnter the number of elements :";
			cin>>n;
			cout<<"Enter the elements :";
			for(int i=0;i<n;i++)
			{
				cin>>ele;
				t.insert(ele);
			}
			cout<<"\nInserted successfully!";
			break;

		case 2:
			cout<<"\nThe in-order traversal is :"<<endl;
			t.inorder();
			break;

		case 3:
			cout<<"\nThe pre-order traversal is :"<<endl;
			t.preorder();
			break;

		case 4:
			{
			cout<<"\nEnter the element to be deleted :";
			cin>>ele;
			Node* parent=NULL;
			Node* temp=t.getroot();
			if(t.search(ele,temp,parent))
			{
				t.del(temp,parent);
				cout<<ele<<" deleted"<<endl;
			}
			else
			{
				cout<<ele<<" not present"<<endl;
			}
			break;
			}

		default:
			cout<<"INVALID CHOICE!"<<endl;
			break;
		}

		cout<<"\nDo you want to continue?(y/n) :";
		cin>>ans;
	}while(ans=='y' || ans=='Y');

	return 0;
}
