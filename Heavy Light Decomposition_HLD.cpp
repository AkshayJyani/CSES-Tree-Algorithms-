const ll N=2e5+5 ;
vector<ll> adj[N] ;
ll val[N]={}, depth[N]={}, par[N][20] , subsize[N] ;
ll chainNo=0 , idx=0 ;
ll baseArray[N] , posInBase[N] ;
ll chainPos[N] , chainIdx[N] , chainHead[N] , chainSize[N] ;

/*
 * Actual HL-Decomposition part
 * Initially all entries of chainHead[] are set to -1.
 * So when ever a new chain is started, chain head is correctly assigned.
 * As we add a new node to chain, we will note its position in the baseArray.
 * In the first for loop we find the child node which has maximum sub-tree size (Special child). 
 * The following if condition is failed for leaf nodes.
 * When the if condition passes, we expand the chain to special child.
 * In the second for loop we recursively call the function on all normal nodes.
 * chainNo++ ensures that we are creating a new chain for each normal child.
 */

void HDL(ll curr,ll p){
    if (chainHead[chainNo]==-1)
        chainHead[chainNo]=curr ;
    chainIdx[curr]= chainNo ;
    chainPos[curr]= chainSize[chainNo] ;
    chainSize[chainNo]++ ;
    // posInBase[curr]=idx ;
    // baseArray[idx++]= val[curr] ;

    // finding special child
    ll sc=-1 ;    
    for(ll it : adj[curr]){
        if (it!=p){
            if (sc==-1 || subsize[it]>subsize[sc])
                sc=it ;
        }
    }
    if (sc!=-1){
        HDL(it,curr) ;
    }
    for(ll it : adj[curr]){
        if (it!=p && it!=sc){
            chainNo++ ;        // New chains at each normal node
            HDL(it,x) ;
        }
    }
}