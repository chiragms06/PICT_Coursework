#include<iostream>
#include<string>
using namespace std;

class Node
{
    string kword,mean;
    Node *next;

    public:
    Node()
    {
        kword=mean="";
        next=NULL;
    }

    Node(string s1,string s2)
    {
        kword=s1;
        mean=s2;
        next=NULL;
    }
    friend class HashTable;
};

class HashTable
{
    int size;
    Node** ht;

    public:
    HashTable()
    {
        size=10;
        ht=new Node*[size];
        for(int i=0;i<size;i++)
        {
            ht[i]=NULL;
        }
    }

    HashTable(int size)
    {
        this->size=size;
        ht=new Node*[size];
        for(int i=0;i<size;i++)
        {
            ht[i]=NULL;
        }
    }

    int hashfunc(string key)
    {
        int hash=0;
        int n=key.length();
        for(int i=0;i<n;i++)
        {
            hash+=key[i];
        }
        return (hash%size);
    }

    void insertatend(Node* t,int i)
    {
        Node* temp=ht[i];
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=t;
    }

    void insert(string key,string val)
    {
        Node* nn=new Node(key,val);
        int idx=hashfunc(key);
        if(ht[idx]==NULL)
        {
            ht[idx]=nn;
        }
        else
        {
            insertatend(nn,idx);
        }
    }

    int search(string key)
    {
        int comp=0,flag=0;
        int idx=hashfunc(key);
        Node* temp=ht[idx];
            while(temp!=NULL)
            {
                if(temp->kword==key)
                {
                    flag=1;
                    comp++;
                    cout<<temp->kword<<" "<<temp->mean<<" "<<"found at index :"<<idx<<endl;
                    return comp;   
                }
                else
                {
                    comp++;
                    temp=temp->next;
                }
            }
            if(flag==0)
            {
                cout<<"not present!"<<endl;
                return -1;
            } 
    }

    void del(string key)
    {
        int idx=hashfunc(key);
        if(ht[idx]==NULL)
        {
            cout<<"not present"<<endl;
        }
        else
        {
            Node* prev=NULL;
            Node* temp=ht[idx];
            if(temp->kword==key)
            {
                temp=temp->next;
                delete(temp);
                ht[idx]=temp;
                temp=NULL;
            }
            else
            {
                while(temp->kword!=key && temp!=NULL)
                {
                    prev=temp;
                    temp=temp->next;
                }
                if(temp->kword==key)
                {
                    prev->next=temp->next;
                    delete(temp);
                    temp=NULL;
                }
                else
                {
                    cout<<"not present!"<<endl;
                }
            }
        }
    }

    void display()
    {
        for(int i=0;i<size;i++)
        {
            cout<<i<<" ";
            Node* temp=ht[i];
            while(temp!=NULL)
            {
                cout<<temp->kword<<" "<<temp->mean<<"-->";
                temp=temp->next;
            }
            cout<<endl;
        }
    }
};

int main()
{
	HashTable h(10);
	char ans;
	int op,n;
	string word,mean;
	do
	{
		cout<<"\n========MENU========\n";
		cout<<"1.Insert\n2.Display\n3.Search\n4.Delete\n";
		cout<<"=====================";
		cout<<"\nEnter your choice :";
		cin>>op;

		switch(op)
		{
		case 1:{
			cout<<"\nHow many entries do you want :";
			cin>>n;
			for(int i=0;i<n;i++)
			{
				cout<<"Enter a word :";
				cin>>word;
				cout<<"Enter its meaning :";
				cin>>mean;
				h.insert(word,mean);
			}
			break;}

		case 2:{
			h.display();
			break;}

		case 3:{
			cout<<"Enter a word you want to search :";
			cin>>word;
			int ans=h.search(word);
			break;}

		case 4:{
			cout<<"Enter a word you want to delete :";
			cin>>word;
			h.del(word);
			break;}

		default:{
			cout<<"\nINVALID CHOICE !"<<endl;
			break;}
		}
		cout<<"\nDo you want to continue?(y/n) :";
		cin>>ans;
	}while(ans=='y' || ans=='Y');
	return 0;
}
