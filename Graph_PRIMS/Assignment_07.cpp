#include<iostream>
using namespace std;

class Graph
{
    int nv,ne;
    int **adjmat;

    public:
    // Graph()
    // {
    //     nv=ne=0;
    //     adjmat=NULL;
    // }

    Graph(int v,int e)
    {
        nv=v;
        ne=e;
        adjmat=new int*[nv];
        for(int i=0;i<nv;i++)
        {
            adjmat[i]=new int[nv];
        }
    }

    void create_graph()
    {
        for(int i=0;i<nv;i++)
        {
            for(int j=0;j<nv;j++)
            {
                adjmat[i][j]=0;
            }
        }

        for(int i=0;i<ne;i++)
        {
            int s,d,c;
            cout<<"Enter source :";
            cin>>s;
            cout<<"Enter destination :";
            cin>>d;
            cout<<"Enter cost :";
            cin>>c;
            adjmat[s][d]=c;
            adjmat[d][s]=c;
        }
    }

    void prims(int start)
    {
        int reach[nv];
        int unreach[nv];
        int result[nv][nv];

        for(int i=0;i<nv;i++)
        {
            for(int j=0;j<nv;j++)
            {
                result[i][j]=0;
            }
        }

        for(int i=0;i<nv;i++)
        {
            reach[i]=0;
            unreach[i]=1;
        }

        int edge=0;
        int weight=0;
        reach[start]=1;
        unreach[start]=0;
        cout<<"PATH"<<"\t"<<"COST"<<endl;
        while(edge<nv-1)
        {
            int s=100000;
            int flag=0;
            int a=0;
            int b=0;

            for(int i=0;i<nv;i++)
            {
                if(reach[i]==1)
                {
                    for(int j=0;j<nv;j++)
                    {
                        if(unreach[j]==1)
                        {
                            if(s>adjmat[i][j] && adjmat[i][j]!=0)
                            {
                                flag=1;
                                a=i;
                                b=j;
                                s=adjmat[i][j];
                            }
                        }
                    }
                }
            }

            if(flag==1)
            {
                reach[b]=1;
                unreach[b]=0;
                weight+=s;
                edge+=1;
                result[a][b]=s;
            }
        }

        for(int i=0;i<nv;i++)
        {
            for(int j=0;j<nv;j++)
            {
                if(result[i][j]!=0)
                {
                    cout<<i<<"-"<<j<<"\t"<<result[i][j]<<endl;
                }
            }
        }

        cout<<"Minimum cost = "<<weight<<endl;
    }

    void display_graph()
    {
        cout<<"Graph :- "<<endl;
        for(int i=0;i<nv;i++)
        {
            cout<<i<<" :- ";
            for(int j=0;j<nv;j++)
            {
                cout<<adjmat[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

int main()
{
    int v,e;
    cout<<"Enter number of vertices :";
    cin>>v;
    cout<<"Enter number of edges :";
    cin>>e;
    Graph g(v,e);

    while(1)
	{
		cout<<" *Menu*"<<endl;
		cout<<" 1.Create Graph"<<endl;
		cout<<" 2.Display Graph"<<endl;
		cout<<" 3.Prim's Algorithm"<<endl;
		cout<<" 4.Kruskal's Algorithm"<<endl;
		cout<<"Enter choice"<<endl;
		int ch;
		cin>>ch;
		switch(ch)
		{
			case 1:
			g.create_graph();
			break;

			case 2:
			g.display_graph();
			break;

			case 3:
			cout<<"Enter Starting Vertex"<<endl;
			int st;
			cin>>st;
			g.prims(st);
			break;

			// case 4:
			// g.kruskalsAlgo(0);
			// break;
		}

	}
}
