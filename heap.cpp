#include <iostream>
using namespace std;
//---------------------------------------------------------heap-----------------------------------------------
template <class type> class heap
{
public:
    heap(int n)
    {
        size=n;
        last_index=-1;
        arr=new type [size];
        for (int i=0; i<n; i++)
        {
            arr[i]=-1;
        }
    }
    void insert(type data)
    {
        if (last_index==-1)
        {
            arr[0]=data;
            last_index=0;
            return;
        }
        else
        {
            last_index+=1;
            arr[last_index]=data;
            heapify_up(last_index);
            return;
        }
    }
    int top()
    {
        return arr[0];
    }
    int pop()
    {
        int t;
        t=arr[0];
        arr[0]=arr[last_index];
        last_index-=1;
        heapify_down(0);
        return t;
    }
    bool is_empty()
    {
        return last_index==-1;
    }
    int count()
    {
        return last_index+1;
    }
private:
    type* arr;
    int size;
    int last_index;
    void heapify_up(int index)
    {
        int lst=index;
        while(index && arr[index]<arr[parent(index)])
        {
            lst=index;
            swap(index, parent(index));
            index=parent(index);
        }
        while (index && arr[index]==arr[parent(index)])
        {
            lst=index;
            swap(index, parent(index));
            index=parent(index);
        }
        if ( lst && lst==left_child(parent(lst)))
        {
            if (lst+1<last_index && arr[lst]==arr[lst+1])
                swap(lst, lst+1);
            else if (lst+1< last_index && arr[lst] > arr[lst+1])
                swap(lst, lst+1);
        }
        else if (lst && lst==right_child(parent(lst)))
        {
            if (arr[lst]==arr[lst-1])
                swap(lst, lst-1);
            else if (arr[lst] < arr[lst-1])
                swap(lst, lst-1);
        }
    }
    void heapify_down(int index)
    {
        int left=left_child(index);
        int right=right_child(index);
        int smallest=index;
        if (left<last_index+1 && arr[left]<arr[index])
            smallest=left;
        if (right<last_index+1 && arr[right]<arr[smallest])
            smallest=right;
        if (smallest==index && right<last_index+1 && arr[right]==arr[left])
        {
            swap(right, left);
        }
        if(smallest!=index)
        {
            swap(index, smallest);
            heapify_down(smallest);
        }
    }
    int parent(int index)
    {
        index+=1;
        return index/2-1;
    }
    int left_child(int index)
    {
        index+=1;
        return 2*index-1;
    }
    int right_child(int index)
    {
        index+=1;
        return 2*index;
    }
    void swap(int i, int j)
    {
        type t1;
        int t2;
        t1=arr[i];
        arr[i]=arr[j];
        arr[j]=t1;
    }
};