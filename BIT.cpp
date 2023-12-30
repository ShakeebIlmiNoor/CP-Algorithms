#include <bits/stdc++.h>

using namespace std;

class BIT{
public:
    int arr[1000];
    int n;
    
    BIT(int a[], int n){
        this->n = n;
        memset(arr,0,sizeof(arr));
        for(int i=0;i<n;i++) update(i,a[i]);
    }

    void update(int pos, int val){
        pos++;
        for(;pos<=n;pos+=pos&-pos) arr[pos]+=val;
    }

    int query(int pos){
        int sum = 0; pos++;
        for(;pos>0;pos-=pos&-pos) sum+=arr[pos];
        return sum;
    }

    int query(int pos1, int pos2){
        return query(pos2)-query(pos1-1);
    }
};

// Keep the array 0-indexed.
int main(){
    int n; cin >> n;
    int a[n];
    for(int i=0;i<n;i++) cin >> a[i];
    BIT bit(a, n);
    cout << bit.query(2,4) << "\n";
}