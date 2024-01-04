#include <bits/stdc++.h>

using namespace std;

class Treap{
public:
    int data, priority;
    vector<Treap*> kids;
    int subtreeSize, sum, toProp ;

    Treap(int data){
        kids={NULL,NULL};
        priority=rand();
        this->data = data;
        toProp=0;
        sum=0;
        subtreeSize=0;
        recalc();
    }
    
    int size(){
        return this==NULL ? 0 : subtreeSize;
    }

    void recalc(){
        if(!this) return;
        subtreeSize=1;
        sum=data+toProp*size();
        for(Treap* t:kids){
            if(t){
                subtreeSize+=t->subtreeSize;
                sum+=t->sum+(t->toProp*(t->size()));
            }
        }
    }

    void prop(){
        if(!this) return;
        if(toProp==0) return;
        for(Treap* t:kids){
            if(t) t->toProp+=toProp;
        }
        data+=toProp;
        toProp=0;
        recalc();
    }
};

vector<Treap*> split(Treap* t, int nInLeft){
    if(!t) return{NULL,NULL};
    t->prop();
    if(t->kids[0]->size()>=nInLeft){
        vector<Treap*> leftRes=split(t->kids[0],nInLeft);
        t->kids[0]=leftRes[1];
        t->recalc();
        return {leftRes[0],t};
    }
    else{
        nInLeft-=(t->kids[0]->size()+1);
        vector<Treap*> rightRes=split(t->kids[1],nInLeft);
        t->kids[1]=rightRes[0];
        t->recalc();
        return {t,rightRes[1]};
    }
}

Treap* merge(Treap* l, Treap* r){
    if(!l) return r;
    if(!r) return l;
    l->prop(); r->prop();
    if(l->priority<r->priority){
        l->kids[1]=merge(l->kids[1],r);
        l->recalc();
        return l;
    }
    else{
        r->kids[0]=merge(l,r->kids[0]);
        r->recalc();
        return r;
    }
}

Treap* rangeAdd(Treap* t, int l, int r, int toAdd){
    vector<Treap*> a=split(t,l), b=split(a[1],r-l+1);
    b[0]->toProp+=toAdd;
    return merge(a[0],merge(b[0],b[1]));
}

int main(){
    int n; cin >> n;
    int a[n];
    for(int i=0;i<n;i++) cin >> a[i];
    Treap* t=NULL;
    for(int i=0;i<n;i++){
        t=merge(t,new Treap(a[i]));
    }
    // The indexes are in 0-based indexing.
    t=rangeAdd(t,1,2,4);
    for(int i=0;i<n;i++){
        vector<Treap*> temp=split(t,1);
        cout << temp[0]->data << " ";
        t=temp[1];
    }
}