#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const ll N=2e5+5 ;
vector<ll> v[N] ;
ll tmp=1,ans=0,d[N]={},dis[N] ;

void DFS(ll x,ll p,ll cnt){
    d[x]=cnt ;                 //  dis[x]=max(dis[x],cnt) ;
    for(auto i : v[x]){
        if (i!=p){
            if (cnt+1>ans){
                ans=cnt+1 ;
                tmp=i ;
            }
            DFS(i,x,cnt+1) ;
        }
    }
}

int main() {
    IOS ;
    ll n,x,y ;
    cin>>n ;
    for(ll i=1 ; i<n ; i++){
        cin>>x>>y ;
        v[y].push_back(x) ;
        v[x].push_back(y) ;
    }
    DFS(1,-1,0) ;

    ans=0 ;
    DFS(tmp,-1,0) ;     // tmp is First Node of Maximum Diameter Path
    for(ll i=1 ; i<=n ; i++)
        dis[i]=max(dis[i],d[i]) ;  // Distance From First node of Maximum Diameter path.
    
    memset(d,0,sizeof(d)) ;
    ans=0 ;
    DFS(tmp,-1,0) ;     // tmp was Last Node of Maximum Diameter Path
    for(ll i=1 ; i<=n ; i++)
        dis[i]=max(dis[i],d[i]) ;   // Distance From Last node of Maximum Diameter path.

    for(ll i=1 ; i<=n ; i++) cout<<dis[i]<<" " ;
	return 0;
}