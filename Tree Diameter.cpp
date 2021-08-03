#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const ll N=2e5+5 ;
vector<ll> v[N] ;
ll tmp=1,ans=0 ;

void DFS(ll x,ll p,ll cnt){
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
    ll n,x,i ;
    cin>>n ;
    while(--n){
        cin>>x>>i ;
        v[i].push_back(x) ;
        v[x].push_back(i) ;
    }
    DFS(1,-1,0) ;
    DFS(tmp,-1,0) ;
    cout<<ans<<endl ;
	return 0;
}