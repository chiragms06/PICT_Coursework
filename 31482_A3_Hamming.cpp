#include <bits/stdc++.h>
using namespace std;

class HammingCode
{
private:
    string send, rec;
    int r, m;

public:
    HammingCode()
    {
        send = "";
        r = m = 0;
    }
    HammingCode(string s1)
    {
        send = s1;
        m = send.length();
        r = 0;
    }

    // finding the value of r using the formula : 2^r >= m + r + 1
    int find_r(int m)
    {
        for (int i = 0; i < m; i++)
        {
            if (pow(2, i) >= m + i + 1)
            {
                r = i;
                return r;
            }
        }
        return 0;
    }

    // checking the parity
    char find_parity(string s)
    {
        int cnt_1 = 0;
        int n = s.length();
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '1')
                cnt_1++;
        }
        if (cnt_1 % 2 != 0)
        {
            return '1';
        }
        else
        {
            return '0';
        }
    }

    void generate_code()
    {
        cout << "---At sender's end---" << endl;
        r = find_r(m);
        char rbit[r];
        for (int i = 0; i < r; i++)
        {
            rbit[i] = 'r';
        }

        int len = m + r;
        char arr[len];
        for (int i = 0; i < r; i++)
        {
            int p = pow(2, i);
            arr[p - 1] = rbit[i];
        }

        int j = m - 1;
        for (int i = 0; i < len; i++)
        {
            if (arr[i] != 'r')
            {
                arr[i] = send[j];
                j--;
            }
        }

        // for(int i=len-1;i>=0;i--)
        // {
        //     cout<<arr[i]<<" ";
        // }

        for (int i = 0; i < r; i++)
        {
            string s = "";
            int cnt = pow(2, i);
            for (int j = cnt - 1; j < len; j += 2 * cnt)
            {
                for (int k = 0; k < cnt; k++)
                {
                    if (k + j < len && arr[k + j] != 'r')
                    {
                        s += arr[k + j];
                    }
                }
            }
            char rval = find_parity(s);
            // cout<<rval<<endl;
            arr[cnt - 1] = rval;
            // cout<<"hi :"<<s<<endl;
        }

        cout << "The Hamming code generated is :" << endl;
        for (int i = len - 1; i >= 0; i--)
        {
            cout << arr[i];
        }

        cout << endl;

        cout << "---At receiver's end---" << endl;

        string rec;
        cout << "Enter data : ";
        cin >> rec;

        char a[len];
        for (int i = 0; i < rec.length(); i++)
        {
            a[rec.length() - i - 1] = rec[i];
        }

        string r_arr[r];
        for (int i = 0; i < r; i++)
        {
            string s = "";
            int cnt = pow(2, i);
            for (int j = cnt - 1; j < len; j += 2 * cnt)
            {
                for (int k = 0; k < cnt; k++)
                {
                    if (k + j < len)
                    {
                        s += a[k + j];
                    }
                }
            }
            r_arr[i] = s;
        }

        char p_bit[r];
        for (int i = 0; i < r; i++)
        {
            char rval = find_parity(r_arr[i]);
            p_bit[i] = rval;
        }

        int pos = 0, flag = 0;
        for (int i = 0; i < r; i++)
        {
            if (p_bit[i] == '1')
            {
                pos = pow(2, i);
                cout << "Error in the data at bit no. " << pos << " from LSB !!" << endl;
                flag = 1;
            }
        }

        if (flag != 1)
        {
            cout << "No error in the data :)" << endl;
        }
    }
};

int main()
{
    string s;
    cout << "Enter the data to be sent :";
    cin >> s;
    HammingCode h(s);

    h.generate_code();
    return 0;
}

// 11001
// 1011001
// 1101001