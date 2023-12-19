#include<iostream>
#include<string>
using namespace std;

class Node
{
    string key,mean;
    Node *left,*right;
    int ht;

    public:
    Node()
    {
        key=mean="";
        left=right=NULL;
    }

    Node(string s1,string s2)
    {
        key=s1;
        mean=s2;
        ht=0;
        left=right=NULL;
    }

    friend class AVL;
};

class AVL
{
    Node* root;

    public:
    AVL()
    {
        root=NULL;
    }

    int node_ht(Node* p)
    {
        int lh=0,rh=0;
        lh=(p && p->left)? p->left->ht : 0;
        rh=(p && p->right)? p->right->ht : 0;
        return (lh>rh ? 1+lh : 1+rh);
    }

    int bf(Node* p)
    {
        int leftht=0,rightht=0;
        leftht=(p && p->left)? p->left->ht : 0;
        rightht=(p && p->right)? p->right->ht : 0;
        return (leftht-rightht);
    }

    Node* LL(Node* p)
    {
        Node* pl=p->left;
        p->left=pl->right;
        pl->right=p;

        p->ht=node_ht(p);
        pl->ht=node_ht(pl);

        if(root==p)
        {
            root=pl;
        }

        return pl;
    }

    Node* RR(Node* p)
    {
        Node* pr=p->right;
        p->right=pr->left;
        pr->left=p;

        p->ht=node_ht(p);
        pr->ht=node_ht(pr);

        if(root==p)
        {
            root=pr;
        }

        return pr;
    }

    Node* LR(Node* p)
    {
        Node* pl=p->left;
        Node* plr=pl->right;
        pl->right=plr->left;
        p->left=plr->right;
        plr->left=pl;
        plr->right=p;

        p->ht=node_ht(p);
        pl->ht=node_ht(pl);
        plr->ht=node_ht(plr);

        if(root==p)
        {
            root=plr;
        }

        return plr;
    }

    Node* RL(Node* p)
    {
        Node* pr=p->right;
        Node* prl=pr->left;
        pr->left=prl->right;
        p->right=prl->left;
        prl->left=p;
        prl->right=pr;
        
        p->ht=node_ht(p);
        pr->ht=node_ht(pr);
        prl->ht=node_ht(prl);

        if(root==p)
        {
            root=prl;
        }

        return prl;
    }

    Node* insert(Node* temp,string s1,string s2)
    {
        Node* nn=NULL;
        if(temp==NULL)
        {
            nn=new Node(s1,s2);
            nn->ht=1;
            return nn;
        }
        if(s1<temp->key)
        {
            temp->left=insert(temp->left,s1,s2);
        }
        else if(s1>temp->key)
        {
            temp->right=insert(temp->right,s1,s2);
        }

        temp->ht=node_ht(temp);

        if(bf(temp)==2 && bf(temp->left)==1)
        {
            temp=LL(temp);
        }
        else if(bf(temp)==2 && bf(temp->left)==-1)
        {
            temp=LR(temp);
        }
        else if(bf(temp)==-2 && bf(temp->right)==1)
        {
            temp=RL(temp);
        }
        else if(bf(temp)==-2 && bf(temp->right)==-1)
        {
            temp=RR(temp);
        }

        return temp;
    }

    void create_avl()
    {
        int n,ele;
        string w,m;
        cout<<"Enter number of elements :";
        cin>>n;
        
        for(int i=0;i<n;i++)
        {
            cout<<"Enter the word :";
            cin>>w;
            cout<<"Enter its meaning :";
            cin>>m;
            this->root=this->insert(this->root,w,m);
        }
    }

    void inorder(Node* root)
    {
        if(root!=NULL)
        {
            inorder(root->left);
            cout<<root->key<<" | "<<root->mean<<" | "<<bf(root)<<endl;
            inorder(root->right);
        }
    }

    void preorder(Node* root)
    {
        if(root!=NULL)
        {
            cout<<root->key<<" | "<<root->mean<<" | "<<bf(root)<<endl;
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
            cout<<root->key<<" | "<<root->mean<<" | "<<bf(root)<<endl;
        }
    }

    Node* findMinNode(Node* temp)
    {
        while(temp && temp->left)
        {
            temp=temp->left;
        }
        return temp;
    }

    Node *deleteNode(Node *p, string key)
    {
        if (p == NULL)
        {
            return p;
        }
        if (key < p->key)
        {
            p->left = deleteNode(p->left, key);
        }
        else if (key > p->key)
        {
            p->right = deleteNode(p->right, key);
        }
        else
        {
            if (p->left == NULL || p->right == NULL)
            {
                Node *temp = p->left ? p->left : p->right;

                if (temp == NULL)
                {
                    temp = p;
                    p = NULL;
                }
                else
                {
                    *p = *temp;
                }

                delete temp;
            }
            else
            {
                Node *temp = findMinNode(p->right);
                p->key = temp->key;
                p->right = deleteNode(p->right, temp->key);
            }
        }

        if (p == NULL)
        {
            return p;
        }

        p->ht = node_ht(p);

        if (bf(p) == 2 && bf(p->left) == 1)
        {
            p = LL(p);
        }
        else if (bf(p) == 2 && bf(p->left) == -1)
        {
            p = LR(p);
        }
        else if (bf(p) == -2 && bf(p->right) == -1)
        {
            p = RR(p);
        }
        else if (bf(p) == -2 && bf(p->right) == 1)
        {
            p = RL(p);
        }

        return p;
    }

    Node* getroot()
    {
        return root;
    }
};

int main()
{
    AVL a;
    char ans;
    int op;
    do
    {
        cout<<"\n----------MENU----------\n\n";
        cout<<"1.CREATE AVL TREE\n2.INORDER TRAVERSAL\n3.PREORDER TRAVERSAL\n4.POSTORDER TRAVERSAL\n";
        cout<<"\n------------------------\n";
		cout<<"Enter your choice :";
		cin>>op;

        switch(op)
        {
            case 1:
            {
                a.create_avl();
                break;
            }

            case 2:
            {
                Node* p=a.getroot();
                if(p!=NULL)
                {
                    a.inorder(p);
                }
                else
                {
                    cout<<"TREE IS EMPTY"<<endl;
                }
                break;
            }

            case 3:
            {
                Node* p=a.getroot();
                if(p!=NULL)
                {
                    a.preorder(p);
                }
                else
                {
                    cout<<"TREE IS EMPTY"<<endl;
                }
                break;
            }

            case 4:
            {
                Node* p=a.getroot();
                if(p!=NULL)
                {
                    a.postorder(p);
                }
                else
                {
                    cout<<"TREE IS EMPTY"<<endl;
                }
                break;
            }

            default:
                cout<<"INVALID CHOICE!!"<<endl;
                break;
        }
        cout<<"Do you want to continue(y/n) :";
        cin>>ans;
    } while (ans=='y' || ans=='Y');
    return 0;
}
