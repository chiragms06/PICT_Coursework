#include<iostream>
using namespace std;
#define size 30

class Node
{
    string v;
    int w;
    Node* next;

    public:
    Node()
    {
        v="";
        w=0;
        next=NULL;
    }

    Node(string ver,int x)
    {
        v=ver;
        w=x;
        next=NULL;
    }
    friend class Graph;
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

class Graph
{
    int nv,ne;
    Node **adjlist;
    string* vname;

    public:
    Graph()
    {
        cout<<"Enter number of vertices :";
        cin>>nv;
        cout<<"Enter number of edges :";
        cin>>ne;
        adjlist=new Node*[nv];
        vname=new string[nv];
        for(int i=0;i<nv;i++)
        {
            string x;
            cout<<"Enter the vertex :";
            cin>>x;
            vname[i]=x;
            adjlist[i]=NULL;
        }
    }

    // Graph()
	// {
	// 	nv=ne=0;
	// 	vname=new string[nv];
	// 	adjlist=new Node*[nv];
	// 	for(int i=0;i<10;i++)
	// 	{
	// 		adjlist[i]=new Node[10];
	// 		vname[i]="";
	// 	}
	// }

    // Graph(int v,int e)
	// {
	// 	nv=v;
	// 	ne=e;
	// 	adjlist=new Node*[v];
	// 	vname=new string[v];
	// 	for(int i=0;i<v;i++)
	// 	{
	// 		adjlist[i]=new Node[v];
	// 		vname[i]="";
	// 	}
	// }

    int findidx(string s)
    {
        int idx;
        for(int i=0;i<nv;i++)
        {
            if(vname[i]==s)
            {
                idx=i;
                break;
            }
        }
        return idx;
    }

    // void create_graph()
	// {
	// 	string s;
	// 	int v;
	// 	cout<<"Enter the number of vertices :";
	// 	cin>>v;
	// 	int i=0;
	// 	while(v)
	// 	{
	// 		cout<<"Enter the name of vertex :";
	// 		cin>>s;
	// 		Node* nn=new Node(s,1);
	// 		vname[i]=s;
	// 		adjlist[i]=nn;
	// 		int nadjv;
	// 		cout<<"Enter the number of adjacent vertices :";
	// 		cin>>nadjv;
	// 		Node* temp=nn;
	// 		while(nadjv)
	// 		{
	// 			string s1;
	// 			cout<<"Enter the name of adjacent vertex :";
	// 			cin>>s1;
	// 			Node* nn1=new Node(s1,1);
	// 			temp->next=nn1;
	// 			temp=temp->next;
	// 			nadjv--;
	// 		}
	// 		i++;
	// 		v--;
	// 	}
	// }

    void insert(string s,string d,int w)
    {
        int idx=findidx(s);
        Node* temp=adjlist[idx];
        if(temp==NULL)
        {
            adjlist[idx]=new Node(d,w);
        }
        else
        {
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            Node* nn=new Node(d,w);
            temp->next=nn;
        }
    }

    void initialize()
    {
        string s,d;
        int w;
        for(int i=0;i<ne;i++){
        cout<<"Enter source :";
        cin>>s;
        cout<<"Enter destination :";
        cin>>d;
        cout<<"Enter weight :";
        cin>>w;
        insert(s,d,w);
        }
    }

    void DFS_itr(string start)
    {
        myStack <string> s;
        int visited[nv];
        cout<<"DFS traversal of the graph is :";
        for(int i=0;i<nv;i++)
        {
            visited[i]=0;
        }
        int idx=findidx(start);
        visited[idx]=1;
        cout<<vname[idx]<<" ";
        s.push(start);
        while(!s.empty())
        {
            string x=s.Top();
            Node* temp=adjlist[findidx(x)];
            int flag=0;
            while(temp!=NULL)
            {
                if(visited[findidx(temp->v)]==0)
                {
                    visited[findidx(temp->v)]=1;
                    cout<<temp->v<<" ";
                    s.push(temp->v);
                    flag=1;
                    break;
                }
                temp=temp->next;
            }
            if(flag==0)
            {
                s.pop();
            }
        }
        cout<<endl;
    }

    void BFS_itr(string start)
    {
        int visited[nv];
        for(int i=0;i<nv;i++)
        {
            visited[i]=0;
        }
        int idx=findidx(start);
        visited[idx]=1;
        myQueue <string> q;
        q.push(start);
        cout<<"BFS traversal of the graph is :";
        while(!q.empty())
        {
            string x=q.pop();
            int i=findidx(x);
            cout<<vname[i]<<" ";
            Node* temp=adjlist[i];
            while(temp!=NULL)
            {
                if(visited[findidx(temp->v)]==0)
                {
                    visited[findidx(temp->v)]=1;
                    q.push(temp->v);
                }
                temp=temp->next;
            }
        }
        cout<<endl;
    }

    void display_graph()
    {
        for(int i=0;i<nv;i++)
        {
            Node* temp=adjlist[i];
            cout<<(vname[i])<<" => ";
            while(temp!=NULL)
            {
                cout<<temp->v<<"|"<<temp->w<<" --> ";
                temp=temp->next;
            }
            cout<<endl;
        }
    }
};

int main()
{
    Graph g;
    g.initialize();
    string v;

    while (1)
    {
        cout << "*MENU*" << endl;
        cout << "1)Display Graph" << endl;
        cout << "2)DFS Traversal " << endl;
        cout << "3)BFS Traversal" << endl;
        cout << "4)Exit" << endl;
        cout << "------------------------------------------------------" << endl
             << endl;
        cout << "Enter the choice " << endl;
        int ch;
        cin >> ch;
        if (ch == 1)
        {
            g.display_graph();
        }
        else if (ch == 2)
        {
            cout<<"Enter start vertex :";
            cin>>v;
            g.DFS_itr(v);
        }
        else if (ch == 3)
        {
            cout<<"Enter start vertex :";
            cin>>v;
            g.BFS_itr(v);
        }
        else if (ch == 4)
        {
            cout << "Exited!" << endl;
            break;
        }
        else
        {
            cout << "Invalid Input " << endl;
        }
    }

    return 0;
}
