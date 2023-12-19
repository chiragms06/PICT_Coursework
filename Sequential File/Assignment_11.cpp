#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

class SeqeuntialFile
{
    string name,addr;
    int rno,div;

    public:
    SeqeuntialFile()
    {
        name=addr="";
        rno=div=0;
    }

    void create_record()
    {
        cout<<"Enter name of student :";
        cin>>name;
        cout<<"Enter roll no of student :";
        cin>>rno;
        cout<<"Enter div of student :";
        cin>>div;
        cout<<"Enter address of student :";
        cin>>addr;
        fstream f("studentinfo.txt",ios::app);
        if(!f)
        {
            cout<<"File not opened!"<<endl;
        }
        else
        {
            f<<name<<" ";
            f<<rno<<" ";
            f<<div<<" ";
            f<<addr<<"\n";
            cout<<"Student record created successfully!"<<endl;
        }
        f.close();
    }

    void display_records()
    {
        string str;
        ifstream fin("studentinfo.txt");
        if(!fin)
        {
            cout<<"File not opened!"<<endl;
        }
        else
        {
            while(getline(fin,str))
            {
                cout<<str<<endl;
            }
        }
    }

    void search()
    {
        string line,rno;
        int found=0;
        cout<<"Enter roll no to be found :";
        cin>>rno;
        fstream f("studentinfo.txt",ios::in);
        if(!f)
        {
            cout<<"File not opened !"<<endl;
        }
        else
        {
            while(getline(f,line))
            {
                istringstream is(line);
                string n,r,d,a;
                is>>n>>r>>d>>a;
                if(rno==r)
                {
                    cout<<"Student Name : "<<n<<endl;
                    cout<<"Student RollNo : "<<r<<endl;
                    cout<<"Student Div : "<<d<<endl;
                    cout<<"Student Address : "<<a<<endl;
                    found=1;
                    break;
                }
            }
            if(!found)
            {
                cout<<"Record not found !"<<endl;
            }
        }
        f.close();
    }

    void del_record()
    {
        string line,rno;
        int found=0;
        cout<<"Enter the roll no to be deleted :";
        cin>>rno;
        fstream f("studentinfo.txt",ios::in);
        ofstream fo("newfile.txt");
        if(!f)
        {
            cout<<"File not opened !"<<endl;
        }
        else
        {
            while(getline(f,line))
            {
                istringstream is(line);
                string n,r,d,a;
                is>>n>>r>>d>>a;
                if(rno!=r)
                {
                    fo<<line<<"\n";
                }
                else
                {
                    found=1;
                }
            }
            f.close();
            fo.close();
            remove("studentinfo.txt");
            rename("newfile.txt","studentinfo.txt");
            if(found)
            {
                cout<<"Record to be deleted found!"<<endl;
            }
            else
            {
                cout<<"Record to be deleted not found!"<<endl;
            }
        }
    }
};

int main()
{
    SeqeuntialFile obj;
    char ans;
    int op;

    do
    {
        cout<<"\n-----MENU-----\n";
        cout<<"\n1.Insert Record\n2.Display Records\n3.Search Record\n4.Delete Record\n";
        cout<<"\n--------------\n";
        cout<<"Enter your choice :";
        cin>>op;

        switch(op)
        {
            case 1:
            {
                int n;
                cout<<"Enter number of records :";
                cin>>n;
                cout<<"Enter the info :"<<endl;
                for(int i=0;i<n;i++)
                {
                    obj.create_record();
                }
                break;
            }

            case 2:
            {
                obj.display_records();
                break;
            }

            case 3:
            {
                obj.search();
                break;
            }

            case 4:
            {
                obj.del_record();
                break;
            }

            default:
            {
                cout<<"INVALID CHOICE !"<<endl;
                break;
            }
        }
        cout<<"Do you want to conitnue(y/n) :";
        cin>>ans;
    } while (ans=='y' || ans=='Y');

    return 0;
}
