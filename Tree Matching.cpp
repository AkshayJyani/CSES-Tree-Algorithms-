#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const ll N=2e5+5 ;
vector<ll> v[N] ;
ll vis[N]={} , ans=0 ;

void DFS(ll x,ll p){
    for(int i : v[x]){
        if (i!=p){
            DFS(i,x) ;
            if (!vis[i] && !vis[x]){
                vis[i]=1 ;
                vis[x]=1 ;
                ans++ ;
            }
        }
    }
}

int main() {
    IOS ;
    ll n,x,y ;
    cin>>n ;
    while(--n){
        cin>>x>>y ;
        v[x].push_back(y) ;
        v[y].push_back(x) ;
    }
    DFS(1,-1) ;
    cout<<ans<<endl ;
	return 0;
}