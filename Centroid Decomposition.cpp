// A centroid of a tree is defined as a node such that when the tree is rooted at it, no other nodes have a subtree of size greater than N/2.
// Each step, loopthrough all of its children. (DFS)
// If all of its children have subtree size less than or equal to N/2 then it is a centroid.
// Otherwise, move to the child with a subtree size that is more than N/2 and repeat until you find a centroid.
// Centroid Decomposition is a divide and conquer technique for trees.
// Centroid Decomposition works by repeated splitting the tree and each of the resulting subgraphs at the centroid, 
// producing O(logn) layers of subgraphs.


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const ll N=2e5+1 ;
vector<ll> adj[N] ;
vector<ll> centroidTree[N];  // Edges of New Centroid Tree form
bool centroidMarked[N];
ll subsize[N] ;

void addEdge(ll u, ll v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void get_subtree_sizes(ll src,ll p){
    subsize[src]=1 ;
    for(ll i : adj[src] ){
        if (i!=p && !centroidMarked[i] ){
            get_subtree_sizes(i,src) ;
            subsize[src]+=subsize[i] ;
        }
    }
}

// Return centroid of a Tree
ll get_centroid(ll node, ll p,ll cnt){
    for(ll i : adj[node] ){
        if (i!=p && !centroidMarked[i] && subsize[i]>cnt/2)
            node = get_centroid(i,node,cnt) ;
    }
    return node ;
}

ll CentroidDecomposition(ll root){

    get_subtree_sizes(root,-1) ;
    ll centroid = get_centroid(root,-1,subsize[root]) ;
    centroidMarked[centroid] = true ;

    printf("%d ", centroid);

    for(ll it : adj[centroid] ){
        if (!centroidMarked[it]){
            ll cntd_subtr = CentroidDecomposition(it) ;
            centroidTree[cntd_subtr].push_back(centroid) ;
            centroidTree[centroid].push_back(cntd_subtr) ;
        }
    }
    return centroid ;
}


int main() {
    IOS ;
    
    // ll x,y ;
    // cin>>n ;
    // for(ll i=1 ; i<n ; i++){
    //     cin>>x>>y ;
    //     adj[x].push_back(y) ;
    //     adj[y].push_back(x) ;
    // }
    // DFS(1,-1) ;

    // cout<<get_centroid(1,-1)<<endl ;

    ll n = 16;
  
    /* arguments in order: node u, node v
     * sequencing starts from 1 */
    addEdge(1, 4);
    addEdge(2, 4);
    addEdge(3, 4);
    addEdge(4, 5);
    addEdge(5, 6);
    addEdge(6, 7);
    addEdge(7, 8);
    addEdge(7, 9);
    addEdge(6, 10);
    addEdge(10, 11);
    addEdge(11, 12);
    addEdge(11, 13);
    addEdge(12, 14);
    addEdge(13, 15);
    addEdge(13, 16);
  
    /* generates centroid tree */
    CentroidDecomposition(1) ;

	return 0;
}