#include <iostream>
#include <string>
using namespace std;

class Node
{
    string data;
    Node* left;
    Node* right;

public:
    Node()
    {
        data = " ";
        left = right = NULL;
    }

    Node(string s1)
    {
        data = s1;
        left = right = NULL;
    }

    friend class OBST;
};

class OBST
{
    Node* root;

public:
    OBST()
    {
        root = NULL;
    }

    void calculate_wt(double[], double[], int, string*);
    Node* create_tree(int, int, double**, string*);
    void inorder(Node* root);
    void preorder(Node* root);
    void postorder(Node* root);

    Node* getroot()
    {
        return root;
    }
};

void OBST::calculate_wt(double* p, double* q, int n, string* input)
{
    double** w = new double*[n + 1];
    double** c = new double*[n + 1];
    double** r = new double*[n + 1];
    
    for (int i = 0; i < n + 1; i++)
    {
        w[i] = new double[n + 1];
        c[i] = new double[n + 1];
        r[i] = new double[n + 1];
    }

    for (int i = 0; i < n; i++)
    {
        w[i][i] = q[i];
        r[i][i] = c[i][i] = 0;

        w[i][i + 1] = q[i] + q[i + 1] + p[i];
        r[i][i + 1] = i + 1;
        c[i][i + 1] = w[i][i + 1];
    }
    
    w[n][n] = q[n];
    r[n][n] = c[n][n] = 0;
    
    for (int m = 2; m <= n; m++)
    {
        for (int i = 0; i <= n - m; i++)
        {
            double min = 999;
            int j = i + m;
            int k = 0;
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
            for (int i1 = i + 1; i1 <= j; i1++)
            {
                double sum = c[i][i1 - 1] + c[i1][j];
                if (sum < min)
                {
                    min = sum;
                    k = i1;
                }
            }
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            r[i][j] = k;
        }
    }
    
    root = create_tree(0, n, r, input);
    
    // cout << "\n-----WEIGHTS-----\n";
    // for(int i = 0; i < n + 1; i++)
    // {
    //     for(int j = 0; j < n + 1; j++)
    //     {
    //         cout << "W" << i << j << " = " << w[i][j] << "  ";
    //     }
    //     cout << endl;
    // }
    
    // cout << "\n-----COSTS-----\n";
    // for(int i = 0; i < n + 1; i++)
    // {
    //     for(int j = 0; j < n + 1; j++)
    //     {
    //         cout << "C" << i << j << " = " << w[i][j] << "  ";
    //     }
    //     cout << endl;
    // }
    
    // cout << "\n-----ROOTS-----\n";
    // for(int i = 0; i < n + 1; i++)
    // {
    //     for(int j = 0; j < n + 1; j++)
    //     {
    //         cout << "R" << i << j << " = " << w[i][j] << "  ";
    //     }
    //     cout << endl;
    // }
}

Node* OBST::create_tree(int i, int j, double** r, string* input)
{
    if (i != j)
    {
        int k = r[i][j];
        Node* nn = new Node(input[k]);
        nn->left = create_tree(i, k - 1, r, input);
        nn->right = create_tree(k, j, r, input);
        return nn;
    }
    else
    {
        return NULL;
    }
}

void OBST::inorder(Node* root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void OBST::preorder(Node* root)
{
    if (root != NULL)
    {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void OBST::postorder(Node* root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

int main()
{
    OBST obj;
    int n;
    

    int choice;
    while (true)
    {
        cout << "\n--- Menu ---\n";
        cout << "1. CREATE OBST\n";
        cout << "2. INORDER TRAVERSAL\n";
        cout << "3. PREORDER TRAVERSAL\n";
        cout << "4. POSTORDER TRAVERSAL\n";
        cout << "5. EXIT\n";
        cout << "\n-------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:{
            cout << "Enter the number of identifiers :";
            cin >> n;
            string input[n+1];
            input[0] = " ";
            cout << "Enter the identifiers :";
            for(int i = 1; i < n+1; i++)
            {
                cin >> input[i];
            }
            double p[n], q[n+1];
    
            cout << "Enter the successful search probabilities :";
            for (int i = 0; i < n; i++)
                cin >> p[i];

            cout << "Enter the unsuccessful search probabilities :";
            for (int i = 0; i <= n; i++)
                cin >> q[i];
                
            obj.calculate_wt(p, q, n, input);
            cout << "\nOBST created successfully !" << endl;
            break;}
            
        case 2:{
            cout << "Inorder Traversal: ";
            obj.inorder(obj.getroot());
            break;}
            
        case 3:{
            cout << "Preorder Traversal: ";
            obj.preorder(obj.getroot());
            break;}
            
        case 4:{
            cout << "Postorder Traversal: ";
            obj.postorder(obj.getroot());
            break;}
            
        case 5:{
            exit(0);}
            
        default:{
            cout << "Invalid choice. Please try again.";
                }
        }
        cout << endl;
    }

    return 0;
}
