#include "B-tree.cpp"
#include "heap.cpp"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

class Table
{
    friend class B_tree;
public:
    Table(string name, vector<string> names, vector<string> types)
    {
        table_name=name;
        for (int i=0; i<names.size(); i++)
            column_names.push_back(names[i]);
        num_of_columns=column_names.size()+1;
        for (int i=0; i<types.size(); i++)
            column_types.push_back(types[i]);
        trees=new B_tree*[num_of_columns];
        for (int i=0; i<num_of_columns; i++)
            trees[i]=new B_tree(2);
        size=0;
        biggest_used_ID=0;
        empty_IDs=new heap<int>(100000);
    }

    void insert(vector<string> arr)
    {
        Node* prev= nullptr;
        Node* last= nullptr;
        int j=arr.size()-1;
        for (int i=num_of_columns-1; i>=1; i--)
        {
            if (column_types[i-1]=="int")
            {
                prev= trees[i]->insert(stoi(arr[j]), prev);
                j--;
            }
            else if (column_types[i-1]=="string")
            {
                prev= trees[i]->insert(hash_str(arr[j]), prev);
                j--;
            }
            else if (column_types[i-1]=="timestamp")
            {
                prev= trees[i]->insert(hash_time(arr[j], arr[j-1], arr[j-2]), prev);
                j-=3;
            }
            if (i==num_of_columns-1)
                last=prev;
        }
        if (empty_IDs->is_empty())
            prev= trees[0]->insert(++biggest_used_ID, prev);
        else
        {
            prev=trees[0]->insert(empty_IDs->pop(), prev);
        }
        last->nextField=prev;
        size++;
    }

    void remove(vector<string> cond)
    {
        how_many_deleted=0;
        int search_condition = 0;
        int n;
        int i = num_of_columns;
        for (int j = 0; j < num_of_columns - 1; j++) {
            if (cond[0] == column_names[j])
            {
                search_condition = 0;
                if (column_types[j] == "int")
                    n = stoi(cond[2]);
                else if (column_types[j] == "string")
                    n = hash_str(cond[2]);
                else if (column_types[j] == "timestamp")
                    n = hash_time(cond[4], cond[3], cond[2]);
                i = j;
                break;
            }
            else if (cond[cond.size() - 1] == column_names[j])
            {
                search_condition = cond.size() - 1;
                if (column_types[j] == "int")
                    n = stoi(cond[0]);
                else if (column_types[j] == "string")
                    n = hash_str(cond[0]);
                else if (column_types[j] == "timestamp")
                    n = hash_time(cond[2], cond[1], cond[0]);
                i = j;
                break;
            }
        }
        i++;
        if (i == num_of_columns) {
            cout << "there is no such column" << endl;
            throw 2;
        }
        vector<Node> result;
        if (cond[1]=="==" || (cond.size()==5 && cond[3]=="==")) //condition is ==
        {
            find1(trees[i]->get_root(), n, result);
        }
        else if (cond[1]==">" || (cond.size()==5 && cond[3]=="<")) //condition is >
        {
            find2(trees[i]->get_root(), n, result);
        }
        else if (cond[1]=="<" || (cond.size()==5 && cond[3]==">")) //condition is <
        {
            find3(trees[i]->get_root(), n, result);
        }
        how_many_deleted=result.size();
        for (int p=0; p<result.size(); p++)
        {
            Node temp;
            Node temp2;
            Node temp4;
            temp=result[p];
            for (int q=0; q<num_of_columns; q++)
            {
                temp4=*temp.nextField;
                temp2=*trees[(i+q)%num_of_columns]->search(temp.data);
                if (&temp2!= nullptr && &temp2!=&temp)
                {
                    Node t=temp;
                    temp.nextField=temp2.nextField;
                    temp2.nextField=&t;
                    Node A=temp;
                    Node B=temp2;
                    for (int d=0; d<num_of_columns-1; d++)
                    {
                        A=*A.nextField;
                        B=*B.nextField;
                    }
                    A.nextField=&temp2;
                    B.nextField=&temp;
                }
                if ((i+q)%num_of_columns==0)
                {
                    empty_IDs->insert(temp2.data);
                }
                trees[(i+q)%num_of_columns]->del(temp2.data);
                temp=temp4;
            }
        }
    }

    void update(vector<string> changes, vector<string> cond)
    {
        vector<int> s;
        while (!empty_IDs->is_empty())
            s.push_back(empty_IDs->pop());
        remove(cond);
        for (int i=0; i<how_many_deleted; i++)
            insert(changes);
        for (int i=0; i<s.size(); i++)
            empty_IDs->insert(s[i]);
    }

    void select(vector<string> cond, vector<string> names) {
        int search_condition = 0;
        int n;
        int i = num_of_columns;
        for (int j = 0; j < num_of_columns - 1; j++) {
            if (cond[0] == column_names[j])
            {
                search_condition = 0;
                if (column_types[j] == "int")
                    n = stoi(cond[2]);
                else if (column_types[j] == "string")
                    n = hash_str(cond[2]);
                else if (column_types[j] == "timestamp")
                    n = hash_time(cond[4], cond[3], cond[2]);
                i = j;
                break;
            }
            else if (cond[cond.size() - 1] == column_names[j])
            {
                search_condition = cond.size() - 1;
                if (column_types[j] == "int")
                    n = stoi(cond[0]);
                else if (column_types[j] == "string")
                    n = hash_str(cond[0]);
                else if (column_types[j] == "timestamp")
                    n = hash_time(cond[2], cond[1], cond[0]);
                i = j;
                break;
            }
        }
        i++;
        if (i == num_of_columns) {
            cout << "there is no such column" << endl;
            throw 2;
        }
        vector<Node> result;
        if (cond[1]=="==" || (cond.size()==5 && cond[3]=="==")) //condition is ==
        {
            find1(trees[i]->get_root(), n, result);
        }
        else if (cond[1]==">" || (cond.size()==5 && cond[3]=="<")) //condition is >
        {
            find2(trees[i]->get_root(), n, result);
        }
        else if (cond[1]=="<" || (cond.size()==5 && cond[3]==">")) //condition is <
        {
            find3(trees[i]->get_root(), n, result);
        }
        // sorting by ID
        int d=0;
        for (int p=0; p<result.size(); p++)
        {
            d=i;
            while(d!=0)
            {
                result[p]=*result[p].nextField;
                d=(d+1)%num_of_columns;
            }
        }
        sort(result, 0, result.size()-1);
        // end of sorting
        for (int w=0; w<result.size(); w++)
            print(&result[w], names);
    }
    string get_name()
    {
        return table_name;
    }
    int get_num_of_columns()
    {
        return num_of_columns;
    }
private:
    int how_many_deleted; // for inserting after delete
    string table_name;
    B_tree** trees;
    vector<string> column_names;
    vector<string> column_types;
    int num_of_columns;
    int size;
    int biggest_used_ID;
    heap<int>* empty_IDs;
    int part(vector<Node>& arr, int l, int r)
    {
        int pivot = arr[r].data;
        int i =l - 1;

        for (int j = l; j < r; j++)
        {
            if (arr[j].data <= pivot)
            {
                i++;
                Node x=arr[i];
                arr[i]=arr[j];
                arr[j]=x;
            }
        }
        Node x=arr[r];
        arr[r]=arr[i+1];
        arr[i+1]=x;
        return i + 1;
    }
    void sort(vector<Node> &arr, int l, int r) //Quick sort
    {
        if (l < r)
        {
            int par = part(arr, l, r);

            sort(arr, l, par - 1);
            sort(arr, par + 1, r);
        }
    }
    void print(Node* ptr, vector<string> chosen_columns)
    {
        for (int i=0; i<num_of_columns; i++)
            ptr=ptr->nextField;
        if (chosen_columns.size()==num_of_columns)
        {
            cout << ptr->data << " ";
            ptr=ptr->nextField;
            for (int j=0; j<num_of_columns-1; j++)
            {
                if (column_types[j] == "int")
                {
                    cout << ptr->data << " ";
                }
                else if (column_types[j] == "string")
                    cout << rev_hash_str(ptr->data) << " ";
                else if (column_types[j] == "timestamp")
                    cout << rev_hash_time(ptr->data) << " ";
                ptr=ptr->nextField;
            }
            cout << endl;
        }
        else
        {
            ptr=ptr->nextField;
            int s=0;
            int j=0;
            while (true)
            {
                if (s>=chosen_columns.size())
                    break;
                if (column_names[j%(num_of_columns-1)]==chosen_columns[s])
                {
                    s++;
                    if (column_types[j%(num_of_columns-1)] == "int")
                    {
                        cout << ptr->data << " ";
                    }
                    else if (column_types[j%(num_of_columns-1)] == "string")
                        cout << rev_hash_str(ptr->data) << " ";
                    else if (column_types[j%(num_of_columns-1)] == "timestamp")
                        cout << rev_hash_time(ptr->data) << " ";
                }
                ptr=ptr->nextField;
                j++;
            }
            cout << endl;
        }
    }
    void right_travel1(BTNode* P, int v, vector<Node> &res)
    {
        if (!P)
            return;
        int i=0;
        while(i<P->num_of_keys)
        {
            if (!P->is_leaf)
                right_travel1(P->childes[i], v, res);
            if (P->keys[i].data!=v)
                return;
            res.push_back(P->keys[i]);
            i++;
        }
        if (!P->is_leaf)
            right_travel1(P->childes[P->num_of_keys], v, res);
    }
    void left_travel1(BTNode* P, int v, vector<Node> &res)
    {
        if (!P)
            return;
        int i=P->num_of_keys-1;
        while(i>=0)
        {
            if (!P->is_leaf)
                left_travel1(P->childes[i+1], v, res);
            if (P->keys[i].data!=v)
                return;
            res.push_back(P->keys[i]);
            i--;
        }
        if (!P->is_leaf)
            left_travel1(P->childes[0], v, res);
    }
    void find1(BTNode* P, int v, vector<Node> &res)
    {
        if (!P)
            return;
        int i=0;
        while (i<P->num_of_keys && P->keys[i].data < v)
            i++;
        if (P->keys[i].data==v)
        {
            if (!P->is_leaf)
                left_travel1(P->childes[i], v, res);
            while (i<P->num_of_keys && P->keys[i].data == v)
            {
                res.push_back(P->keys[i]);
                right_travel1(P->childes[i+1], v, res);
                i++;
            }
        }
        else
            if (!P->is_leaf)
                find1(P->childes[i], v, res);
    }
    void find2(BTNode* P, int v, vector<Node> &res) // >
    {
        if (!P)
            return;
        for (int j=P->num_of_keys-1; j>-1; j--)
        {
            if (!P->is_leaf)
                find2(P->childes[j+1], v, res);
            if (P->keys[j].data <= v)
                return;
            res.push_back(P->keys[j]);
        }
        if (!P->is_leaf)
            find2(P->childes[0], v, res);
    }

    void find3(BTNode* P, int v, vector<Node> &res) // <
    {
        if (!P)
            return;
        for (int j=0; j<P->num_of_keys; j++)
        {
            if (!P->is_leaf)
                find3(P->childes[j], v, res);
            if (P->keys[j].data >= v)
                return;
            res.push_back(P->keys[j]);
        }
        if (!P->is_leaf)
            find3(P->childes[P->num_of_keys], v, res);
    }
    long long hash_str(string str)
    {
        long long res=0;
        for (int i=0; i<str.size(); i++)
        {
            res+=(int(str[i])-48)*pow(10, 2*i);
        }
        return res;
    }
    string rev_hash_str(long long n)
    {
        string res="";
        int b=0;
        int i=0;
        while(n>0)
        {
            b=n%100;
            while(b>0)
            {
                res+=char(b%100+48);
                b/=100;
            }
            n=n/100;
            i++;
        }
        return res;
    }
    long long hash_time(string day, string month, string year)
    {
        return stoi(day) + stoi(month)*100 + stoi(year)*10000;
    }
    string rev_hash_time(long long n)
    {
        string res="";
        int b=0;
        for (int i=0; i<3; i++)
        {
            b=n%(i!=2 ? 100 : 10000);
            while(b>0)
            {
                res=char(b%10+48)+res;
                b/=10;
            }
            n=n/100;
            if (i!=2)
                res='/'+res;
        }
        return res;
    }
};