// Re-Rooting DP

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

const ll N=2e5+5 ;
vector<ll> v[N] ;
ll n,ans[N],subdist[N]={},subsize[N]={} ;
//  subsize[i] represents sizeof subtree rooted with i.
//  subdist[i] represents total distance of a subtree rooted with i (distance for i only).


void DFS(ll x,ll p){
    subsize[x]=1;
    for(auto i : v[x]){
        if (i!=p){
            DFS(i,x) ;
            subsize[x]+=subsize[i] ;
            subdist[x]+=subdist[i]+subsize[i] ;
        }
    }
}

void DFS1(ll x,ll p){
    ans[x] = (ans[p]-subsize[x]-subdist[x])+(n-subsize[x])+subdist[x] ;
    for(auto i : v[x]){
        if (i!=p)
            DFS1(i,x) ;
    }
}

int main() {
    IOS ;
    ll x,y ;
    cin>>n ;
    for(ll i=1 ; i<n ; i++){
        cin>>x>>y ;
        v[y].push_back(x) ;
        v[x].push_back(y) ;
    }
    DFS(1,-1) ;
    ans[1]=subdist[1] ;  // ans[1] is sum of the distances from the node 1 to all other nodes.
    for(auto i : v[1])
        DFS1(i,1) ;
    for(ll i=1 ; i<=n ; i++) cout<<ans[i]<<" " ;
	return 0;
}