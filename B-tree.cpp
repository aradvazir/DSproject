#include <iostream>
using namespace std;

class B_tree;
class BTNode;

class Node{
public:
    long long data;
    Node* nextField;
    BTNode* self;
};

class BTNode
{
    friend class B_tree;
public:
    BTNode(int m, int leaf)
    {
        t=m;
        is_leaf=leaf;
        childes= new BTNode* [2*t];
        keys= new Node [2*t-1];
        num_of_keys=0;
    }
    void split(int i, BTNode* Ptr1)
    {
        BTNode* Ptr2= new BTNode(Ptr1->t, Ptr1->is_leaf);
        Ptr2->num_of_keys=t-1;

        for (int p=0; p<t-1; p++)
        {
            Ptr2->keys[p]=Ptr1->keys[p+t];
            Ptr2->keys[p].self=Ptr2;
        }

        if (!Ptr1->is_leaf)
        {
            for (int p=0; p<t; p++)
            {
                Ptr2->childes[p]=Ptr1->childes[p+t];
            }
        }

        Ptr1->num_of_keys=t-1;
        Node* arr1=new Node[2*t-1];
        BTNode** arr2=new BTNode*[t*2];
        for (int f=0; f<=t-1; f++)
        {
            arr1[f]=Ptr1->keys[f];
        }
        if (!Ptr1->is_leaf)
        {
            for (int p=0; p<t; p++)
            {
                arr2[p]=Ptr1->childes[p];
            }
            Ptr1->childes=arr2;
        }
        Ptr1->keys=arr1;
        for (int p=num_of_keys; p>=i+1; p--)
            childes[p+1]=childes[p];

        childes[i+1]=Ptr2;

        for (int p=num_of_keys-1; p>=i; p--)
            keys[p+1]=keys[p];

        keys[i]=Ptr1->keys[t-1];

        num_of_keys+=1;
    }
    Node* simple_insert(long long value, Node* ptr)
    {
        int i=num_of_keys-1;

        if (is_leaf)
        {
            Node* arr=new Node[2*t-1];
            while ( i>=0 && keys[i].data > value)
            {
                arr[i+1]=keys[i];
                i-=1;
            }
            for (int f=0; f<=i; f++)
            {
                arr[f] = keys[f];
            }
            arr[i+1].data = value;
            arr[i+1].self=this;
            arr[i+1].nextField=ptr;
            keys=arr;
            num_of_keys+=1;
            return &keys[i+1];
        }
        else
        {
            while (i>=0 && keys[i].data > value)
                i-=1;
            if (childes[i+1]->num_of_keys == 2*t-1)
            {
                split(i+1, childes[i+1]);
                if (keys[i+1].data < value)
                    i+=1;
            }
            return childes[i+1]->simple_insert(value, ptr);
        }
    }
    Node* predecessor(int index)
    {
        BTNode* current=childes[index];
        while (!current->is_leaf)
        {
            current=current->childes[current->num_of_keys];
        }

        return &current->keys[current->num_of_keys-1];
    }
    Node* successor(int index)
    {
        if (is_leaf)
            return &keys[index+1];
        BTNode* current=childes[index+1];
        while (!current->is_leaf)
        {
            current=current->childes[0];
        }
        return &current->keys[0];
    }
    void merge(int index)
    {
        if (is_leaf)
            return;
        if (index<0)
            return;
        BTNode* curr=childes[index];
        BTNode* sib=childes[index+1];

        Node* arr1=new Node [2*t-1];
        for (int i=0; i<t-1; i++)
            arr1[i]=curr->keys[i];

        arr1[t-1]=keys[index];

        for (int i=0; i<sib->num_of_keys; i++)
            arr1[t+i]=sib->keys[i];

        curr->keys=arr1;
        if (!curr->is_leaf)
        {
            BTNode** arr2=new BTNode* [2*t];
            for (int i=0; i<t; i++)
                arr2[i]=curr->childes[i];
            for (int i=0; i<sib->num_of_keys+1; i++)
                arr2[t+i]=sib->childes[i];
            curr->childes=arr2;
        }

        Node* arr3=new Node [2*t-1];
        for (int i=0; i<index; i++)
            arr3[i]=keys[i];
        for (int i=index+1; i<num_of_keys; i++)
            arr3[i-1]=keys[i];
        keys=arr3;

        BTNode** arr4=new BTNode* [2*t];
        for (int i=0; i<index+1; i++)
            arr4[i]=childes[i];
        for (int i=index+2; i<num_of_keys+1; i++)
            arr4[i-1]=childes[i];

        childes=arr4;

        curr->num_of_keys=curr->num_of_keys+sib->num_of_keys+1;
        num_of_keys-=1;

        delete sib;
    }

    void borrow_right(int index)
    {
        if (is_leaf)
            return;
        if (index<0)
            return;
        BTNode* curr=childes[index];
        BTNode* right=childes[index+1];

        Node* arr1=new Node [2*t-1];
        for (int i=0; i<curr->num_of_keys; i++)
            arr1[i]=curr->keys[i];
        arr1[curr->num_of_keys]=keys[index];

        curr->keys=arr1;

        if (!curr->is_leaf)
        {
            BTNode** arr2=new BTNode* [2*t];
            for (int i=0; i<=curr->num_of_keys; i++)
                arr2[i]=curr->childes[i];
            arr2[curr->num_of_keys+1]=right->childes[0];

            curr->childes=arr2;
        }

        Node* arr3=new Node [2*t-1];

        for (int i=0; i<index; i++)
            arr3[i]=keys[i];
        arr3[index]=right->keys[0];
        for (int i=index+1; i<num_of_keys; i++)
            arr3[i]=keys[i];

        keys=arr3;

        Node* arr4=new Node [2*t-1];

        for (int i=1; i<right->num_of_keys; i++)
            arr4[i-1]=right->keys[i];

        right->keys=arr4;

        if (!right->is_leaf)
        {
            BTNode** arr5=new BTNode* [2*t];
            for (int i=1; i<right->num_of_keys+1; i+=1)
                arr5[i-1]=right->childes[i];
            right->childes=arr5;
        }
        curr->num_of_keys++;
        right->num_of_keys--;
    }

    void borrow_left(int index)
    {
        if (is_leaf)
            return;
        if (index<0)
            return;
        BTNode* curr=childes[index];
        BTNode* left=childes[index-1];

        Node* arr1=new Node [2*t-1];
        for ( int i=curr->num_of_keys-1; i>-1; i-=1)
            arr1[i+1]=curr->keys[i];

        BTNode** arr2=new BTNode* [2*t];
        if (!curr->is_leaf)
        {
            for (int i=curr->num_of_keys; i>-1; i-=1)
                arr2[i+1]=curr->childes[i];
        }

        arr1[0]=keys[index-1];
        curr->keys=arr1;
        if (!curr->is_leaf)
        {
            arr2[0] = left->childes[left->num_of_keys];
            curr->childes=arr2;
        }

        Node* arr3=new Node [2*t-1];
        for (int i=0; i<index-1; i++)
            arr3[i]=keys[i];
        arr3[index-1]=left->keys[left->num_of_keys-1];
        for (int i=index; i<num_of_keys; i++)
            arr3[i]=keys[i];
        keys=arr3;

        Node* arr4=new Node [2*t-1];
        BTNode** arr5=new BTNode* [2*t];
        for (int i=0; i<num_of_keys-1; i++)
        {
            arr4[i]=left->keys[i];
            arr5[i]=left->childes[i];
        }
        arr5[num_of_keys-1]=left->childes[num_of_keys-1];
        left->keys=arr4;
        left->childes=arr5;
        curr->num_of_keys++;
        left->num_of_keys--;
    }

    void fill_up(int index) //in case the BTNode does not have enough keys to be deleted
    {
        if (index!=num_of_keys && childes[index+1]->num_of_keys >= t)
        {
            borrow_right(index);
        }
        else if (index && childes[index-1]->num_of_keys >= t)
        {
            borrow_left(index);
        }
        else
        {
            if (index!=num_of_keys)
            {
                merge(index);
            }
            else
            {
                merge(index-1);
            }
        }
    }
    void del_leaf(int index)
    {
        Node* arr1=new Node [2*t-1];
        for (int i=0; i<index+1; i++)
            arr1[i]=keys[i];
        for (int i=index+1; i<num_of_keys; i++)
            arr1[i-1]=keys[i];
        keys=arr1;
        num_of_keys-=1;
    }

    void del_non_leaf(int index)
    {
        int val=keys[index].data;

        if (childes[index]->num_of_keys >=t)
        {
            Node p=*predecessor(index);
            keys[index]=p;
            childes[index]->del(p.data);
        }
        else if (childes[index+1]->num_of_keys >=t)
        {
            Node s=*successor(index);
            keys[index]=s;
            childes[index+1]->del(s.data);
        }
        else
        {
            merge(index);
            childes[index]->del(val);
        }

    }
    void del(int value)
    {
        int index=0;
        while ( index < num_of_keys && keys[index].data < value)
            index+=1;
        if (index < num_of_keys && keys[index].data==value)
        {
            if (!is_leaf)
                del_non_leaf(index);
            else
                del_leaf(index);
        }

        else
        {
            if (is_leaf)
            {
                cout << "the key does not exist to be deleted";
                return;
            }

            int is_equal= index==num_of_keys ? 1 : 0;

            if (childes[index]->num_of_keys < t) //might change the index value
                fill_up(index);

            if (is_equal && index > num_of_keys)
                childes[index-1]->del(value);
            else
                childes[index]->del(value);
        }
    }

    Node* search(long long value) {
        int i = 0;
        while (i < num_of_keys && value > keys[i].data)
            i++;

        if (keys[i].data == value)
            return &keys[i];

        if (is_leaf)
            return nullptr;

        return childes[i]->search(value);
    }
    Node* keys;
    int t; //minimum degree
    BTNode** childes;
    int num_of_keys;
    int is_leaf;
};

class B_tree
{
public:
    B_tree(int m)
    {
        t=m;
        rootPtr= nullptr;
    }
    Node* insert(long long value, Node* ptr)
    {
        if (rootPtr== nullptr)
        {
            rootPtr=creat_Node(1);
            rootPtr->keys[0].data=value;
            rootPtr->num_of_keys+=1;
            rootPtr->keys[0].self=rootPtr;
            rootPtr->keys[0].nextField=ptr;
            return &rootPtr->keys[0];
        }
        else
        {
            if (rootPtr->num_of_keys == 2*t-1)
            {
                BTNode* new_root= creat_Node(0);
                new_root->childes[0]=rootPtr;

                new_root->split(0, rootPtr);
                new_root->keys[0].self=new_root;

                int p=0;
                if (new_root->keys[0].data <= value)
                    p++;

                Node* A= new_root->childes[p]->simple_insert(value, ptr);

                rootPtr=new_root;
                return A;
            }

            else
            {
                return rootPtr->simple_insert(value, ptr);
            }
        }
    }
    void del(int value)
    {
        if (!rootPtr)
        {
            cout << "there is nothing to delete!";
            return;
        }
        else
            rootPtr->del(value);
    }
    void travel()
    {
        if (rootPtr)
            travel(rootPtr);
    }
    void travel2()
    {
        if (rootPtr)
            travel2(rootPtr);
    }

    Node* search(long long value)
    {
        return rootPtr->search(value);
    }
    BTNode* get_root()
    {
        return rootPtr;
    }
private:
    BTNode* rootPtr;
    int t; //minimum degree
    BTNode* creat_Node(int a)
    {
        return new BTNode(t, a);
    }
    void travel(BTNode* ptr)
    {
        int i=0;
        for (i=0; i<ptr->num_of_keys; i++)
        {
            if (!ptr->is_leaf)
                travel(ptr->childes[i]);
            cout << ptr->keys[i].data << " ";
        }

        if (!ptr->is_leaf)
            travel(ptr->childes[i]);
    }
    void travel2(BTNode* ptr)
    {
        if (ptr)
        {
            for (int i=0; i<ptr->num_of_keys; i++)
                cout << ptr->keys[i].data << " ";
            cout << "*";
            if (!ptr->is_leaf)
                for (int i=0; i<ptr->num_of_keys+1; i++)
                    travel2(ptr->childes[i]);
        }
    }
};