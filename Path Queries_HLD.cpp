// Heavy-Light decomposition of trees |
// decompose the tree into chains using heavy-light scheme and then build a segment tree over each chain.
// heavy-light scheme ensures there can be at most O(logn) chains, each query can be answered in O(logn)^2 time.

// Similarly, each update can be performed in O(logn) time as it requires update on a single chain 
        // (single segment tree) corresponding to the given node.

// Interesting BLOG on HLD : https://blog.anudeep2011.com/heavy-light-decomposition/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const ll N=2e5+5 ;
vector<ll> adj[N] ;
ll val[N]={}, depth[N]={}, par[N][20] , subsize[N] ;
ll n, chainNo=0 , idx=0 ;
ll baseArray[N], posInBase[N], chainIdx[N] , chainHead[N] ;
ll tree[4*N] ;  // array size is almost N so ST Array should be 4 times of array size


void build(ll st, ll ed, ll idx){
    if (st==ed){
        tree[idx]=baseArray[st] ;
        return ;
    }
    ll mid=st+(ed-st)/2 ;
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

ll query(ll u,ll v){
    ll uchain=chainIdx[u] , vchain=chainIdx[v] , ans=0 ;
    while(1){
        uchain = chainIdx[u] ;
        if (uchain==vchain){
            ans+=sumst(0,n-1,1,posInBase[v],posInBase[u]) ;
            break ;
        }
        ans+=sumst(0,n-1,1,posInBase[chainHead[uchain]],posInBase[u]) ;
        u = chainHead[uchain] ;
        u = par[u][0] ;
    }
    return ans ;
}

void HDL(ll curr,ll p){
    if (chainHead[chainNo]==-1)
        chainHead[chainNo]=curr ;
    chainIdx[curr]= chainNo ;
    posInBase[curr]=idx ;
    baseArray[idx++]= val[curr] ;

    // finding special child
    ll sc=-1 ;
    for(ll it : adj[curr]){
        if (it!=p){
            if (sc==-1 || subsize[it]>subsize[sc])
                sc=it ;
        }
    }
    if (sc!=-1){
        HDL(sc,curr) ;
    }
    for(ll it : adj[curr]){
        if (it!=p && it!=sc){
            chainNo++ ;         // New chains at each normal node
            HDL(it,curr) ;
        }
    }
}

void DFS(ll x, ll p, ll cnt){
    depth[x]=cnt ;
    par[x][0] = p ;
    subsize[x]=1 ;
    for(ll it : adj[x]){
        if (it!=p){
            DFS(it,x,cnt+1) ;
            subsize[x]+=subsize[it] ;
        }
    }
}

int main() {
    IOS ;
    ll q,x,y,z ;
    cin>>n>>q ;
    for(ll i=1 ; i<=n ; i++) cin>>val[i] ;
    memset(par,-1,sizeof(par)) ;            
    memset(chainHead,-1,sizeof(chainHead)) ;    // all entries of chainHead[] are set to -1
    for(ll i=1 ; i<n ; i++){
        cin>>x>>y ;
        adj[x].push_back(y) ;
        adj[y].push_back(x) ;
    }

    chainNo=0 ;
    DFS(1,-1,0) ;
    HDL(1,-1) ;
    build(0,n-1,1);

    // for(ll i=0 ; i<=2*n ; i++) cout<<tree[i]<<" " ; cout<<endl ;
    // for(ll i=0 ; i<=n ; i++) cout<<baseArray[i]<<" " ; cout<<endl ;
    // for(ll i=0 ; i<=n ; i++) cout<<posInBase[i]+1<<" " ; cout<<endl ;

    while(q--){
        cin>>x ;
        if (x==1){
            cin>>y>>z ;
            update(0,n-1,1,posInBase[y],z) ;
        }
        else{
            cin>>y ;
            cout<<query(y,1)<<endl ;
        }
    }

	return 0;
}