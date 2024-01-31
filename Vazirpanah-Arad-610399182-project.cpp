//#include <vector>
//#include <string>
//#include <iostream>
//#include <cmath>
//
//using namespace std;
//
//class B_tree;
//class BTNode;
//
//class Node{
//public:
//    long long data;
//    Node* nextField;
//    BTNode* self;
//};
//
//class BTNode
//{
//    friend class B_tree;
//public:
//    BTNode(int m, int leaf)
//    {
//        t=m;
//        is_leaf=leaf;
//        childes= new BTNode* [2*t];
//        keys= new Node [2*t-1];
//        num_of_keys=0;
//    }
//    void split(int i, BTNode* Ptr1)
//    {
//        BTNode* Ptr2= new BTNode(Ptr1->t, Ptr1->is_leaf);
//        Ptr2->num_of_keys=t-1;
//
//        for (int p=0; p<t-1; p++)
//        {
//            Ptr2->keys[p]=Ptr1->keys[p+t];
//            Ptr2->keys[p].self=Ptr2;
//        }
//
//        if (!Ptr1->is_leaf)
//        {
//            for (int p=0; p<t; p++)
//            {
//                Ptr2->childes[p]=Ptr1->childes[p+t];
//            }
//        }
//
//        Ptr1->num_of_keys=t-1;
//        Node* arr1=new Node[2*t-1];
//        BTNode** arr2=new BTNode*[t*2];
//        for (int f=0; f<=t-1; f++)
//        {
//            arr1[f]=Ptr1->keys[f];
//        }
//        if (!Ptr1->is_leaf)
//        {
//            for (int p=0; p<t; p++)
//            {
//                arr2[p]=Ptr1->childes[p];
//            }
//            Ptr1->childes=arr2;
//        }
//        Ptr1->keys=arr1;
//        for (int p=num_of_keys; p>=i+1; p--)
//            childes[p+1]=childes[p];
//
//        childes[i+1]=Ptr2;
//
//        for (int p=num_of_keys-1; p>=i; p--)
//            keys[p+1]=keys[p];
//
//        keys[i]=Ptr1->keys[t-1];
//
//        num_of_keys+=1;
//    }
//    Node* simple_insert(long long value, Node* ptr)
//    {
//        int i=num_of_keys-1;
//
//        if (is_leaf)
//        {
//            Node* arr=new Node[2*t-1];
//            while ( i>=0 && keys[i].data > value)
//            {
//                arr[i+1]=keys[i];
//                i-=1;
//            }
//            for (int f=0; f<=i; f++)
//            {
//                arr[f] = keys[f];
//            }
//            arr[i+1].data = value;
//            arr[i+1].self=this;
//            arr[i+1].nextField=ptr;
//            keys=arr;
//            num_of_keys+=1;
//            return &keys[i+1];
//        }
//        else
//        {
//            while (i>=0 && keys[i].data > value)
//                i-=1;
//            if (childes[i+1]->num_of_keys == 2*t-1)
//            {
//                split(i+1, childes[i+1]);
//                if (keys[i+1].data < value)
//                    i+=1;
//            }
//            return childes[i+1]->simple_insert(value, ptr);
//        }
//    }
//    Node* predecessor(int index)
//    {
//        BTNode* current=childes[index];
//        while (!current->is_leaf)
//        {
//            current=current->childes[current->num_of_keys];
//        }
//
//        return &current->keys[current->num_of_keys-1];
//    }
//    Node* successor(int index)
//    {
//        if (is_leaf)
//            return &keys[index+1];
//        BTNode* current=childes[index+1];
//        while (!current->is_leaf)
//        {
//            current=current->childes[0];
//        }
//        return &current->keys[0];
//    }
//    void merge(int index)
//    {
//        if (is_leaf)
//            return;
//        if (index<0)
//            return;
//        BTNode* curr=childes[index];
//        BTNode* sib=childes[index+1];
//
//        Node* arr1=new Node [2*t-1];
//        for (int i=0; i<t-1; i++)
//            arr1[i]=curr->keys[i];
//
//        arr1[t-1]=keys[index];
//
//        for (int i=0; i<sib->num_of_keys; i++)
//            arr1[t+i]=sib->keys[i];
//
//        curr->keys=arr1;
//        if (!curr->is_leaf)
//        {
//            BTNode** arr2=new BTNode* [2*t];
//            for (int i=0; i<t; i++)
//                arr2[i]=curr->childes[i];
//            for (int i=0; i<sib->num_of_keys+1; i++)
//                arr2[t+i]=sib->childes[i];
//            curr->childes=arr2;
//        }
//
//        Node* arr3=new Node [2*t-1];
//        for (int i=0; i<index; i++)
//            arr3[i]=keys[i];
//        for (int i=index+1; i<num_of_keys; i++)
//            arr3[i-1]=keys[i];
//        keys=arr3;
//
//        BTNode** arr4=new BTNode* [2*t];
//        for (int i=0; i<index+1; i++)
//            arr4[i]=childes[i];
//        for (int i=index+2; i<num_of_keys+1; i++)
//            arr4[i-1]=childes[i];
//
//        childes=arr4;
//
//        curr->num_of_keys=curr->num_of_keys+sib->num_of_keys+1;
//        num_of_keys-=1;
//
//        delete sib;
//    }
//
//    void borrow_right(int index)
//    {
//        if (is_leaf)
//            return;
//        if (index<0)
//            return;
//        BTNode* curr=childes[index];
//        BTNode* right=childes[index+1];
//
//        Node* arr1=new Node [2*t-1];
//        for (int i=0; i<curr->num_of_keys; i++)
//            arr1[i]=curr->keys[i];
//        arr1[curr->num_of_keys]=keys[index];
//
//        curr->keys=arr1;
//
//        if (!curr->is_leaf)
//        {
//            BTNode** arr2=new BTNode* [2*t];
//            for (int i=0; i<=curr->num_of_keys; i++)
//                arr2[i]=curr->childes[i];
//            arr2[curr->num_of_keys+1]=right->childes[0];
//
//            curr->childes=arr2;
//        }
//
//        Node* arr3=new Node [2*t-1];
//
//        for (int i=0; i<index; i++)
//            arr3[i]=keys[i];
//        arr3[index]=right->keys[0];
//        for (int i=index+1; i<num_of_keys; i++)
//            arr3[i]=keys[i];
//
//        keys=arr3;
//
//        Node* arr4=new Node [2*t-1];
//
//        for (int i=1; i<right->num_of_keys; i++)
//            arr4[i-1]=right->keys[i];
//
//        right->keys=arr4;
//
//        if (!right->is_leaf)
//        {
//            BTNode** arr5=new BTNode* [2*t];
//            for (int i=1; i<right->num_of_keys+1; i+=1)
//                arr5[i-1]=right->childes[i];
//            right->childes=arr5;
//        }
//        curr->num_of_keys++;
//        right->num_of_keys--;
//    }
//
//    void borrow_left(int index)
//    {
//        if (is_leaf)
//            return;
//        if (index<0)
//            return;
//        BTNode* curr=childes[index];
//        BTNode* left=childes[index-1];
//
//        Node* arr1=new Node [2*t-1];
//        for ( int i=curr->num_of_keys-1; i>-1; i-=1)
//            arr1[i+1]=curr->keys[i];
//
//        BTNode** arr2=new BTNode* [2*t];
//        if (!curr->is_leaf)
//        {
//            for (int i=curr->num_of_keys; i>-1; i-=1)
//                arr2[i+1]=curr->childes[i];
//        }
//
//        arr1[0]=keys[index-1];
//        curr->keys=arr1;
//        if (!curr->is_leaf)
//        {
//            arr2[0] = left->childes[left->num_of_keys];
//            curr->childes=arr2;
//        }
//
//        Node* arr3=new Node [2*t-1];
//        for (int i=0; i<index-1; i++)
//            arr3[i]=keys[i];
//        arr3[index-1]=left->keys[left->num_of_keys-1];
//        for (int i=index; i<num_of_keys; i++)
//            arr3[i]=keys[i];
//        keys=arr3;
//
//        Node* arr4=new Node [2*t-1];
//        BTNode** arr5=new BTNode* [2*t];
//        for (int i=0; i<num_of_keys-1; i++)
//        {
//            arr4[i]=left->keys[i];
//            arr5[i]=left->childes[i];
//        }
//        arr5[num_of_keys-1]=left->childes[num_of_keys-1];
//        left->keys=arr4;
//        left->childes=arr5;
//        curr->num_of_keys++;
//        left->num_of_keys--;
//    }
//
//    void fill_up(int index) //in case the BTNode does not have enough keys to be deleted
//    {
//        if (index!=num_of_keys && childes[index+1]->num_of_keys >= t)
//        {
//            borrow_right(index);
//        }
//        else if (index && childes[index-1]->num_of_keys >= t)
//        {
//            borrow_left(index);
//        }
//        else
//        {
//            if (index!=num_of_keys)
//            {
//                merge(index);
//            }
//            else
//            {
//                merge(index-1);
//            }
//        }
//    }
//    void del_leaf(int index)
//    {
//        Node* arr1=new Node [2*t-1];
//        for (int i=0; i<index+1; i++)
//            arr1[i]=keys[i];
//        for (int i=index+1; i<num_of_keys; i++)
//            arr1[i-1]=keys[i];
//        keys=arr1;
//        num_of_keys-=1;
//    }
//
//    void del_non_leaf(int index)
//    {
//        int val=keys[index].data;
//
//        if (childes[index]->num_of_keys >=t)
//        {
//            Node p=*predecessor(index);
//            keys[index]=p;
//            childes[index]->del(p.data);
//        }
//        else if (childes[index+1]->num_of_keys >=t)
//        {
//            Node s=*successor(index);
//            keys[index]=s;
//            childes[index+1]->del(s.data);
//        }
//        else
//        {
//            merge(index);
//            childes[index]->del(val);
//        }
//
//    }
//    void del(int value)
//    {
//        int index=0;
//        while ( index < num_of_keys && keys[index].data < value)
//            index+=1;
//        if (index < num_of_keys && keys[index].data==value)
//        {
//            if (!is_leaf)
//                del_non_leaf(index);
//            else
//                del_leaf(index);
//        }
//
//        else
//        {
//            if (is_leaf)
//            {
//                cout << "the key does not exist to be deleted";
//                return;
//            }
//
//            int is_equal= index==num_of_keys ? 1 : 0;
//
//            if (childes[index]->num_of_keys < t) //might change the index value
//                fill_up(index);
//
//            if (is_equal && index > num_of_keys)
//                childes[index-1]->del(value);
//            else
//                childes[index]->del(value);
//        }
//    }
//
//    Node* search(long long value) {
//        int i = 0;
//        while (i < num_of_keys && value > keys[i].data)
//            i++;
//
//        if (keys[i].data == value)
//            return &keys[i];
//
//        if (is_leaf)
//            return nullptr;
//
//        return childes[i]->search(value);
//    }
//    Node* keys;
//    int t; //minimum degree
//    BTNode** childes;
//    int num_of_keys;
//    int is_leaf;
//};
//
//class B_tree
//{
//public:
//    B_tree(int m)
//    {
//        t=m;
//        rootPtr= nullptr;
//    }
//    Node* insert(long long value, Node* ptr)
//    {
//        if (rootPtr== nullptr)
//        {
//            rootPtr=creat_Node(1);
//            rootPtr->keys[0].data=value;
//            rootPtr->num_of_keys+=1;
//            rootPtr->keys[0].self=rootPtr;
//            rootPtr->keys[0].nextField=ptr;
//            return &rootPtr->keys[0];
//        }
//        else
//        {
//            if (rootPtr->num_of_keys == 2*t-1)
//            {
//                BTNode* new_root= creat_Node(0);
//                new_root->childes[0]=rootPtr;
//
//                new_root->split(0, rootPtr);
//                new_root->keys[0].self=new_root;
//
//                int p=0;
//                if (new_root->keys[0].data <= value)
//                    p++;
//
//                Node* A= new_root->childes[p]->simple_insert(value, ptr);
//
//                rootPtr=new_root;
//                return A;
//            }
//
//            else
//            {
//                return rootPtr->simple_insert(value, ptr);
//            }
//        }
//    }
//    void del(int value)
//    {
//        if (!rootPtr)
//        {
//            cout << "there is nothing to delete!";
//            return;
//        }
//        else
//            rootPtr->del(value);
//    }
//    void travel()
//    {
//        if (rootPtr)
//            travel(rootPtr);
//    }
//    void travel2()
//    {
//        if (rootPtr)
//            travel2(rootPtr);
//    }
//
//    Node* search(long long value)
//    {
//        return rootPtr->search(value);
//    }
//    BTNode* get_root()
//    {
//        return rootPtr;
//    }
//private:
//    BTNode* rootPtr;
//    int t; //minimum degree
//    BTNode* creat_Node(int a)
//    {
//        return new BTNode(t, a);
//    }
//    void travel(BTNode* ptr)
//    {
//        int i=0;
//        for (i=0; i<ptr->num_of_keys; i++)
//        {
//            if (!ptr->is_leaf)
//                travel(ptr->childes[i]);
//            cout << ptr->keys[i].data << " ";
//        }
//
//        if (!ptr->is_leaf)
//            travel(ptr->childes[i]);
//    }
//    void travel2(BTNode* ptr)
//    {
//        if (ptr)
//        {
//            for (int i=0; i<ptr->num_of_keys; i++)
//                cout << ptr->keys[i].data << " ";
//            cout << "*";
//            if (!ptr->is_leaf)
//                for (int i=0; i<ptr->num_of_keys+1; i++)
//                    travel2(ptr->childes[i]);
//        }
//    }
//};
//
////---------------------------------------------------------heap-----------------------------------------------
//template <class type> class heap
//{
//public:
//    heap(int n)
//    {
//        size=n;
//        last_index=-1;
//        arr=new type [size];
//        for (int i=0; i<n; i++)
//        {
//            arr[i]=-1;
//        }
//    }
//    void insert(type data)
//    {
//        if (last_index==-1)
//        {
//            arr[0]=data;
//            last_index=0;
//            return;
//        }
//        else
//        {
//            last_index+=1;
//            arr[last_index]=data;
//            heapify_up(last_index);
//            return;
//        }
//    }
//    int top()
//    {
//        return arr[0];
//    }
//    int pop()
//    {
//        int t;
//        t=arr[0];
//        arr[0]=arr[last_index];
//        last_index-=1;
//        heapify_down(0);
//        return t;
//    }
//    bool is_empty()
//    {
//        return last_index==-1;
//    }
//    int count()
//    {
//        return last_index+1;
//    }
//private:
//    type* arr;
//    int size;
//    int last_index;
//    void heapify_up(int index)
//    {
//        int lst=index;
//        while(index && arr[index]<arr[parent(index)])
//        {
//            lst=index;
//            swap(index, parent(index));
//            index=parent(index);
//        }
//        while (index && arr[index]==arr[parent(index)])
//        {
//            lst=index;
//            swap(index, parent(index));
//            index=parent(index);
//        }
//        if ( lst && lst==left_child(parent(lst)))
//        {
//            if (lst+1<last_index && arr[lst]==arr[lst+1])
//                swap(lst, lst+1);
//            else if (lst+1< last_index && arr[lst] > arr[lst+1])
//                swap(lst, lst+1);
//        }
//        else if (lst && lst==right_child(parent(lst)))
//        {
//            if (arr[lst]==arr[lst-1])
//                swap(lst, lst-1);
//            else if (arr[lst] < arr[lst-1])
//                swap(lst, lst-1);
//        }
//    }
//    void heapify_down(int index)
//    {
//        int left=left_child(index);
//        int right=right_child(index);
//        int smallest=index;
//        if (left<last_index+1 && arr[left]<arr[index])
//            smallest=left;
//        if (right<last_index+1 && arr[right]<arr[smallest])
//            smallest=right;
//        if (smallest==index && right<last_index+1 && arr[right]==arr[left])
//        {
//            swap(right, left);
//        }
//        if(smallest!=index)
//        {
//            swap(index, smallest);
//            heapify_down(smallest);
//        }
//    }
//    int parent(int index)
//    {
//        index+=1;
//        return index/2-1;
//    }
//    int left_child(int index)
//    {
//        index+=1;
//        return 2*index-1;
//    }
//    int right_child(int index)
//    {
//        index+=1;
//        return 2*index;
//    }
//    void swap(int i, int j)
//    {
//        type t1;
//        int t2;
//        t1=arr[i];
//        arr[i]=arr[j];
//        arr[j]=t1;
//    }
//};
//
//class Table
//{
//    friend class B_tree;
//public:
//    Table(string name, vector<string> names, vector<string> types)
//    {
//        table_name=name;
//        for (int i=0; i<names.size(); i++)
//            column_names.push_back(names[i]);
//        num_of_columns=column_names.size()+1;
//        for (int i=0; i<types.size(); i++)
//            column_types.push_back(types[i]);
//        trees=new B_tree*[num_of_columns];
//        for (int i=0; i<num_of_columns; i++)
//            trees[i]=new B_tree(2);
//        size=0;
//        biggest_used_ID=0;
//        empty_IDs=new heap<int>(100000);
//    }
//
//    void insert(vector<string> arr)
//    {
//        Node* prev= nullptr;
//        Node* last= nullptr;
//        int j=arr.size()-1;
//        for (int i=num_of_columns-1; i>=1; i--)
//        {
//            if (column_types[i-1]=="int")
//            {
//                prev= trees[i]->insert(stoi(arr[j]), prev);
//                j--;
//            }
//            else if (column_types[i-1]=="string")
//            {
//                prev= trees[i]->insert(hash_str(arr[j]), prev);
//                j--;
//            }
//            else if (column_types[i-1]=="timestamp")
//            {
//                prev= trees[i]->insert(hash_time(arr[j], arr[j-1], arr[j-2]), prev);
//                j-=3;
//            }
//            if (i==num_of_columns-1)
//                last=prev;
//        }
//        if (empty_IDs->is_empty())
//            prev= trees[0]->insert(++biggest_used_ID, prev);
//        else
//        {
//            prev=trees[0]->insert(empty_IDs->pop(), prev);
//        }
//        last->nextField=prev;
//        size++;
//    }
//
//    void remove(vector<string> cond)
//    {
//        how_many_deleted=0;
//        int search_condition = 0;
//        int n;
//        int i = num_of_columns;
//        for (int j = 0; j < num_of_columns - 1; j++) {
//            if (cond[0] == column_names[j])
//            {
//                search_condition = 0;
//                if (column_types[j] == "int")
//                    n = stoi(cond[2]);
//                else if (column_types[j] == "string")
//                    n = hash_str(cond[2]);
//                else if (column_types[j] == "timestamp")
//                    n = hash_time(cond[4], cond[3], cond[2]);
//                i = j;
//                break;
//            }
//            else if (cond[cond.size() - 1] == column_names[j])
//            {
//                search_condition = cond.size() - 1;
//                if (column_types[j] == "int")
//                    n = stoi(cond[0]);
//                else if (column_types[j] == "string")
//                    n = hash_str(cond[0]);
//                else if (column_types[j] == "timestamp")
//                    n = hash_time(cond[2], cond[1], cond[0]);
//                i = j;
//                break;
//            }
//        }
//        i++;
//        if (i == num_of_columns) {
//            cout << "there is no such column" << endl;
//            throw 2;
//        }
//        vector<Node> result;
//        if (cond[1]=="==" || (cond.size()==5 && cond[3]=="==")) //condition is ==
//        {
//            find1(trees[i]->get_root(), n, result);
//        }
//        else if (cond[1]==">" || (cond.size()==5 && cond[3]=="<")) //condition is >
//        {
//            find2(trees[i]->get_root(), n, result);
//        }
//        else if (cond[1]=="<" || (cond.size()==5 && cond[3]==">")) //condition is <
//        {
//            find3(trees[i]->get_root(), n, result);
//        }
//        how_many_deleted=result.size();
//        for (int p=0; p<result.size(); p++)
//        {
//            Node temp;
//            Node temp2;
//            Node temp4;
//            temp=result[p];
//            for (int q=0; q<num_of_columns; q++)
//            {
//                temp4=*temp.nextField;
//                temp2=*trees[(i+q)%num_of_columns]->search(temp.data);
//                if (&temp2!= nullptr && &temp2!=&temp)
//                {
//                    Node t=temp;
//                    temp.nextField=temp2.nextField;
//                    temp2.nextField=&t;
//                    Node A=temp;
//                    Node B=temp2;
//                    for (int d=0; d<num_of_columns-1; d++)
//                    {
//                        A=*A.nextField;
//                        B=*B.nextField;
//                    }
//                    A.nextField=&temp2;
//                    B.nextField=&temp;
//                }
//                if ((i+q)%num_of_columns==0)
//                {
//                    empty_IDs->insert(temp2.data);
//                }
//                trees[(i+q)%num_of_columns]->del(temp2.data);
//                temp=temp4;
//            }
//        }
//    }
//
//    void update(vector<string> changes, vector<string> cond)
//    {
//        vector<int> s;
//        while (!empty_IDs->is_empty())
//            s.push_back(empty_IDs->pop());
//        remove(cond);
//        for (int i=0; i<how_many_deleted; i++)
//            insert(changes);
//        for (int i=0; i<s.size(); i++)
//            empty_IDs->insert(s[i]);
//    }
//
//    void select(vector<string> cond, vector<string> names) {
//        int search_condition = 0;
//        int n;
//        int i = num_of_columns;
//        for (int j = 0; j < num_of_columns - 1; j++) {
//            if (cond[0] == column_names[j])
//            {
//                search_condition = 0;
//                if (column_types[j] == "int")
//                    n = stoi(cond[2]);
//                else if (column_types[j] == "string")
//                    n = hash_str(cond[2]);
//                else if (column_types[j] == "timestamp")
//                    n = hash_time(cond[4], cond[3], cond[2]);
//                i = j;
//                break;
//            }
//            else if (cond[cond.size() - 1] == column_names[j])
//            {
//                search_condition = cond.size() - 1;
//                if (column_types[j] == "int")
//                    n = stoi(cond[0]);
//                else if (column_types[j] == "string")
//                    n = hash_str(cond[0]);
//                else if (column_types[j] == "timestamp")
//                    n = hash_time(cond[2], cond[1], cond[0]);
//                i = j;
//                break;
//            }
//        }
//        i++;
//        if (i == num_of_columns) {
//            cout << "there is no such column" << endl;
//            throw 2;
//        }
//        vector<Node> result;
//        if (cond[1]=="==" || (cond.size()==5 && cond[3]=="==")) //condition is ==
//        {
//            find1(trees[i]->get_root(), n, result);
//        }
//        else if (cond[1]==">" || (cond.size()==5 && cond[3]=="<")) //condition is >
//        {
//            find2(trees[i]->get_root(), n, result);
//        }
//        else if (cond[1]=="<" || (cond.size()==5 && cond[3]==">")) //condition is <
//        {
//            find3(trees[i]->get_root(), n, result);
//        }
//        // sorting by ID
//        int d=0;
//        for (int p=0; p<result.size(); p++)
//        {
//            d=i;
//            while(d!=0)
//            {
//                result[p]=*result[p].nextField;
//                d=(d+1)%num_of_columns;
//            }
//        }
//        sort(result, 0, result.size()-1);
//        // end of sorting
//        for (int w=0; w<result.size(); w++)
//            print(&result[w], names);
//    }
//    string get_name()
//    {
//        return table_name;
//    }
//    int get_num_of_columns()
//    {
//        return num_of_columns;
//    }
//private:
//    int how_many_deleted; // for inserting after delete
//    string table_name;
//    B_tree** trees;
//    vector<string> column_names;
//    vector<string> column_types;
//    int num_of_columns;
//    int size;
//    int biggest_used_ID;
//    heap<int>* empty_IDs;
//    int part(vector<Node>& arr, int l, int r)
//    {
//        int pivot = arr[r].data;
//        int i =l - 1;
//
//        for (int j = l; j < r; j++)
//        {
//            if (arr[j].data <= pivot)
//            {
//                i++;
//                Node x=arr[i];
//                arr[i]=arr[j];
//                arr[j]=x;
//            }
//        }
//        Node x=arr[r];
//        arr[r]=arr[i+1];
//        arr[i+1]=x;
//        return i + 1;
//    }
//    void sort(vector<Node> &arr, int l, int r) //Quick sort
//    {
//        if (l < r)
//        {
//            int par = part(arr, l, r);
//
//            sort(arr, l, par - 1);
//            sort(arr, par + 1, r);
//        }
//    }
//    void print(Node* ptr, vector<string> chosen_columns)
//    {
//        for (int i=0; i<num_of_columns; i++)
//            ptr=ptr->nextField;
//        if (chosen_columns.size()==num_of_columns)
//        {
//            cout << ptr->data << " ";
//            ptr=ptr->nextField;
//            for (int j=0; j<num_of_columns-1; j++)
//            {
//                if (column_types[j] == "int")
//                {
//                    cout << ptr->data << " ";
//                }
//                else if (column_types[j] == "string")
//                    cout << rev_hash_str(ptr->data) << " ";
//                else if (column_types[j] == "timestamp")
//                    cout << rev_hash_time(ptr->data) << " ";
//                ptr=ptr->nextField;
//            }
//            cout << endl;
//        }
//        else
//        {
//            ptr=ptr->nextField;
//            int s=0;
//            int j=0;
//            while (true)
//            {
//                if (s>=chosen_columns.size())
//                    break;
//                if (column_names[j%(num_of_columns-1)]==chosen_columns[s])
//                {
//                    s++;
//                    if (column_types[j%(num_of_columns-1)] == "int")
//                    {
//                        cout << ptr->data << " ";
//                    }
//                    else if (column_types[j%(num_of_columns-1)] == "string")
//                        cout << rev_hash_str(ptr->data) << " ";
//                    else if (column_types[j%(num_of_columns-1)] == "timestamp")
//                        cout << rev_hash_time(ptr->data) << " ";
//                }
//                ptr=ptr->nextField;
//                j++;
//            }
//            cout << endl;
//        }
//    }
//    void right_travel1(BTNode* P, int v, vector<Node> &res)
//    {
//        if (!P)
//            return;
//        int i=0;
//        while(i<P->num_of_keys)
//        {
//            if (!P->is_leaf)
//                right_travel1(P->childes[i], v, res);
//            if (P->keys[i].data!=v)
//                return;
//            res.push_back(P->keys[i]);
//            i++;
//        }
//        if (!P->is_leaf)
//            right_travel1(P->childes[P->num_of_keys], v, res);
//    }
//    void left_travel1(BTNode* P, int v, vector<Node> &res)
//    {
//        if (!P)
//            return;
//        int i=P->num_of_keys-1;
//        while(i>=0)
//        {
//            if (!P->is_leaf)
//                left_travel1(P->childes[i+1], v, res);
//            if (P->keys[i].data!=v)
//                return;
//            res.push_back(P->keys[i]);
//            i--;
//        }
//        if (!P->is_leaf)
//            left_travel1(P->childes[0], v, res);
//    }
//    void find1(BTNode* P, int v, vector<Node> &res)
//    {
//        if (!P)
//            return;
//        int i=0;
//        while (i<P->num_of_keys && P->keys[i].data < v)
//            i++;
//        if (P->keys[i].data==v)
//        {
//            if (!P->is_leaf)
//                left_travel1(P->childes[i], v, res);
//            while (i<P->num_of_keys && P->keys[i].data == v)
//            {
//                res.push_back(P->keys[i]);
//                right_travel1(P->childes[i+1], v, res);
//                i++;
//            }
//        }
//        else
//        if (!P->is_leaf)
//            find1(P->childes[i], v, res);
//    }
//    void find2(BTNode* P, int v, vector<Node> &res) // >
//    {
//        if (!P)
//            return;
//        for (int j=P->num_of_keys-1; j>-1; j--)
//        {
//            if (!P->is_leaf)
//                find2(P->childes[j+1], v, res);
//            if (P->keys[j].data <= v)
//                return;
//            res.push_back(P->keys[j]);
//        }
//        if (!P->is_leaf)
//            find2(P->childes[0], v, res);
//    }
//
//    void find3(BTNode* P, int v, vector<Node> &res) // <
//    {
//        if (!P)
//            return;
//        for (int j=0; j<P->num_of_keys; j++)
//        {
//            if (!P->is_leaf)
//                find3(P->childes[j], v, res);
//            if (P->keys[j].data >= v)
//                return;
//            res.push_back(P->keys[j]);
//        }
//        if (!P->is_leaf)
//            find3(P->childes[P->num_of_keys], v, res);
//    }
//    long long hash_str(string str)
//    {
//        long long res=0;
//        for (int i=0; i<str.size(); i++)
//        {
//            res+=(int(str[i])-48)*pow(10, 2*i);
//        }
//        return res;
//    }
//    string rev_hash_str(long long n)
//    {
//        string res="";
//        int b=0;
//        int i=0;
//        while(n>0)
//        {
//            b=n%100;
//            while(b>0)
//            {
//                res+=char(b%100+48);
//                b/=100;
//            }
//            n=n/100;
//            i++;
//        }
//        return res;
//    }
//    long long hash_time(string day, string month, string year)
//    {
//        return stoi(day) + stoi(month)*100 + stoi(year)*10000;
//    }
//    string rev_hash_time(long long n)
//    {
//        string res="";
//        int b=0;
//        for (int i=0; i<3; i++)
//        {
//            b=n%(i!=2 ? 100 : 10000);
//            while(b>0)
//            {
//                res=char(b%10+48)+res;
//                b/=10;
//            }
//            n=n/100;
//            if (i!=2)
//                res='/'+res;
//        }
//        return res;
//    }
//};
//
//vector<string> split(string str)
//{
//    vector<string> res;
//    string x="";
//    for (int i=0; i<str.size(); i++)
//    {
//        if ((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z') || (str[i]>='0' && str[i]<='9'))
//        {
//            if ((str[i-1]>='a' && str[i-1]<='z') || (str[i-1]>='A' && str[i-1]<='Z') || (str[i-1]>='0' && str[i-1]<='9'))
//                x+=str[i];
//            else
//            {
//                if (!x.size())
//                    x+=str[i];
//                else
//                {
//                    res.push_back(x);
//                    x="";
//                }
//            }
//        }
//        else if (str[i]==')' || str[i]=='(' || str[i]=='>' || str[i]=='<')
//        {
//            if (x.size())
//            {
//                res.push_back(x);
//                x="";
//                res.push_back(string(1, str[i]));
//            }
//            else
//                res.push_back(string(1, str[i]));
//        }
//        else if ( str[i] == '=' && str[i-1] == '=' )
//        {
//            res.push_back("==");
//        }
//        else if (str[i]=='*')
//        {
//            if (x.size())
//            {
//                res.push_back(x);
//                x="";
//            }
//            res.push_back(string(1, str[i]));
//        }
//        else
//        {
//            if (x.size())
//            {
//                res.push_back(x);
//                x="";
//            }
//        }
//    }
//    if (x!="")
//    {
//        res.push_back(x);
//    }
//    return res;
//}
//
//int main() {
//    vector<Table> tables;
//    int n;
//    cin >> n;
//    if (cin.fail())
//        cout << "Invalid input!" << endl;
//    cin.ignore();
//    for (int i=0; i<n; i++)
//    {
//        string input;
//        getline(cin, input);
//
//        vector<string> res=split(input);
//
//        if (res[0]=="CREATE")
//        {
//            if (res[1]!="TABLE")
//            {
//                cout << "you have to enter 'table' after 'creat'1"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            if (res[3]!="(")
//            {
//                cout << "you have to enter '(' after table name"
//                     << endl << "try again: ";;
//                i-=1;
//                continue;
//            }
//            vector<string> column_names;
//            vector<string> types;
//            for (int j=4; res[j]!=")"; j+=2)
//            {
//                column_names.push_back(res[j]);
//                types.push_back(res[j+1]);
//            }
//            Table t(res[2], column_names, types);  //res[2]=tree name
//            tables.push_back(t);
//        }
//        else if (res[0]=="INSERT")
//        {
//            if (res[1]!="INTO")
//            {
//                cout <<"Invalid input! you have to insert 'INTO' after 'Insert'"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            int j=0;
//            int s=0;
//            while (j < tables.size() && tables[j].get_name()!=res[2])
//                j++;
//            if (j>=tables.size())
//            {
//                cout << "there is no such a table"
//                     << endl << "try again:";
//                i-=1;
//                s=1;
//                continue;
//            }
//            if (res[3]!="VALUES")
//            {
//                cout << "you have to put 'VALUES' after table's name"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            if (res[4]!="(")
//            {
//                cout << "you have to put '(' after 'VALUES'"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            vector<string> pass_v;
//            for (int p=5; res[p]!=")"; p++)
//            {
//                pass_v.push_back(res[p]);
//            }
//            tables[j].insert(pass_v);
//        }
//        else if (res[0]=="SELECT")
//        {
//            if (res[1]!="(" && res[1]!="*")
//            {
//                cout << "you have to put '(' or '*' after 'SELECT'"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            vector<string> chosen_columns;
//            int p;
//            if (res[1]=="(")
//            {
//                p=2;
//                while (res[p]!=")")
//                {
//                    chosen_columns.push_back(res[p]);
//                    p++;
//                }
//            }
//            else
//                p=1;
//            if (res[p+1]!="FROM")
//            {
//                cout << "you have to put 'FROM' after columns name"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            p+=2;
//            int j=0; //index of the table we want
//            int s=0;
//            while (j<tables.size() && tables[j].get_name()!=res[p])
//                j++;
//            if (j>=tables.size())
//            {
//                cout << "there is no such a table"
//                     << endl << "try again:";
//                i-=1;
//                s=1;
//                continue;
//            }
//            if (p-2==1)
//            {
//                for (int w=0; w<tables[j].get_num_of_columns(); w++)
//                    chosen_columns.push_back("s");
//            }
//            if (res[p+1]!="WHERE")
//            {
//                cout << "you have to put 'WHERE' after table name"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            p+=2;
//            vector<string> con;
//            for (int q=p; q<res.size(); q++)
//            {
//                con.push_back(res[q]);
//            }
//            tables[j].select(con, chosen_columns);
//        }
//        else if (res[0]=="DELETE")
//        {
//            if (res[1]!="FROM")
//            {
//                cout << "you have to put 'FROM' after 'DELETE"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            int j=0;
//            while (j < tables.size() && tables[j].get_name()!=res[2])
//                j++;
//            if (j>=tables.size())
//            {
//                cout << "there is no such a table"
//                     << endl << "try again:";
//                i-=1;
//                continue;
//            }
//            if (res[3]!="WHERE")
//            {
//                cout << "you have to put 'WHERE' after changes"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            vector<string> con;
//            for (int q=4; q<res.size(); q++)
//            {
//                con.push_back(res[q]);
//            }
//            tables[j].remove(con);
//        }
//        else if (res[0]=="UPDATE")
//        {
//            if (res[2]!="SET")
//            {
//                cout << "you have to put 'SET' after table name"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            int j=0;
//            int s=0;
//            while (tables[j].get_name()!=res[1])
//            {
//                if (j>=tables.size())
//                {
//                    cout << "there is no such a table"
//                         << endl << "try again:";
//                    i-=1;
//                    s=1;
//                    break;
//                }
//                j++;
//            }
//            if (s)
//            {
//                continue;
//            }
//            vector<string> changes;
//            int a=0;
//            while(res[a+4]!=")")
//            {
//                changes.push_back(res[a + 4]);
//                a++;
//            }
//            a+=5;
//            if (res[a]!="WHERE")
//            {
//                cout << "you have to put 'WHERE' after changes"
//                     << endl << "try again: ";
//                i-=1;
//                continue;
//            }
//            vector<string> condition;
//            for (int q=a+1; q<res.size(); q++)
//                condition.push_back(res[q]);
//            tables[j].update(changes, condition);
//        }
//        else
//        {
//            cout << "Invalid input!";
//            i-=1;
//        }
//    }
//    return 0;
//}