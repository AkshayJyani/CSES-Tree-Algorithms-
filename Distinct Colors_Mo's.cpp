// using Mo's algorithm on trees 
// Flatten the tree to an array using the same technique mentioned in solution of Subtree Queries.
// Then the subtree of each node will correspond to a contiguous subarray of flattened array.
//  We can then use Mo's algorithm to answer each query in O(√n) time with O(n√n) preprocessing.


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const int N=2e5+1 ;
vector<int> adj[N] ;
int n , SQRT=700 ;    // It's good to choose 700 & also greater than sqrt(n)
ll col[N]={} , res[N] , freq[N]={} , ans=0 ;   // res[i] stores result of query i .
ll start[N],finish[N], flat_arr[2*N+1], timer=0 ;    // start[i] - start time for node i in flat_arr

struct node{
    ll L,R,pos ;
} query[N] ;

void map_colors(){          // convert larger values(like 1e9) into smaller values , in between 0 to n 
    map<ll,ll> mp ;
    vector<ll> col_copy(col+1,col+1+n) ;
    sort(col_copy.begin(),col_copy.end()) ;
    for(ll i=0 ; i<n ; i++)
        mp[col_copy[i]]=i ;
    for(ll i=1 ; i<=n ; i++)
        col[i] = mp[col[i]] ;
}

void Eular_tour_array(ll x,ll p){
    start[x]=timer ;
    flat_arr[timer]=col[x] ;
    timer++ ;
    for(ll i : adj[x]){
        if (i!=p)
            Eular_tour_array(i,x) ;
    }
    finish[x]=timer ;
    flat_arr[timer]=col[x] ;
    timer++ ;
}

bool cmp(node a, node b){
    if (a.L/SQRT != b.L/SQRT)
        return a.L < b.L ;
    return a.R < b.R ;
}

void Add(ll pos){
    freq[flat_arr[pos]]++ ;
    if (freq[flat_arr[pos]]==1)
        ans++ ;
}

void Remove(ll pos){
    freq[flat_arr[pos]]-- ;
    if (freq[flat_arr[pos]]==0)
        ans-- ;
}

void mos_algorithm(){
    sort(query+1,query+1+n,cmp) ;
    ll currL=0 , currR=0 , L , R ;

    for(ll i=1; i<=n ; i++){
        L = query[i].L ;        
        R = query[i].R ;

        while(currL<L){
            Remove(currL) ;
            currL++ ;
        }
        while(currL>L){
            Add(currL-1) ;      // currL is already included from previous query 
            if (currL==L) break ;
            currL-- ;
        }
        while(currR>R){
            Remove(currR) ;
            currR-- ;
        }
        while(currR<R){
            Add(currR+1) ;      // currR is already included from previous query 
            if (currR==R) break ;
            currR++ ;
        }
        res[query[i].pos]= ans ;
    }
}

int main() {
    IOS ;
    ll x,y ;
    cin>>n ;
    SQRT = ceil(sqrt(2*n)) ;
    for(ll i=1 ; i<=n ; i++){
        cin>>col[i] ;
    }  
    map_colors();  // convert larger values into smaller values , in between 0 to n 

    for(int i=1 ; i<n ; i++){
        cin>>x>>y ;
        adj[x].push_back(y) ;
        adj[y].push_back(x) ;
    }
    Eular_tour_array(1,-1) ;
    // for(ll i=0 ; i<=2*n ; i++) cout<<flat_arr[i]<<" \n"[i==2*n] ;

    for(int i=1 ; i<=n ; i++){
        query[i].L = start[i] ;
        query[i].R = finish[i] ;
        query[i].pos = i ;
    }

    mos_algorithm();

    for(ll i=1 ; i<=n ; i++)
        cout<<res[i]<<" " ;

	return 0;
}