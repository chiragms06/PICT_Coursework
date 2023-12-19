#include<iostream>
using namespace std;

class HeapSort
{
    int n;
    int* arr;

    public:
    HeapSort()
    {
        n=0;
        arr=NULL;
    }

    HeapSort(int num)
    {
        n=num;
        arr=new int[num];
    }

    void accept()
    {
        cout<<"Enter the elements :";
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
        }
    }

    void display()
    {
        for(int i=0;i<n;i++)
        {
            cout<<arr[i]<<" ";
        }
    }

    void minheapify()
    {
        for(int i=1;i<n;i++)
        {
            if(arr[i]<arr[(i-1)/2])
            {
                int j=i;
                while(arr[j]<arr[(j-1)/2])
                {
                    int temp=arr[j];
                    arr[j]=arr[(j-1)/2];
                    arr[(j-1)/2]=temp;
                    j=(j-1)/2;
                }
            }
        }
    }

    void maxheapify()
    {
        for(int i=1;i<n;i++)
        {
            if(arr[i]>arr[(i-1)/2])
            {
                int j=i;
                while(arr[j]>arr[(j-1)/2])
                {
                    int temp=arr[j];
                    arr[j]=arr[(j-1)/2];
                    arr[(j-1)/2]=temp;
                    j=(j-1)/2;
                }
            }
        }
    }

    void insert(int x)
    {
        n=n+1;
        arr[n-1]=x;
        maxheapify();
    }

    void del()
    {
        int last=arr[n-1];
        arr[0]=last;
        n=n-1;
        maxheapify();
    }

    void heapsorting()
    {
        maxheapify();
        for(int i=n-1;i>0;i--)
        {
            int temp=arr[0];
            arr[0]=arr[i];
            arr[i]=temp;
            int j=0,idx;

            do
            {
                idx=2*j+1;
                if(arr[idx]<arr[idx+1] && idx<(i-1))
                {
                    idx++;
                }

                if(arr[j]<arr[idx] && idx<i)
                {
                    int temp=arr[j];
                    arr[j]=arr[idx];
                    arr[idx]=temp;
                }
                j=idx;
            } while (idx<i);
        }
    }

    void heapsorting2()
    {
        minheapify();
        for(int i=n-1;i>0;i--)
        {
            int temp=arr[0];
            arr[0]=arr[i];
            arr[i]=temp;
            int j=0,idx;

            do
            {
                idx=2*j+1;
                if(arr[idx]>arr[idx+1] && idx<(i-1))
                {
                    idx++;
                }

                if(arr[j]>arr[idx] && idx<i)
                {
                    int temp=arr[j];
                    arr[j]=arr[idx];
                    arr[idx]=temp;
                }
                j=idx;
            } while (idx<i);
        }
    }
};

int main() {
	cout << "Enter number of elements" << endl;
	int num;
	cin >> num;
	HeapSort h(num);
	while (1) {
		cout << "Menu" << endl;
		cout << "1.Accept Array" << endl;
		cout << "2.Create Max Heap" << endl;
		cout << "3.Insert Element" << endl;
		cout << "4.Delete Element" << endl;
		cout << "5.Create Min heap" << endl;
		cout << "6.Sort the Array(MAX)" << endl;
		cout << "7.Sort the Array(MIN)" << endl;
		int ch;
		cin >> ch;
		switch (ch) {
		case 1:
			h.accept();
			h.display();
			break;
		case 2:
			h.maxheapify();
			h.display();
			break;
		case 3:
			int nu;
			cout<<"Enter element"<<endl;
			cin>>nu;
			h.insert(nu);
			h.display();
			break;
		case 4:
			h.del();
			h.display();
			break;
		case 5:
			h.minheapify();
			h.display();
			break;
		case 6:
			h.heapsorting();
			h.display();
			break;
		case 7:
			h.heapsorting2();
			h.display();
			break;

		}
	}
	return 0;
}
