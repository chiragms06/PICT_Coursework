#include <iostream>
using namespace std;
class SelectSort
{
private:int n;
public:template<typename T>
	   void sort(T a[],int n)
		{
			int min;
			for(int i=0;i<n-1;i++)
			{
				min = i;
				for(int j = i+1;j<n;j++)
				{
					if(a[j]<a[min])
					{
						min = j;
					}

				}
				T temp = a[i];
				a[i] = a[min];
				a[min] = temp;

			}
		}
		template<typename T>
		void disp(T a[],int n)
		{
			cout<<"Sorted array is:";
			for(int i = 0;i<n;i++)
			{
				cout<<a[i]<<" ";
			}
			cout<<endl;
		}
};
int main() {
	while(true)
		{
			int op;
			cout<<"Menu:\n1 for sorting an integer array\n2 for sorting a float array"<<endl;
			cout<<"Enter an option:";
			cin>>op;
			if(op == 1)
			{
				int n;
				cout<<"Enter no of elements:"<<endl;
				cin >> n;
				int a[n];
				cout<<"Enter elements:"<<endl;
				for(int i = 0;i<n;i++)
				{
					cin >> a[i];
				}
				SelectSort s;
				s.sort<int>(a, n);
				s.disp<int>(a, 5);
			}
			else if(op == 2)
			{
				int n;
				cout<<"Enter no of elements:"<<endl;
				cin >> n;
				float b[n];
				cout<<"Enter elements:"<<endl;
				for(int i = 0;i<n;i++)
				{
					cin >> b[i];
				}
				SelectSort s;
				s.sort<float>(b, n);
				s.disp<float>(b, n);
			}
			else
			{
			cout<<endl<<"Enter valid input!";
			continue;
			}
			int ch;
			cout<<"Do you want to continue?\nEnter 1 if yes else 0:";
			cin>>ch;
			if(ch == 1)
				continue;
			else
			{
				cout<<endl<<"Thanks for using!";
				break;
			}
		}
	return 0;
}


