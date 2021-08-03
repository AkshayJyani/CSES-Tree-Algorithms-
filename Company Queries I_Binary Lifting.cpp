// Binary Lifting - O(logN)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const ll N=2e5+5 ;
int par[N][20] ;

int getKthAncestor(int node, int k) {
    while(k>0){
        if (node==-1) break ;
        int x = log2(k) ;
        node = par[node][x] ;
        k-=(1<<x) ;
    }
    return node ;
}

int main() {
    IOS ;
    ll n,q,x,y ;
    cin>>n>>q ;
    memset(par,-1,sizeof(par)) ;
    for(ll i=2 ; i<=n ; i++){
        cin>>x ;
        par[i][0]=x ;
    }

    for(ll j=1 ; j<20 ; j++){      // O(logN)
        for(ll i=1 ; i<=n ; i++){      //  O(N)
            int x = par[i][j-1] ;
            if (x!=-1)
                par[i][j]=par[x][j-1] ;
        }
    }

    while(q--){
        cin>>x>>y ;
        cout<<getKthAncestor(x,y)<<endl ;
    }

	return 0;
}

