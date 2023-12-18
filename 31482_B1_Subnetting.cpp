#include <iostream>
#include<vector>
#include<math.h>
#include<string>
using namespace std;
class  subnet{
    vector<int>myInput;
public:
    subnet(string inp){
        string octet="";
        int dummy;
        cout<<"\n";
        for(int i=0;i<inp.length();i++)
        {
            if(inp[i]=='.'){
                dummy=stoi(octet);
                myInput.push_back(dummy);
                octet="";
                continue;
            }
            octet=octet+inp[i];
        }
        dummy=stoi(octet);
        myInput.push_back(dummy);
        display();
        cout<<"\n";
    }
    void display(){
        for(int i=0;i<myInput.size();i++){
            cout<<myInput[i];
			if(i!=3)
			cout<<".";
        }
    }
    int getClass(){
        for(int i=0;i<myInput.size();i++){
            if(myInput[i]==0){
//              cout<<"class :"<<i<<endl;
                return i;
            }
        }
        return -1;
    }
    int getnearestPower(int num){
        int i=0;
        while(num>pow(2,i)){
            i++;
        }
        return i;
    }
    int binaryTodecimal(string str1){
//inp->binary string  ,op->integer decimal equi
        int sum=0;
        int myLen=str1.length();
        for(int i=myLen-1;i>=0;i--){
            string dum=str1.substr(i,1);
            sum+=stoi(dum)*pow(2,myLen-i-1);
        }
        return sum;
    }
    void divideSubnets(int numSubnets){
        int N=getnearestPower(numSubnets);
        int H=8*(4-getClass())-N;
        cout<<"N :"<<N<<" H:"<<H<<endl;
        cout<<"number of networks :"<<pow(2,N)<<endl;
        cout<<"Number of Hosts per network :"<<pow(2,H)-2<<endl;
        string buffer="";
        vector<int>myOutput;
        vector<int>difference;
        int myClass=getClass();
        for(int i=0;i<4;i++){
            if(buffer.length()==8){
                myOutput.push_back(binaryTodecimal(buffer));
                buffer="";
            }
            if(myInput[i]!=0){
                cout<<"11111111";
                myOutput.push_back(255);
            }
            else if(i==myClass){
					
                for(int j=0;j<8;j++){
                    string temp;
                    if(j<N){
                        cout<<"1";
                        buffer+="1";
                    }
                    else{
                        cout<<"0";
                        buffer+="0";
                    }
                }
            }
            else{
                cout<<"00000000";
                myOutput.push_back(0);
            }
            if(i!=3)
            cout<<".";
        }
		if(buffer.length()==8)
       	 myOutput.push_back(binaryTodecimal(buffer));
		 //----------------------------
        cout<<"\nOUTPUT :";
        for(int i=0;i<myOutput.size();i++){
            difference.push_back(255-myOutput[i]);
            cout<<myOutput[i];
            if(i!=3)
            cout<<".";

        }
		//---------------------------
        cout<<"\nDifference :";
        for(int i=0;i<difference.size();i++){
            cout<<difference[i];
            if(i!=3)
            cout<<".";

        }
		//----------------------------
        cout<<"\nClass :"<<char(myClass+'A'-1)<<endl;
        buffer="";
        int i;
        for(i=0;i<myClass;i++){
                buffer+=to_string(myInput[i]);
                buffer+=".";
        }
        int incr=difference[i];
        int tempo=0;
        cout<<"\nBuffer :"<<buffer<<endl;
        cout<<"incr :"<<incr<<endl;

		cout<<"\n\t\tNetwork Add\tBroadcast Add"<<endl;
        for(int j=0;j<pow(2,N);j++){// for num of networks
           cout<<"\nSubnet "<<j+1<<"\t"<<buffer<<tempo;
            if(myClass==2)
            cout<<".255";
            else if(myClass==1)
            cout<<".255.255";
            else if(myClass==0)
            cout<<".255.255.255";
           tempo+=incr;
        cout<<"\t"<<buffer<<tempo;
            if(myClass==2)
            cout<<".255";
            else if(myClass==1)
            cout<<".255.255";
            else if(myClass==0)
            cout<<".255.255.255";
            tempo+=1;
        }
    }
	  void divideSubnetsByHosts(int numSubnets){
        int H=getnearestPower(numSubnets);    //N ad H get interchanged 
        int N=8*(4-getClass())-H;             //notable differene from network based subnetting
        cout<<"N :"<<N<<" H:"<<H<<endl;
        cout<<"number of networks :"<<pow(2,N)<<endl;
        cout<<"Number of Hosts per network :"<<pow(2,H)-2<<endl;
        string buffer="";
        vector<int>myOutput;
        vector<int>difference;
        int myClass=getClass();
        for(int i=0;i<4;i++){
            if(buffer.length()==8){
                myOutput.push_back(binaryTodecimal(buffer));
                buffer="";
            }
            if(myInput[i]!=0){
                cout<<"11111111";
                myOutput.push_back(255);
            }
            else if(i==myClass){
				if(N>8){                      //
					cout<<"11111111.";        //
                	myOutput.push_back(255);  //  --->extra code for 
					N-=8;                     //      subnetting based 
					i++;                      //      on hosts
					myClass++;                //
				}
                for(int j=0;j<8;j++){
                    string temp;
                    if(j<N){
                        cout<<"1";
                        buffer+="1";
                    }
                    else{
                        cout<<"0";
                        buffer+="0";
                    }
                }
            }
            else{
                cout<<"00000000";
                myOutput.push_back(0);
            }
            if(i!=3)
            cout<<".";
        }
		if(buffer.length()==8)
       	 myOutput.push_back(binaryTodecimal(buffer));
		 //----------------------------
        cout<<"\nOUTPUT :";
        for(int i=0;i<myOutput.size();i++){
            difference.push_back(255-myOutput[i]);
            cout<<myOutput[i];
            if(i!=3)
            cout<<".";

        }
		//---------------------------
        cout<<"\nDifference :";
        for(int i=0;i<difference.size();i++){
            cout<<difference[i];
            if(i!=3)
            cout<<".";

        }
		//----------------------------
        cout<<"\nClass :"<<char(myClass+'A'-1)<<endl;
        buffer="";
        int i;
        for(i=0;i<myClass;i++){
                buffer+=to_string(myInput[i]);
                buffer+=".";
        }
        int incr=difference[i];
        int tempo=0;
        cout<<"\nBuffer :"<<buffer<<endl;
        cout<<"incr :"<<incr<<endl;

		cout<<"\n\t\tNetwork Add\tBroadcast Add"<<endl;
        for(int j=0;j<pow(2,N);j++){// for num of networks
           cout<<"\nSubnet "<<j+1<<"\t"<<buffer<<tempo;
            if(myClass==2)
            cout<<".255";
            else if(myClass==1)
            cout<<".255.255";
            else if(myClass==0)
            cout<<".255.255.255";
           tempo+=incr;
        cout<<"\t"<<buffer<<tempo;
            if(myClass==2)
            cout<<".255";
            else if(myClass==1)
            cout<<".255.255";
            else if(myClass==0)
            cout<<".255.255.255";
            tempo+=1;
        }
    }
};

int main() {
	cout<<"\n-------Based on Networks--------\n";
//  subnet obj("192.168.6.0");
//  obj.divideSubnets(4);
 	subnet obj("10.0.0.0");
    obj.divideSubnets(100);
	cout<<"\n-------Based on Hosts--------\n";
    subnet obj2("192.168.6.0");
    obj2.divideSubnetsByHosts(28);
//  subnet obj2("10.0.0.0");
//  obj2.divideSubnetsByHosts(4000);  //->console not supporting 4K
    return 0;

}