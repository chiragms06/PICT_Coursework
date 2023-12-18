#include <bits/stdc++.h>
using namespace std;

class MachineOpcodeTable
{
    map<string, pair<string, int>> IS;
    map<string, pair<string, int>> AD;
    map<string, pair<string, int>> REG;
    map<string, pair<string, int>> CC;
    map<string, pair<string, int>> DL;

public:
    MachineOpcodeTable()
    {
        // imperative
        IS["STOP"] = {"IS", 00};
        IS["ADD"] = {"IS", 01};
        IS["SUB"] = {"IS", 02};
        IS["MUL"] = {"IS", 03};
        IS["MOVER"] = {"IS", 04};
        IS["MOVEM"] = {"IS", 05};

        IS["COMP"] = {"IS", 06};
        IS["BC"] = {"IS", 07};
        IS["DIV"] = {"IS", 8};
        IS["READ"] = {"IS", 9};
        IS["PRINT"] = {"IS", 10};
        IS["START"] = {"AD", 00};
        IS["END"] = {"AD", 02};
        IS["ORIGIN"] = {"AD", 03};
        IS["EQU"] = {"AD", 04};
        IS["LTORG"] = {"AD", 05};

        // declarative
        DL["DS"] = {"DL", 02};
        DL["DC"] = {"DL", 01};

        // register
        REG["AREG"] = {"RG", 01};
        REG["BREG"] = {"RG", 02};
        REG["CREG"] = {"RG", 03};
        REG["DREG"] = {"RG", 04};

        // CC
        CC["EQ"] = {"CC", 01};
        CC["LT"] = {"CC", 02};
        CC["GT"] = {"CC", 03};
        CC["LE"] = {"CC", 04};
        CC["GE"] = {"CC", 05};
        CC["NE"] = {"CC", 06};
        CC["ANY"] = {"CC", 07};
    }

    pair<string, int> findOpcode(string opcode)
    {
        auto IT = IS.find(opcode);
        if (IT != IS.end())
            return IS[opcode];
        IT = AD.find(opcode);
        if (IT != AD.end())
            return AD[opcode];
        IT = REG.find(opcode);
        if (IT != REG.end())
            return REG[opcode];
        IT = DL.find(opcode);
        if (IT != DL.end())
            return DL[opcode];
        IT = CC.find(opcode);
        if (IT != CC.end())
            return CC[opcode];
        if (opcode[0] == '=')
            return {"L", -1};
        return {"S", -1};
    }
};

class symbolTable
{
    vector<pair<string, int>> SYMTAB;
    friend class assembler;
    int symCount = 0;
    ofstream syFile;

public:
    symbolTable()
    {
        syFile.open("STM.txt", ios::out);
        syFile << "Symbol\tAddress" << endl;
    }

    bool present(string sym)
    {
        vector<pair<string, int>>::iterator IT = SYMTAB.begin();
        while (IT < SYMTAB.end())
        {
            if (IT->first == sym)
                return true;
            IT++;
        }
        return false;
    }

    void handleSymbol(string sym, int curLC, bool defination_flag)
    {
        if (defination_flag)
        {
            if (!present(sym))
                SYMTAB.push_back({sym, curLC});
            else                                          // forward definition
                SYMTAB[getIndex(sym) - 1].second = curLC; // update address
        }
        else if (!present(sym))
            SYMTAB.push_back({sym, 999});
    }

    int getIndex(string sym)
    {
        vector<pair<string, int>>::iterator IT = SYMTAB.begin();
        int index = 0;
        while (IT < SYMTAB.end())
        {
            if (IT->first == sym)
                return index + 1;
            index++;
            IT++;
        }
        return -1;
    }

    int getAddress(string sym)
    {
        return SYMTAB[getIndex(sym) - 1].second;
    }

    void displayST()
    {
        cout << "\n---------SYMTAB------------\n";
        vector<pair<string, int>>::iterator IT = SYMTAB.begin();
        while (IT != SYMTAB.end())
        {
            cout << "\n"
                 << IT->first << "\t" << IT->second;
            syFile << IT->first << "\t\t" << IT->second << endl;
            IT++;
        }
        cout << "\n---------------------------\n";
    }
};

class literalTable
{
    vector<pair<string, int>> LTAB;
    int litCount = 0;
    friend class assembler;
    fstream ltFile;
    vector<string> LPool;

public:
    literalTable()
    {
        ltFile.open("LT.txt", ios::out);
        ltFile << "Literal\tAddress" << endl;
    }

    void updateAddress(string lit, int add)
    {
        LTAB.push_back({lit, add});
    }

    void displayLT()
    {
        vector<pair<string, int>>::iterator IT = LTAB.begin();
        cout << "\n---------LTAB------------\n";
        while (IT != LTAB.end())
        {
            cout << "\n"
                 << IT->first << "\t" << IT->second;
            ltFile << "\n"
                   << IT->first << "\t" << IT->second;
            IT++;
        }
        cout << "\n--------------------------\n";
    }

    int computePool(int curLC, ofstream &fobj2)
    {
        fobj2 << endl;
        for (int i = 0; i < LPool.size(); i++)
        {
            curLC++;
            updateAddress(LPool[i], curLC);
            fobj2 << curLC << "-> ";
            fobj2 << "(DL,01) "
                  << "(C," << LPool[i].substr(2, 1) << ")\t" << endl;
        }
        LPool = {};
        return curLC;
    }
};

class assembler
{

    MachineOpcodeTable obj;
    symbolTable symObj;
    literalTable litObj;
    ifstream fobj;
    ofstream fobj2;
    int poolTableCount = 0;
    int LC;
    int lC_incr = 1;

public:
    assembler()
    {
        fobj.open("input.txt");
        fobj2.open("IC.txt", ios::out);
        if (!fobj)
            cerr << "NO such file!" << endl;
        else
            cout << "File opened successfully!" << endl;
    }
    void pass1()
    {
        string buffer;

        while (!fobj.eof())
        {
            bool flag = true;
            lC_incr = 1;
            getline(fobj, buffer);
            stringstream ss(buffer);
            string words;
            vector<string> tokens;
            fobj2 << LC + 1 << "-> ";
            while (ss >> words)
            {
                tokens.push_back(words);
            }
            for (int i = 0; i < tokens.size(); i++)
            {
                //-------********************-----------------------
                if (tokens.size() == 4)
                {
                    // 4 tokens
                    i += 4;
                    LC++;
                    symObj.handleSymbol(tokens[0], LC, true);
                    auto mnemonic = obj.findOpcode(tokens[1]);
                    auto operand1 = obj.findOpcode(tokens[2]);
                    auto operand2 = obj.findOpcode(tokens[3]);
                    fobj2 << "(" << mnemonic.first << "," << mnemonic.second << ") ";
                    fobj2 << "(" << operand1.first << "," << operand1.second << ") ";
                    if (operand2.first == "L")
                    {
                        litObj.LPool.push_back(tokens[3]);
                        litObj.litCount++;
                        fobj2 << "(L," << litObj.litCount << ") ";
                    }
                    else
                    {
                        symObj.handleSymbol(tokens[3], LC, false);
                        fobj2 << "(S," << symObj.getIndex(tokens[3]) << ") ";
                    }
                }
                //------------------*******************--------------------------
                else
                {               // tokens<4
                    int MN = 0; //
                    // label encountered
                    auto mnemonic = obj.findOpcode(tokens[0]);
                    if (mnemonic.first == "S")
                    {
                        i += 1;
                        symObj.handleSymbol(tokens[0], LC, true);
                        MN = 1;
                    }
                    mnemonic = obj.findOpcode(tokens[MN]);

                    //-----------------------------------------------
                    // IS
                    if (mnemonic.first == "IS")
                    { // tokens=3
                        if (tokens[MN] == "PRINT" || tokens[MN] == "READ")
                        { // 2 tokens
                            LC++;
                            i += 2;
                            symObj.handleSymbol(tokens[MN + 1], LC, false);
                            fobj2 << "(" << mnemonic.first << "," << mnemonic.second << ") (S," << symObj.getIndex(tokens[MN + 1]) << ") ";
                        }
                        else if (tokens[MN] == "STOP")
                        { // 1 token
                            LC++;
                            i++;
                            fobj2 << "(" << mnemonic.first << "," << mnemonic.second << ") ";
                        }
                        else
                        {
                            LC++;
                            i += 3;
                            auto operand1 = obj.findOpcode(tokens[MN + 1]);
                            fobj2 << "(" << mnemonic.first << "," << mnemonic.second << ") ";
                            fobj2 << "(" << operand1.first << "," << operand1.second << ") ";
                            auto operand2 = obj.findOpcode(tokens[MN + 2]);
                            if (operand2.first == "L")
                            {
                                litObj.LPool.push_back(tokens[MN + 2]);
                                litObj.litCount++;
                                fobj2 << "(L," << litObj.litCount << ") ";
                            }
                            else
                            {
                                symObj.handleSymbol(tokens[2], LC, false);
                                fobj2 << "(S," << symObj.getIndex(tokens[2]) << ") ";
                            }
                        }
                    }
                    //-------------------------------------------------

                                        // AD
                    else if (mnemonic.first == "AD")
                    { // tokens<=2
                        if (tokens[MN] == "START")
                        {
                            LC = stoi(tokens[MN + 1]);

                            fobj2 << "(AD," << mnemonic.second << ") (C," << LC << ") ";
                            LC -= 1; //-1 to keep LC same for next statement
                            i += 2;
                            continue;
                        }
                        else if (tokens[MN] == "ORIGIN")
                        {
                            fobj2 << "(AD," << mnemonic.second << ") ";
                            i += 2;
                            if (tokens[MN + 1].find("+") != string::npos)
                            {
                                auto label = tokens[MN + 1].substr(0, tokens[MN + 1].find("+"));
                                int offset = stoi(tokens[MN + 1].substr(tokens[MN + 1].find("+") + 1, tokens[MN + 1].length()));
                                // cout<<"L&O :"<<label<<"\t"<<offset<<endl;
                                LC = symObj.getAddress(label) + offset;
                            }
                            else if (tokens[MN + 1].find("-") != string::npos)
                            {
                                auto label = tokens[MN + 1].substr(0, tokens[MN + 1].find("-"));
                                int offset = stoi(tokens[MN + 1].substr(tokens[MN + 1].find("-") + 1, tokens[MN + 1].length()));
                                // cout<<"L&O :"<<label<<"\t"<<offset<<endl;
                                LC = symObj.getAddress(label) - offset;
                            }
                            else
                            {
                                LC = stoi(tokens[MN + 1]);
                            }
                            LC -= 1; //-1 to keep LC same for next statement
                            continue;
                        }
                        //------------------------------------------------
                        else if (tokens[MN] == "LTORG")
                        {
                            i += 2;
                            LC = litObj.computePool(LC, fobj2);
                            flag = false;
                        }
                        //------------------------------------------------
                        else if (tokens[MN] == "EQU")
                        {
                            // thus prev token(MN-1) is label;
                            //  and next (MN+1) is LC to set
                            i += 3;
                            LC++;
                            int offset = 0;
                            string label = tokens[MN + 1];
                            if (tokens[MN + 1].find("+") != string::npos)
                            {
                                label = tokens[MN + 1].substr(0, tokens[MN + 1].find("+"));
                                offset = stoi(tokens[MN + 1].substr(tokens[MN + 1].find("+") + 1, tokens[MN + 1].length()));
                                // cout<<"L&O :"<<label<<"\t"<<offset<<endl;
                                LC = symObj.getAddress(label) + offset;
                            }
                            else if (tokens[MN + 1].find("-") != string::npos)
                            {
                                label = tokens[MN + 1].substr(0, tokens[MN + 1].find("-"));
                                offset = stoi(tokens[MN + 1].substr(tokens[MN + 1].find("-") + 1, tokens[MN + 1].length()));
                                // cout<<"L&O :"<<label<<"\t"<<offset<<endl;ṇ
                                LC = symObj.getAddress(label) - offset;
                            }
                            symObj.handleSymbol(tokens[MN - 1], symObj.getAddress(label) + offset, true);
                            fobj2 << "(" << mnemonic.first << "," << mnemonic.second << ") ";
                            fobj2 << "(S," << symObj.getIndex(label) << ")";
                        }
                        else if (tokens[MN] == "BC")
                        {
                            i += 3;
                            LC++;
                            auto operand1 = obj.findOpcode(tokens[MN + 1]);
                            fobj2 << "(" << mnemonic.first << "," << mnemonic.second << ") ";
                            fobj2 << "(" << operand1.first << "," << operand1.second << ") ";
                            fobj2 << "(S," << symObj.getIndex(tokens[MN + 2]) << ")";
                        }
                        else
                        { // tokens[MN]=="END"
                            fobj2 << "(" << mnemonic.first << "," << mnemonic.second << ") ";
                            // same code as LTORG
                            LC = litObj.computePool(LC + 1, fobj2);
                            break;
                        }
                    }
                    // DL
                    else
                    {
                        if (tokens[MN] == "DS")
                        {
                            i += 2; // should be i+=3 but symbol token is already considered at start(first if condition)
                            LC++;
                            string label = tokens[0];
                            int length = stoi(tokens[2]);
                            symObj.handleSymbol(label, LC, true); //--->NO NEED AS ITS ALREADY HANDLED
                            fobj2 << "(DL," << mnemonic.second << ") (C," << length << ") ";
                            LC += length - 1; // incr LC by size
                            continue;         // continue as LC is already printed
                        }
                        else
                        { // DC
                            i += 2;
                            LC++;
                            string label = tokens[0];
                            symObj.handleSymbol(label, LC, true);             //--->NO NEED AS ITS ALREADY HANDLED
                            fobj2 << "(DL," << mnemonic.second << ") (C,1) "; // for DC length is 1
                            continue;
                        }
                    }
                }
            }
            if (flag) // next line only when break statement{
                fobj2 << endl;
        }
        symObj.displayST();
        litObj.displayLT();
        fobj2.close();
    }

    pair<string, int> get_codes(string token)
    {
        // for each IC token this returns the opcode and its value
        //  i.e for (IS,01)----> {"IS",1}
        string S1, S2;
        bool flag = false;
        for (int i = 1; i < token.length() - 1; i++)
        {
            if (token.substr(i, 1) == ",")
            {
                flag = true;
                continue;
            }
            if (flag)
                S2 += token.substr(i, 1);
            else
                S1 += token.substr(i, 1);
        }
        int number = stoi(S2);
        cout << S1 << "-" << S2;
        return {S1, number};
    }

    void pass2()
    {
        pass1();
        string buffer;
        ifstream ICFile;
        ICFile.open("IC.txt");
        ofstream MCFile;
        MCFile.open("MC.txt", ios::out);
        while (!ICFile.eof())
        {
            MCFile << " " << endl;
            // get tokens from IC File
            getline(ICFile, buffer);
            stringstream ss(buffer);
            string words;
            vector<string> tokens;
            while (ss >> words)
            {
                tokens.push_back(words);
            }
            // consider each token
            // First token is always LC
            MCFile << tokens[0];
            for (int i = 1; i < tokens.size(); i++)
            {
                pair<string, int> myToken = get_codes(tokens[i]);
                // MCFile<<myToken.first<<" "<<myToken.second<<"  ";
                if (myToken.first == "IS" || myToken.first == "RG")
                {
                    MCFile << myToken.second << "\t";
                }
                if (myToken.first == "AD")
                {
                    MCFile << "----------";
                    break; // move to next line
                }
                if (myToken.first == "DL")
                {
                    if (myToken.second == 1)
                    {
                        MCFile << myToken.second << "\t";
                    }
                    else
                    {
                        MCFile << "----------";
                        break; // move to next line
                    }
                }
                if (myToken.first == "C")
                {
                    MCFile << myToken.second << "\t";
                }
                if (myToken.first == "S")
                {
                    MCFile << symObj.SYMTAB[myToken.second - 1].second;
                }
                if (myToken.first == "L")
                    MCFile << litObj.LTAB[myToken.second - 1].second;
            }
        }
        MCFile.close();
    }
};

int main()
{
    assembler obj2;
    obj2.pass2();
    return 0;
}

