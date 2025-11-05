#include <bits/stdc++.h>
using namespace std;
class heap{
    public:
    int a[100];
    int size;

    heap(){
        a[0]=-1;
        size=0;
    }

    void insert(int val){
        size++;
        int i=size;
        a[i]=val;
        
        while(i>1){
            int parent=i/2;

            if(a[parent]<a[i]){
                swap(a[parent],a[i]);
                i=parent;
            }
            else
            return ;
        }
    }

    void print(){
        for(int j=1;j<=size;j++){
            cout<<a[j]<<" ";
        }cout<<endl;
    }
//deleting from root node
    void del(){
        if(size==0){
            cout<<"nothing to delete"<<endl;
        }
        a[1]=a[size];
        size--;
        int k=1;
        while(k<=size){
            int leftindex=2*k;
            int rightindex=2*k +1;

            if(leftindex<size && a[k]<a[leftindex]){
                swap(a[k],a[leftindex]);
                k=leftindex;
            }
            if(rightindex<size && a[k]<a[rightindex]){
                swap(a[k],a[rightindex]);
                k=rightindex;
            }
            else
            return;

        }

    }
 void heapify(int a[],int n, int i){
        int large=i;
        int left=2*i;
        int right=2*i+1;

        if(left<=n && a[large]<a[left]){
            large=left;
        }
        if(right<=n && a[large]<a[right]){
            large=right;
        }
        if(large !=i){
            swap(a[large],a[i]);
            heapify(a,n,large);
        }
    }

 void heapsort(int a[],int n){
            int t=n;
            while(t>1){
                swap(a[t],a[1]);
                t--;
                heapify(a,t,1);

            }
        }
 
};
  
int main() {
    heap h;
   
    int a[6]={-1,54,53,55,52,50};
    int n=5;
    for(int i=n/2;i>0;i--){
    h.heapify(a,n,i);
}

    cout<<"printing"<<endl;
    for(int i=1;i<=n;i++){
        cout<<a[i]<<" ";
    }cout<<endl; 

    h.heapsort(a,n);
    cout<<"print sort"<<endl;
    for(int i=1;i<=n;i++){
        cout<<a[i]<<" ";
    }cout<<endl; 
   

    priority_queue<int> pq;
    pq.push(3);
    pq.push(5);
    pq.push(4);
    pq.push(2);
    pq.push(1);
    pq.pop();
    cout<<pq.top()<<endl;


    priority_queue<int,vector<int>,greater<int>> minl;
minl.push(5);
minl.push(4);
minl.push(3);
minl.push(2);
minl.push(1);
cout<<minl.top()<<endl;

 return 0;
}