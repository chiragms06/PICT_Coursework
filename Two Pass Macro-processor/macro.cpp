#include <bits/stdc++.h>
using namespace std;

class macro
{
private:
    vector<tuple<string, int, int, int, int>> MNTAB;
    vector<tuple<string, string>> KDTAB;
    vector<vector<tuple<string, string>>> APTAB;
    vector<vector<string>> MDT;
    vector<vector<string>> PNTAB;
    vector<vector<string>> myToken;
    ifstream ipfile;

public:
    macro()
    {
        ipfile.open("input1.txt", ios::in);
        string buffer;
        string words;
        while (!ipfile.eof())
        {
            vector<string> token;
            getline(ipfile, buffer);
            stringstream ss(buffer);
            while (ss >> words)
            {
                if (words != ",")
                    token.push_back(words);
            }
            myToken.push_back(token);
        }
        displayToken();
    }

    void displayToken()
    {
        for (int i = 0; i < myToken.size(); i++)
        {
            cout << i << " : ";
            for (int j = 0; j < myToken[i].size(); j++)
            {
                cout << myToken[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void displayAll()
    {
        // MNT
        cout << "------MNT------" << endl;
        cout << "NAME\t#PP\t#KP\t#MDTP\t#KDTP" << endl;
        for (int i = 0; i < MNTAB.size(); i++)
        {
            string name = get<0>(MNTAB[i]);
            int PP = get<1>(MNTAB[i]);
            int KP = get<2>(MNTAB[i]);
            int MDTP = get<3>(MNTAB[i]);
            int KDTP = get<4>(MNTAB[i]);

            cout << name << "\t" << PP << "\t" << KP << "\t" << MDTP << "\t" << KDTP << endl;
        }
        cout << "---------------" << endl;
        cout << endl;

        // MDT
        cout << "------MDT------" << endl;
        for (int i = 0; i < MDT.size(); i++)
        {
            for (int j = 0; j < MDT[i].size(); j++)
            {
                cout << MDT[i][j] << "\t";
            }
            cout << endl;
        }
        cout << "---------------" << endl;
        cout << endl;

        // KDTAB
        cout << "------KDTAB------" << endl;
        cout << "KEYWORD\tVALUE" << endl;
        for (int i = 0; i < KDTAB.size(); i++)
        {
            string keyword = get<0>(KDTAB[i]);
            string value = get<1>(KDTAB[i]);

            cout << keyword << "\t" << value << endl;
        }
        cout << "---------------" << endl;
        cout << endl;

        // PNTAB
        cout << "------PNTAB------" << endl;
        for (int i = 0; i < PNTAB.size(); i++)
        {
            for (int j = 0; j < PNTAB[i].size(); j++)
            {
                cout << PNTAB[i][j] << "\t";
            }
            cout << endl;
        }
        cout << "---------------" << endl;
        cout << endl;
    }

    void displayAPTAB(string macroName, vector<string> &APTAB)
    {
        cout << "------APTAB[ " << macroName << "]------" << endl;
        for (int i = 0; i < APTAB.size(); i++)
        {
            cout << i << " : " << APTAB[i] << endl;
        }
        cout << "---------------------" << endl;
        cout << endl;
    }

    int deal(string token, int index)
    {
        // searches in PNTAB for curr token
        for (int i = 0; i < PNTAB[index].size(); i++)
        {
            if (PNTAB[index][i] == token)
            {
                return i + 1;
            }
        }
        return -1;
    }

    int storeDefinition(int lineNum)
    {
        string name;
        vector<string> tempPNTAB;
        int PP, KP, KDTP, MDTP, j;
        PP = KP = 0;
        KDTP = KDTAB.size();
        MDTP = MDT.size();

        // first line(macro_name and parameters)
        name = myToken[lineNum][0];
        for (int i = 1; i < myToken[lineNum].size(); i++)
        {
            string currToken = myToken[lineNum][i];
            if (currToken.find("=") != string::npos)
            {
                // keyword para
                KP++;
                auto index = currToken.find("=");
                string keyword = currToken.substr(0, index);
                string value = currToken.substr(index + 1, currToken.size() - index);
                tuple<string, string> t1(keyword, value);
                KDTAB.push_back(t1);
                tempPNTAB.push_back(keyword);
            }
            else
            {
                // pos para
                tempPNTAB.push_back(currToken);
            }
        }
        PP = tempPNTAB.size() - KP;
        PNTAB.push_back(tempPNTAB);

        // rem. lines(macro_body and MEND)
        for (j = lineNum + 1; j < myToken.size() && myToken[j][0] != "MEND"; j++)
        {
            vector<string> v1;
            for (int i = 0; i < myToken[j].size(); i++)
            {
                int index = deal(myToken[j][i], PNTAB.size() - 1);
                if (index != -1)
                {
                    // parameter
                    v1.push_back("(P," + to_string(index) + ")");
                }
                else
                {
                    // non-para(registers)
                    v1.push_back(myToken[j][i]);
                }
            }
            MDT.push_back(v1);
            cout << endl;
        }
        MDT.push_back({"MEND"});
        MNTAB.push_back(make_tuple(name, PP, KP, MDTP, KDTP));
        return j;
    }

    void pass1()
    {
        for (int i = 0; i < myToken.size(); i++)
        {
            vector<string> curr = myToken[i];
            for (int j = 0; j < myToken[i].size(); j++)
            {
                if (curr[j] == "MACRO")
                {
                    i = storeDefinition(i + 1);
                    break;
                }
            }
        }
        // displayAll();
    }

    int findInMNT(string name)
    {
        for (int i = 0; i < MNTAB.size(); i++)
        {
            if (name == get<0>(MNTAB[i]))
            {
                return i;
            }
        }
        return -1;
    }

    int getMacroLength(string name)
    {
        int index = findInMNT(name);
        for (int k = get<3>(MNTAB[index]);; k++)
        {
            if (MDT[k][0] == "MEND")
            {
                return k + 1 - get<3>(MNTAB[index]);
            }
        }
    }

    int getKeywordIndex(string keyword, int macroIndex)
    {
        vector<string> currParameters = PNTAB[macroIndex];
        for (int i = 0; i < currParameters.size(); i++)
        {
            if (currParameters[i] == keyword)
            {
                return i;
            }
        }
        return -1;
    }

    string getKeywordValue(string key, int KDTP)
    {
        for (int i = KDTP; i < KDTAB.size(); i++)
        {
            if (get<0>(KDTAB[i]) == key)
            {
                return get<1>(KDTAB[i]);
            }
        }
        return "NOT TODAY";
    }

    void expandMacro(vector<string> &currSentence, ofstream &opfile)
    {
        int index = findInMNT(currSentence[0]);
        int numPP = get<1>(MNTAB[index]);
        int numKP = get<2>(MNTAB[index]);
        int MDTP = get<3>(MNTAB[index]);
        int KDTP = get<4>(MNTAB[index]);

        //-------make APTAB------------
        vector<string> APTAB(numPP + numKP, "NULL");
        // push PP
        int i;
        for (i = 1; i <= numPP; i++)
        {
            APTAB[i - 1] = currSentence[i];
        }

        // determine keyword then push(KP with val)
        for (; i < currSentence.size(); i++)
        {
            auto loc = currSentence[i].find("=");
            string keyword = currSentence[i].substr(0, loc);
            string value = currSentence[i].substr(loc + 1, currSentence[i].length() - loc);
            APTAB[getKeywordIndex(keyword, index)] = value;
        }

        // default values(KP w/o val)
        for (int i = 0; i < APTAB.size(); i++)
        {
            if (APTAB[i] == "NULL")
            {
                string key = PNTAB[index][i];
                APTAB[i] = getKeywordValue(key, KDTP);
            }
        }
        displayAPTAB(get<0>(MNTAB[index]), APTAB);
        //--------APTAB made--------------

        for (int i = MDTP; MDT[i][0] != "MEND"; i++)
        {
            for (int j = 0; j < MDT[i].size(); j++)
            {
                string instruct = MDT[i][j];
                if (instruct.find("(") != string::npos)
                {
                    // cout << "String before stoi: " << instruct << endl;

                    int temp = stoi(instruct.substr(3, 1));
                    opfile << APTAB[temp - 1] << " ";
                }
                else
                    opfile << instruct << " ";
            }
            opfile << endl;
        }
    }

    void pass2()
    {
        ofstream opfile("expandedCode.txt", ios::out);
        pass1();
        displayAll();
        for (int i = 0; i < myToken.size(); i++)
        {
            vector<string> curr = myToken[i];
            for (int j = 0; j < myToken[i].size(); j++)
            {
                if (curr[j] == "MACRO")
                {
                    i = i + 1 + getMacroLength(myToken[i + 1][0]);
                    break;
                }
                else if (findInMNT(curr[j]) != -1)
                {
                    expandMacro(curr, opfile);
                    break;
                }
                else
                {
                    opfile << curr[j] << " ";
                }
            }
            opfile << endl;
        }
    }
};

int main()
{
    macro obj;
    obj.pass2();
    return 0;
}
