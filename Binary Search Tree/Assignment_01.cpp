#include<iostream>
#include<string>
using namespace std;

class Node
{
    string kword,mean;
    Node *left,*right;

    public:
    Node()
    {
        kword=mean="";
        left=right=NULL;
    }

    Node(string s1,string s2)
    {
        kword=s1;
        mean=s2;
        left=right=NULL;
    }
    friend class BST;
};

class BST
{
    Node* root;

    public:
    BST()
    {
        root=NULL;
    }

    void create();
    void insert(string,string);
    void update(string,string);
    void inorder(Node*);
    void revorder(Node*);
    int search(string,Node*&,Node*&);
    Node* findmin(Node*);
    void del(string);
    Node* getroot()
    {
        return root;
    }
};

void BST :: create()
{
    int n;
    cout<<"Enter number of words :";
    cin>>n;
    string s1,s2;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter the word :";
        cin>>s1;
        cout<<"Enter its meaning :";
        cin>>s2;
        Node* nn=new Node(s1,s2);
        if(root==NULL)
        {
            root=nn;
        }
        else
        {
            Node* temp=root;
            Node* par=NULL;
            int flag=0;
            while(temp!=NULL)
            {
                if(temp->kword>s1)
                {
                    par=temp;
                    temp=temp->left;
                }
                else if(temp->kword<s1)
                {
                    par=temp;
                    temp=temp->right;
                }
                else
                {
                    flag=1;
                    cout<<"Duplicate entries not allowed"<<endl;
                    break;
                }
            }
            if(temp==NULL)
            {
                if(par->kword>s1)
                {
                    par->left=nn;
                }
                else
                {
                    par->right=nn;
                }
            }
        }
    }
}
void BST :: insert(string s1,string s2)
{
    Node* nn=new Node(s1,s2);
    if(root==NULL)
    {
        root=nn;
    }
    else
    {
        Node* temp=root;
        Node* par=NULL;
        int flag=0;
        while(temp!=NULL)
        {
            if(temp->kword>s1)
            {
                par=temp;
                temp=temp->left;
            }
            else if(temp->kword<s1)
            {
                par=temp;
                temp=temp->right;
            }
            else
            {
                flag=1;
                cout<<"Duplicate entries not allowed"<<endl;
                break;
            }
        }
        if(temp==NULL)
        {
            if(par->kword>s1)
            {
                par->left=nn;
            }
            else
            {
                par->right=nn;
            }
        }
    }
}

void BST :: update(string key,string newmean)
{
    if(root==NULL)
    {
        cout<<"Empty"<<endl;
    }
    else
    {
        Node* temp=root;
        while(temp!=NULL)
        {
            if(temp->kword==key)
            {
                temp->mean=newmean;
                break;
            }
            else if(temp->kword>key)
            {
                temp=temp->left;
            }
            else
            {
                temp=temp->right;
            }
        }
        if(temp==NULL)
        {
            cout<<"Entered word not present"<<endl;
        }
    }
}

void BST :: inorder(Node* root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        cout<<root->kword<<" "<<root->mean<<endl;
        inorder(root->right);
    }
}

void BST :: revorder(Node* root)
{
    if(root!=NULL)
    {
        revorder(root->right);
        cout<<root->kword<<" "<<root->mean<<endl;
        revorder(root->left);
    }
}

int BST :: search(string key,Node*&temp,Node*&par)
{
    int count=0;
    if(root==NULL)
    {
        cout<<"Tree is empty"<<endl;
        return -1;
    }
    else
    {
        while(temp!=NULL)
        {
            if(temp->kword==key)
            {
                count++;
                return count;
            }
            else if(temp->kword>key)
            {
                par=temp;
                temp=temp->left;
                count++;
            }
            else
            {
                par=temp;
                temp=temp->right;
                count++;
            }
        }
        cout<<"Entered word not found"<<endl;
        return -1;
    }
   
}

Node* BST :: findmin(Node* temp)
{
    while(temp->left!=NULL)
    {
        temp=temp->left;
    }
    return temp;
}

void BST :: del(string key)
{
    if(root==NULL)
    {
        cout<<"Tress is empty"<<endl;
        return;
    }

    Node* temp=root;
    Node* par=NULL;
    int ans=search(key,temp,par);
    if(ans!=-1)
    {
        if(par!=NULL)
        {
            if(temp->left==NULL && temp->right==NULL)
            {
                if(temp==par->left)
                {
                    par->left=NULL;
                }
                else
                {
                    par->right=NULL;
                }
                delete(temp);
                temp=NULL;
            }
            else if(temp->left!=NULL && temp->right==NULL)
            {
                if(temp==par->left)
                {
                    par->left=temp->left;
                }
                else
                {
                    par->right=temp->left;
                }
                delete(temp);
                temp=NULL;
            }
            else if(temp->left==NULL && temp->right!=NULL)
            {
                if(temp==par->left)
                {
                    par->left=temp->right;
                }
                else
                {
                    par->right=temp->right;
                }
                delete(temp);
                temp=NULL;
            }
            else
            {
                Node* succ=findmin(temp->right);
                string val1=succ->kword;
                string val2=succ->mean;
                del(val1);
                temp->kword=val1;
                temp->mean=val2;
            }
        }
        else
        {
            if(temp->left==NULL && temp->right==NULL)
            {
                delete(temp);
                temp=root=NULL;
            }
            else if(temp->left!=NULL && temp->right==NULL)
            {
                root=root->left;
                delete(temp);
                temp=NULL;
            }
            else if(temp->left==NULL && temp->right!=NULL)
            {
                root-root->right;
                delete(temp);
                temp=NULL;
            }
            else
            {
                Node* succ=findmin(temp->right);
                string val1=succ->kword;
                string val2=succ->mean;
                del(val1);
                temp->kword=val1;
                temp->mean=val2;
            }
        }
    }
    else
    {
        cout<<"Entered word not present"<<endl;
    }
}

int main()
{
	BST b;
    Node *p1,*p2;
	string s1,s2;
	int op,n;
	while(true)
	{
		cout<<"\n----------MENU----------\n";
		cout<<"1.Create a Dictionary\n2.Insert a new word\n3.Update meaning of a word\n"
			  "4.Display in ascending order\n5.Display in descending order\n6.Search a word\n"
			  "7.Delete a word\n";
		cout<<"Enter your choice :";
		cin>>op;

		switch(op)
		{
		case 1:
			b.create();
			break;

		case 2:
			cout<<"Enter a new word :";
			cin>>s1;
			cout<<"Enter its meaning :";
			cin>>s2;
			b.insert(s1,s2);
			break;

		case 3:
			cout<<"Enter the word :";
			cin>>s1;
			cout<<"Enter its new meaning :";
			cin>>s2;
			b.update(s1,s2);
			break;

		case 4:
            p1=b.getroot();
			b.inorder(p1);
			break;

		case 5:
            p2=b.getroot();
			b.revorder(p2);
			break;

		case 6:{
            Node* par=NULL;
            Node* temp=b.getroot();
			cout<<"Enter the word to be searched :";
			cin>>s1;
			int ans=b.search(s1,temp,par);
            if(ans!=-1)
            {
                cout<<"Entered word found after "<<ans<<" comparisons"<<endl; 
            }
			break;}

		case 7:
			cout<<"Enter the word you want to delete :";
			cin>>s1;
			b.del(s1);
			break;

        default:
            cout<<"INVALID CHOICE"<<endl;
            break;
		}
	}
	return 0;
}
