#include <bits/stdc++.h>
using namespace std;

typedef long long ;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const int N=5e4+4 ;
int par[N][50] ;

int getKthAncestor(int node, int k) {
    while(k>0){
        if (node==-1) break ;
        int x = log2(k) ;
        node = par[node][x] ;
        k-=(1<<x) ;
    }
    return node ;
}

int mai() {
    IOS;
    ll n ;
    cin>>n ;
    memset(par,-1,sizeof(par)) ;
    for(ll i=0 ; i<n ; i++){
        cin>>par[i][0] ;
    }
    for(ll j=1 ; j<50 ; j++){      // O(logN) - Always outer loop with k=log(N)
        for(ll i=0 ; i<n ; i++){      //  O(N)
            int x = par[i][j-1] ;
            if (x!=-1)
                par[i][j]=par[x][j-1] ;
        }
    }
    cout<<getKthAncestor(3,1)<<endl ;   // 1
    cout<<getKthAncestor(5,2)<<endl ;   // 0
    cout<<getKthAncestor(6,3)<<endl ;   // -1

	return 0;
}
// Complexity : Nlog(N)
// 7
// -1 0 0 1 1 2 2