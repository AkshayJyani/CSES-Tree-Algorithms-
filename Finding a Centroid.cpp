// We can find a centroid in a tree by starting at the root
// Each step, loopthrough all of its children. (DFS)
// If all of its children have subtree size less than or equal to N/2 then it is a centroid.
// Otherwise, move to the child with a subtree size that is more than N/2 and repeat until you find a centroid.


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const int N=2e5+1 ;
vector<int> adj[N] ;
ll n , subsize[N] ;

void DFS(ll x,ll p){   // for finding subtree size .
    subsize[x]=1 ;
    for(ll i : adj[x]){
        if (i!=p){
            DFS(i,x) ;
            subsize[x]+=subsize[i] ;
        }
    }
}

// Return centroid of a Tree
ll get_centroid(ll node, ll p){
    for(ll i : adj[node] ){
        if (i!=p && subsize[i]>n/2)
            node = get_centroid(i,node) ;
    }
    return node ;
}

int main() {
    IOS ;
    
    ll x,y ;
    cin>>n ;
    for(ll i=1 ; i<n ; i++){
        cin>>x>>y ;
        adj[x].push_back(y) ;
        adj[y].push_back(x) ;
    }
    DFS(1,-1) ;

    cout<<get_centroid(1,-1)<<endl ;

	return 0;
}