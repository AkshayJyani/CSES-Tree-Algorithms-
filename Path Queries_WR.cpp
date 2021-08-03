// Use of Eular Tour Technique | Flatting Tree | Range Query using Segment Tree .
// same as Subtree Quaries question , only differenece is after visiting node set negative value in the flat array.

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const ll N=2e5+5 ;
vector<ll> v[N] ;
ll val[N]={},level[N]={},par[N][20] ;
ll start[N],endd[N], flat_arr[2*N+1], timer=0 ;
ll tree[8*N] ;  // flat array size is almost 2*N so ST Array should be 4 times of array size


void Eular_tour_array(ll x,ll p){
    start[x]=timer ;
    flat_arr[timer]=val[x] ;
    timer++ ;
    for(ll i : v[x]){
        if (i!=p)
            Eular_tour_array(i,x) ;
    }
    endd[x]=timer ;
    flat_arr[timer]=-val[x] ;   // negation of element , overall sum will be zero for subtree.
    timer++ ;
}

void build(ll st, ll ed, ll idx){
    if (st==ed){
        // cout<<"idx: "<<idx<<" "<<st<<" "<<flat_arr[st]<<endl ;
        tree[idx]=flat_arr[st] ;
        return ;
    }
    ll mid=st+(ed-st)/2 ;
    // cout<<"||: " <<mid<<endl ;
    build(st,mid,2*idx) ; 
    build(mid+1,ed,2*idx+1) ;
    tree[idx] = tree[2*idx]+tree[2*idx+1] ;
}

void update(ll st, ll ed, ll idx, ll pos,ll valc){
    if (st==ed){
        tree[idx]=valc ;
    }
    else{
        ll mid = st+(ed-st)/2 ;
        if (mid>=pos)
            update(st,mid,2*idx, pos,valc) ;
        else    
            update(mid+1,ed,2*idx+1, pos,valc) ;
        tree[idx] = tree[2*idx]+tree[2*idx+1] ;
    }
}

ll sumst(ll st, ll ed,ll idx, ll l, ll r){
    if (st>r || l>ed)
        return 0 ;
    if (st>=l && r>=ed )
        return tree[idx] ;
    ll mid = st+(ed-st)/2 ;
    return sumst(st,mid,2*idx,l,r)+sumst(mid+1,ed,2*idx+1,l,r) ;
}

int main() {
    IOS ;
    ll n,q,x,y,z ;
    cin>>n>>q ;
    for(ll i=1 ; i<=n ; i++) cin>>val[i] ;
    memset(par,-1,sizeof(par)) ;
    for(ll i=1 ; i<n ; i++){
        cin>>x>>y ;
        v[x].push_back(y) ;
        v[y].push_back(x) ;
    }
    Eular_tour_array(1,-1) ;
    // for(ll i=0 ; i<=2*n ; i++) cout<<flat_arr[i]<<" " ; cout<<endl ;
    
    build(0,2*n-1,1);
    // for(ll i=0 ; i<=8*n ; i++) std::cout<<tree[i]<<" " ; cout<<endl ;
    
    while(q--){
        cin>>x ;
        if (x==1){
            cin>>y>>z ;
            update(0,2*n-1,1,start[y],z) ;
            update(0,2*n-1,1,endd[y],z) ;
        }
        else{
            cin>>y ;
            cout<<sumst(0,2*n-1,1,0,start[y])<<endl ;
        }
    }

	return 0;
}