#include<iostream>
#include<string>
using namespace std;

class DataEntry
{
    string name,tele;

    public:
    DataEntry()
    {
        name=tele=" ";
    }

    DataEntry(string s1,string s2)
    {
        name=s1;
        tele=s2;
    }

    friend class HashTable;
};

class HashTable
{
    int size;
    DataEntry* ht;

    public:
    HashTable()
    {
        size=10;
        ht=new DataEntry[10];
        for(int i=0;i<10;i++)
        {
            ht[i]=DataEntry();
        }
    }

    HashTable(int size)
    {
        this->size=size;
        ht=new DataEntry[size];
        for(int i=0;i<size;i++)
        {
            ht[i]=DataEntry();
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
        return hash;
    }

    int find_slot(string key)
    {
        int idx=hashfunc(key)%size;
        while(ht[idx].name!=" " && ht[idx].name!=key)
        {
            idx=(idx+1)%size;
        }
        return idx;
    }

    void insert_wo_replace(string key,string val)
    {
        int idx=find_slot(key);
        ht[idx].name=key;
        ht[idx].tele=val;
    }

    void insert_w_replace(string key,string val)
    {
        int idx=hashfunc(key)%size;
        while(ht[idx].name!=" " && ht[idx].name!=key)
        {
            int loc=hashfunc(ht[idx].name)%size;
            if(loc!=idx)
            {
                string tempname=ht[idx].name;
                string tempnum=ht[idx].tele;

                ht[idx].name=key;
                ht[idx].tele=val;

                key=tempname;
                val=tempnum;
            }
            idx=(idx+1)%size;
        }
       ht[idx].name=key;
       ht[idx].tele=val;
    }
    
    int search(string key)
    {
        int comp=0;
        int idx=hashfunc(key)%size;
        for(int i=0;i<size;i++)
        {
            comp++;
            if(ht[idx].name==key)
            {
                cout<<"NAME :"<<key<<endl;
                cout<<"TELEPHONE NO. :"<<ht[idx].tele<<endl;
                return comp;
            }
            else
            {
                idx=(idx+1)%size;
            }
        }
        cout<<key<<" not present in the list"<<endl;
        return comp;
    }

    int search_idx(string key)
    {
        int idx=hashfunc(key)%size;
        for(int i=0;i<size;i++)
        {
            if(ht[idx].name==key)
            {
                cout<<"NAME :"<<key<<endl;
                cout<<"TELEPHONE NO. :"<<ht[idx].tele<<endl;
                return idx;
            }
            else
            {
                idx=(idx+1)%size;
            }
        }
        cout<<key<<" not present in the list"<<endl;
        return -1;
    }

    void del(string key)
    {
        int idx=this->search_idx(key);
        if(idx!=-1)
        {
            ht[idx].name="-1";
            ht[idx].tele="-1";
            cout<<"Entry deleted !"<<endl;
        }
    }

    void display()
    {
        cout<<"============================================\n";
        cout<<"INDEX"<<"\t"<<"NAME"<<"\t\t"<<"TELEPHONE NO"<<endl;
        cout<<"============================================\n";
        for(int i=0;i<size;i++)
        {
            cout<<i<<"\t"<<ht[i].name<<"\t\t"<<ht[i].tele<<endl;
        }
        cout<<"============================================\n";
    }

};

int main()
{
	HashTable htwor;
	HashTable htwr;
	int op,n,comp;
	char ans;
	string name,num;
	do
	{
		cout<<"\n=====MENU=====";
		cout<<"\n1.Insert\n2.Display\n3.Search\n4.Delete\n";
		cout<<"================\n";
		cout<<"Enter your choice :";
		cin>>op;

		switch(op)
		{
		case 1:
			cout<<"How many entries you want to make :";
			cin>>n;
			for(int i=0;i<n;i++)
			{
				cout<<"Enter client's name :";
				cin>>name;
				cout<<"Enter client's telephone number :";
				cin>>num;
				htwor.insert_wo_replace(name, num);
				htwr.insert_w_replace(name, num);
			}
			break;

		case 2:
			cout<<"\nWithout Replacement :"<<endl;
			htwor.display();
			cout<<"\nWith Replacement :"<<endl;
			htwr.display();
			break;

		case 3:
			cout<<"Enter name of client :";
			cin>>name;
			comp=htwor.search(name);
			cout<<"For without replacement, number of comparisons :"<<comp<<endl;
			comp=htwr.search(name);
			cout<<"For with replacement, number of comparisons :"<<comp<<endl;
			break;

        case 4:
            cout<<"Enter name of client to be deleted :";
            cin>>name;
            htwor.del(name);
            htwr.del(name);
            break;

        default:
            cout<<"INVALID CHOICE !!"<<endl;
            break;
		}
		cout<<"\nDo you want to continue?(y/n) :";
		cin>>ans;
	}while(ans=='y' || ans=='y');

	return 0;
}
