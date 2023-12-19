#include<iostream>
using namespace std;
#define size 30

class Node
{
    int data;
    Node *left,*right;

    public:
    Node()
    {
        data=0;
        left=right=NULL;
    }

    Node(int x)
    {
        data=x;
        left=right=NULL;
    }

    friend class BT;
    template<class T>friend class myStack;
    template<class T1>friend class myQueue;
};

template<class T>
class myStack
{
    int top;
    T arr1[size];

    public:
    myStack()
    {
        top=-1;
    }

    bool full()
    {
        if(top==size-1)
        {
            return true;
        }
        return false;
    }

    bool empty()
    {
        if(top==-1)
        {
            return true;
        }
        return false;
    }

    void push(T d)
    {
        if(full())
        {
            cout<<"STACK FULLL"<<endl;
        }
        else
        {
            top++;
            arr1[top]=d;
        }
    }

    T pop()
    {
        T d;
        if(empty())
        {
            cout<<"STACK EMPTY"<<endl;
        }
        else
        {
            d=arr1[top];
            top--;
        }
        return d;
    }

    T Top()
    {
        return arr1[top];
    }

    void display()
    {
        for(int i=top;i>=0;i--)
        {
            cout<<arr1[i]->data<<endl;
        }
    }
};

template<class T>
class myQueue
{
    int f,r;
    T arr2[size];

    public:
    myQueue()
    {
        f=r=-1;
    }

    bool full()
    {
        if(r==size-1)
        {
            return true;
        }
        return false;
    }

    bool empty()
    {
        if(f==-1 && r==-1)
        {
            return true;
        }
        return false;
    }

    void push(T d)
    {
        if(full())
        {
            cout<<"QUEUE FULL"<<endl;
        }
        else if(f==-1 && r==-1)
        {
            f++;
            r++;
            arr2[r]=d;
        }
        else
        {
            r++;
            arr2[r]=d;
        }
    }

    T pop()
    {
        T d;
        if(empty())
        {
            cout<<"QUEUE EMPTY"<<endl;
        }
        else if(f==r)
        {
            d=arr2[f];
            f=-1;
            r=-1;
        }
        else
        {
            d=arr2[f];
            f++;
        }
        return d;
    }

    void display()
    {
        for(int i=f;i<=r;i++)
        {
            cout<<arr2[i]->data<<endl;
        }
    }

};

class BT
{
    Node* root;

    public:
    BT()
    {
        root=NULL;
    }

    void create_itr(int x)
    {
        myQueue <Node*> q;
        Node* nn=new Node(x);
        if(root==NULL)
        {
            root=nn; 
            return;
        }

        q.push(root);
        while(!q.empty())
        {
            Node* temp=q.pop();
            if(temp->left!=NULL)
            {
                q.push(temp->left);
            }
            else
            {
                temp->left=nn;
                return;
            }

            if(temp->right!=NULL)
            {
                q.push(temp->right);
            }
            else
            {
                temp->right=nn;
                return;
            }
        }
    }

    bool flag=false;
    Node* create_rec()
    {
        int x;
        if(flag==false)
        {
            cout<<"Enter root value :"<<endl;
            cin>>x;
            flag=true;
            if(x==-1)
            {
                return NULL;
            }
            root=new Node(x);
            cout<<"Enter left child of "<<x<<" :"<<endl;
            root->left=create_rec();
            cout<<"Enter right child of "<<x<<" :"<<endl;
            root->right=create_rec();
            return root;
        }
        else
        {
            cout<<"Enter data or -1 for no data :"<<endl;
            cin>>x;
            if(x==-1)
            {
                return NULL;
            }
            Node* nn=new Node(x);
            cout<<"Enter left child of "<<x<<" :"<<endl;
            nn->left=create_rec();
            cout<<"Enter right child of "<<x<<" :"<<endl;
            nn->right=create_rec();
            return nn;
        }
    }

    void inorder(Node* root)
    {
        if(root!=NULL)
        {
            inorder(root->left);
            cout<<root->data<<endl;
            inorder(root->right);
        }
    }

    void preorder(Node* root)
    {
        if(root!=NULL)
        {
            cout<<root->data<<endl;
            preorder(root->left);
            preorder(root->right);
        }
    }

    void postorder(Node* root)
    {
        if(root!=NULL)
        {
            postorder(root->left);
            postorder(root->right);
            cout<<root->data<<endl;
        }
    }

    void inorder_itr()
    {
        myStack <Node*> s;
        Node* temp=root;
        while(!s.empty() || temp!=NULL)
        {
            if(temp!=NULL)
            {
                s.push(temp);
                temp=temp->left;
            }
            else
            {
                temp=s.pop();
                cout<<temp->data<<endl;
                temp=temp->right;
            }
        }
    }

    void preorder_itr()
    {
        myStack <Node*> s;
        Node* temp=root;
        s.push(temp);
        while(!s.empty())
        {
            if(temp!=NULL)
            {
                cout<<temp->data<<endl;
                if(temp->right!=NULL)
                {
                    s.push(temp->right);
                }
                if(temp->left!=NULL)
                {
                    temp=temp->left;
                }
                else
                {
                    temp=s.pop();
                }
            }
        }
    }

    void postorder_itr()
    {
        myStack <Node*> s1,s2;
        Node* temp=root;
        s1.push(temp);
        while(!s1.empty())
        {
            if(temp!=NULL)
            {
                temp=s1.pop();
                s2.push(temp);
            }
            Node* ptr=s2.Top();
            if(ptr->left!=NULL)
            {
                s1.push(ptr->left);
            }
            if(ptr->right!=NULL)
            {
                s1.push(ptr->right);
            }
        }
        while(!s2.empty())
        {
            Node* n=s2.pop();
            cout<<n->data<<endl;
        }
    }

    Node* getroot()
    {
        return root;
    }

    int height(Node* temp)
    {
        if(temp==NULL)
        {
            return -1;
        }
        else
        {
            int l=height(temp->left);
            int r=height(temp->right);
            return (1+max(l,r));
        }
    }

    void mirror(Node* temp)
    {
        if(temp==NULL)
        {
            return;
        }
        else
        {
            mirror(temp->left);
            mirror(temp->right);
            Node* t=temp->right;
            temp->right=temp->left;
            temp->left=t;
        }
    }

    void del_tree(Node* temp)
    {
        if(temp!=NULL)
        {
            del_tree(temp->left);
            del_tree(temp->right);
            delete(temp);
            temp=NULL;
        }
    }
};

int main()
{
	int n,ele,op,ch,h,count1,count2;
	char ans;
	BT b,b1;
	Node *p=NULL;

	do
	{
		cout<<"\n----------MENU----------\n\n";
		cout<<"1.Creation\n2.In-order Traversal\n3.Pre-order Traversal\n4.Post-order Traversal\n5.Height of tree\n6.Get mirror image of the tree\n7.Copy tree\n8.Erase nodes in the tree\n9.Number of leaf nodes\n10.NUmber of internal nodes\n";
		cout<<"\n------------------------\n";
		cout<<"Enter your choice :";
		cin>>op;

		switch(op)
		{
		case 1:
			cout<<"\n1.Recursive\n2.Non-recursive\n";
			cout<<"Enter your choice :";
			cin>>ch;
			if(ch==1)
			{
				b.create_rec();
			}
			else if(ch==2)
			{
				cout<<"Enter the number of elements :";
				cin>>n;
				cout<<"Enter elements :";
				for(int i=0;i<n;i++)
				{
					cin>>ele;
					b.create_itr(ele);
				}
			}
			else
			{
				cout<<"INVALID CHOICE";
			}
			break;

		case 2:
			cout<<"\n1.Recursive\n2.Non-recursive\n";
			cout<<"Enter your choice :";
			cin>>ch;
			if(ch==1)
			{
				p=b.getroot();
                if(p!=NULL)
				b.inorder(p);
                else
                cout<<"Tree is empty"<<endl;
			}
			else if(ch==2)
			{
				b.inorder_itr();
			}
			else
			{
				cout<<"INVALID CHOICE"<<endl;
			}
			break;

		case 3:
			cout<<"\n1.Recursive\n2.Non-recursive\n";
			cout<<"Enter your choice :";
			cin>>ch;
			if(ch==1)
			{
				p=b.getroot();
                if(p!=NULL)
				b.preorder(p);
                else
                cout<<"Tree is empty"<<endl;
			}

			else if(ch==2)
			{
				b.preorder_itr();

			}
			else
			{
				cout<<"INVALID CHOICE"<<endl;
			}
			break;

		case 4:
			cout<<"\n1.Recursive\n2.Non-recursive\n";
			cout<<"Enter your choice :";
			cin>>ch;
			if(ch==1)
			{
				p=b.getroot();
                if(p!=NULL)
				b.postorder(p);
                else
                cout<<"Tree is empty"<<endl;
			}
			else if(ch==2)
			{
				b.postorder_itr();
			}
			else
			{
				cout<<"INVALID CHOICE"<<endl;
			}
			break;

		case 5:
            p=b.getroot();
			h=b.height(p);
			if(h!=-1)
			{
				cout<<"Height of the tree is :"<<h<<endl;
			}
			else
			{
				cout<<"Tree is empty"<<endl;
			}
			break;

		case 6:
			p=b.getroot();
			b.mirror(p);
			b.inorder(p);
			break;

		// case 7:
		// 	b1=b;
		// 	p=b1.getroot();
		// 	b1.inorder(p);
		// 	break;

		case 8:
			p=b.getroot();
			b.del_tree(p);
			break;

		// case 9:
		// 	count1=b.leaf_count();
		// 	if(count1!=-1)
		// 	{
		// 		cout<<"Number of leaf nodes = "<<count1<<endl;
		// 	}
		// 	else
		// 	{
		// 		cout<<"Tree is empty"<<endl;
		// 	}
		// 	break;

		// case 10:
		// 	p=b.getroot();
		// 	count2=b.internal_count(p);
		// 	if(count2!=0)
		// 	{
		// 		cout<<"Number of internal nodes = "<<count2<<endl;
		// 	}
		// 	else
		// 	{
		// 		cout<<"Tree is empty"<<endl;
		// 	}
		// 	break;

		default:
			cout<<"INVALID CHOICE!"<<endl;
			break;
		}
		cout<<"\nDo you want to continue?(y/n) :";
		cin>>ans;
	}while(ans=='y' || ans=='Y');
	return 0;
}
