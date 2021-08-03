#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
 
const ll N=2e5+5 ;
vector<ll> v[N] ;
ll ans[N]={} ;
 
void DFS(ll x,ll p){
    for(auto i : v[x]){
        if (i!=p){
            DFS(i,x) ;
            ans[x]+=(1+ans[i]) ;
        }
    }
}
 
int main() {
    IOS ;
    ll tc=1 ; 
	// cin>>tc ;
	while(tc--){
        ll n,x ;
        cin>>n ;
        for(ll i=2 ; i<=n ; i++){
            cin>>x ;
            v[i].push_back(x) ;
            v[x].push_back(i) ;
        }
        DFS(1,-1) ;
        for(ll i=1 ; i<=n ; i++){
            cout<<ans[i]<<" " ;
        }
    }
	return 0;
}