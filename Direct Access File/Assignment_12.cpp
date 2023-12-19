#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Hashtable
{
    public:
    int addr;
    Hashtable();
    }HT[10];
    Hashtable :: Hashtable()
    {
    for(int i=0; i<10; i++)
    HT[i].addr = -1;
}

class Student : public Hashtable
{
    int roll_no;
    char department[10];
    char name[10];
    char year[10];
    public:
    void add_Rec();
    void display_Rec(); 
    void search_Rec(); 
    void delete_Rec(); 
};

void Student :: add_Rec()
{
    int index, count, tablesize = 10;

    int location;
    cout<<"\n\n How many records..? : ";
    cin>>count;
    ofstream fout;
    fout.open("Rec.txt", ios::out);

    for (int i = 0; i < count; i++)
    {
        cout << "\n Enter Student roll: ";
        cin >> roll_no;
        cout << "\n Enter Student name: ";
        cin >> name;
        cout << "\n Enter Student department: ";
        cin >> department;
        cout << "\n Enter Student year: ";
        cin >> year;
        location = fout.tellp(); 
        index = roll_no % tablesize; 
        HT[index].addr = location; 

        fout<<roll_no<<" "<<name<<" "<<""<<year<<" "<<department<<endl;
    }
    fout.close();
}

void Student :: display_Rec()
{
    char buffer[40];
    int cnt = 1;
    ifstream fin;

    fin.open("Rec.txt", ios::in);

    while(! fin.eof())
    {
        fin.getline(buffer,40);
        cout<<"\n\n Record "<<cnt<<" : "<<buffer;
        cnt++;

    }
}

void Student :: search_Rec()
{
    int id;
    int tablesize = 10;

    cout<<"\n\t Enter Emp_id to search record: ";
    cin>>id;

    int index = id % tablesize;

    int location = HT[index].addr;

    ifstream fin;
    fin.open("Rec.txt", ios::in);

    fin.seekg(location, ios::beg);

    char buffer[40];
    fin.getline(buffer, 40);
    cout<<"\n\t Found Record : "<<buffer;
}

void Student ::delete_Rec()
{
    int i, id;
    int tablesize = 10;
    cout<<"\n\t Enter the Student_roll to delete: ";
    cin>>id;
    int index = id % tablesize;
    int location = HT[index].addr;

    ifstream fin;

    fin.open("Rec.txt", ios::in);

    fin.seekg(location, ios::beg);

    char buffer[40];
    fin.getline(buffer, 40);
    cout<<"\n\t Deleted Record : "<<buffer;
    fin.close();
    cout<<"\n\t Remaining Records:- ";

    fin.open("Rec.txt", ios::in);
    for(i=0; i<10; i++)
    {
        if(HT[i].addr != -1 && HT[i].addr != location)
        {
            fin.seekg(HT[i].addr, ios::beg);
            fin.getline(buffer, 40);
            cout<<"\n\t Record : "<<buffer;
        }
    }
    fin.close();
}

int main()
{
    Student E;
    cout<<"\n\n A] Write Records in Direct Access File";
    E.add_Rec();
    cout<<"\n\n B] Read Records from Direct Access File";
    E.display_Rec();
    cout<<"\n\n C] Search Record in Direct Access File";
    E.search_Rec();
    cout<<"\n\n D] Delete Record from Direct Access File";
    E.delete_Rec();
    cout<<"\n\n";
    return 0;
}
