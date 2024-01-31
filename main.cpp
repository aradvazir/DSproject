#include <iostream>
#include <vector>
#include <string>
#include "table.cpp"
using namespace std;

vector<string> split(string str)
{
    vector<string> res;
    string x="";
    for (int i=0; i<str.size(); i++)
    {
        if ((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z') || (str[i]>='0' && str[i]<='9'))
        {
            if ((str[i-1]>='a' && str[i-1]<='z') || (str[i-1]>='A' && str[i-1]<='Z') || (str[i-1]>='0' && str[i-1]<='9'))
                x+=str[i];
            else
            {
                if (!x.size())
                    x+=str[i];
                else
                {
                    res.push_back(x);
                    x="";
                }
            }
        }
        else if (str[i]==')' || str[i]=='(' || str[i]=='>' || str[i]=='<')
        {
            if (x.size())
            {
                res.push_back(x);
                x="";
                res.push_back(string(1, str[i]));
            }
            else
                res.push_back(string(1, str[i]));
        }
        else if ( str[i] == '=' && str[i-1] == '=' )
        {
            res.push_back("==");
        }
        else if (str[i]=='*')
        {
            if (x.size())
            {
                res.push_back(x);
                x="";
            }
            res.push_back(string(1, str[i]));
        }
        else
        {
            if (x.size())
            {
                res.push_back(x);
                x="";
            }
        }
    }
    if (x!="")
    {
        res.push_back(x);
    }
    return res;
}

int main() {
    vector<Table> tables;
    int n;
    cin >> n;
    if (cin.fail())
        cout << "Invalid input!" << endl;
    cin.ignore();
    for (int i=0; i<n; i++)
    {
        string input;
        getline(cin, input);

        vector<string> res=split(input);

        if (res[0]=="CREATE")
        {
            if (res[1]!="TABLE")
            {
                cout << "you have to enter 'table' after 'creat'1"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            if (res[3]!="(")
            {
                cout << "you have to enter '(' after table name"
                     << endl << "try again: ";;
                i-=1;
                continue;
            }
            vector<string> column_names;
            vector<string> types;
            for (int j=4; res[j]!=")"; j+=2)
            {
                column_names.push_back(res[j]);
                types.push_back(res[j+1]);
            }
            Table t(res[2], column_names, types);  //res[2]=tree name
            tables.push_back(t);
        }
        else if (res[0]=="INSERT")
        {
            if (res[1]!="INTO")
            {
                cout <<"Invalid input! you have to insert 'INTO' after 'Insert'"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            int j=0;
            int s=0;
            while (j < tables.size() && tables[j].get_name()!=res[2])
                j++;
            if (j>=tables.size())
            {
                cout << "there is no such a table"
                     << endl << "try again:";
                i-=1;
                s=1;
                continue;
            }
            if (res[3]!="VALUES")
            {
                cout << "you have to put 'VALUES' after table's name"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            if (res[4]!="(")
            {
                cout << "you have to put '(' after 'VALUES'"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            vector<string> pass_v;
            for (int p=5; res[p]!=")"; p++)
            {
                pass_v.push_back(res[p]);
            }
            tables[j].insert(pass_v);
        }
        else if (res[0]=="SELECT")
        {
            if (res[1]!="(" && res[1]!="*")
            {
                cout << "you have to put '(' or '*' after 'SELECT'"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            vector<string> chosen_columns;
            int p;
            if (res[1]=="(")
            {
                p=2;
                while (res[p]!=")")
                {
                    chosen_columns.push_back(res[p]);
                    p++;
                }
            }
            else
                p=1;
            if (res[p+1]!="FROM")
            {
                cout << "you have to put 'FROM' after columns name"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            p+=2;
            int j=0; //index of the table we want
            int s=0;
            while (j<tables.size() && tables[j].get_name()!=res[p])
                j++;
            if (j>=tables.size())
            {
                cout << "there is no such a table"
                     << endl << "try again:";
                i-=1;
                s=1;
                continue;
            }
            if (p-2==1)
            {
                for (int w=0; w<tables[j].get_num_of_columns(); w++)
                    chosen_columns.push_back("s");
            }
            if (res[p+1]!="WHERE")
            {
                cout << "you have to put 'WHERE' after table name"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            p+=2;
            vector<string> con;
            for (int q=p; q<res.size(); q++)
            {
                con.push_back(res[q]);
            }
            tables[j].select(con, chosen_columns);
        }
        else if (res[0]=="DELETE")
        {
            if (res[1]!="FROM")
            {
                cout << "you have to put 'FROM' after 'DELETE"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            int j=0;
            while (j < tables.size() && tables[j].get_name()!=res[2])
                j++;
            if (j>=tables.size())
            {
                cout << "there is no such a table"
                     << endl << "try again:";
                i-=1;
                continue;
            }
            if (res[3]!="WHERE")
            {
                cout << "you have to put 'WHERE' after changes"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            vector<string> con;
            for (int q=4; q<res.size(); q++)
            {
                con.push_back(res[q]);
            }
            tables[j].remove(con);
        }
        else if (res[0]=="UPDATE")
        {
            if (res[2]!="SET")
            {
                cout << "you have to put 'SET' after table name"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            int j=0;
            int s=0;
            while (tables[j].get_name()!=res[1])
            {
                if (j>=tables.size())
                {
                    cout << "there is no such a table"
                         << endl << "try again:";
                    i-=1;
                    s=1;
                    break;
                }
                j++;
            }
            if (s)
            {
                continue;
            }
            vector<string> changes;
            int a=0;
            while(res[a+4]!=")")
            {
                changes.push_back(res[a + 4]);
                a++;
            }
            a+=5;
            if (res[a]!="WHERE")
            {
                cout << "you have to put 'WHERE' after changes"
                     << endl << "try again: ";
                i-=1;
                continue;
            }
            vector<string> condition;
            for (int q=a+1; q<res.size(); q++)
                condition.push_back(res[q]);
            tables[j].update(changes, condition);
        }
        else
        {
            cout << "Invalid input!";
            i-=1;
        }
    }
    return 0;
}