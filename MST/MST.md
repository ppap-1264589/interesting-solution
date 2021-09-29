```C++
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define Task            "A"                                 ///map of knowledge
#define ll              long long                           //+ Binary Lifting
#define bit(x,i)        ((x >> i) & 1)                      //+ Hash Table
#define stt(x,i)        (x & (1 << i))                      //+ Trie Tree
#define trail0(x)       (x & (-x))                          //+ Sparse Table - RMQ
#define up(i,a,b)       for (int i = (a); i <= (b); i++)    //+ Matrix
#define down(i,a,b)     for (int i = (a); i >= (b); i--)    //+ DSU
#define MOD             1000000007                          //+ Joints - Bridges
#define base            311                                 //+ SCC
#define pii             pair<int, int>                      //+ Z-KMP
#define f               first
#define s               second
#define pb              push_back
#define ep              emplace_back
using namespace std;

const int maxn = 100001;
int n,m;
struct edges{
    int u,v;
    int w;
};
vector<edges> E;
long long res = 0;

int par[maxn];
int root(int u){
    if (par[u] == u) return u;
    int x = root(par[u]);
    par[u] = x;
    return x;
}

void Union(int u, int v){
    u = root(u);
    v = root(v);
    if (u != v) par[u] = v;
}

bool Same(int u, int v){
    return (root(u) == root(v));
}

bool cmp(const edges& x, const edges& y){
    return (x.w < y.w);
}

void Kruskal(){
    sort(E.begin(), E.end(), cmp);
    for (auto e : E){
        if (!Same(e.u, e.v)) {
            Union(e.u, e.v);
            res += e.w;
        }
    }
}

signed main (){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if (fopen(Task".inp", "r")){
        freopen (Task".inp", "r", stdin);
        freopen (Task".out", "w", stdout);
    }
    cin >> n >> m;
    int u,v,w;
    up(i, 1, m){
        cin >> u >> v >> w;
        E.pb({u, v, w});
    }
    up(i, 1, n) par[i] = i;
    Kruskal();
    cout << res;
    return 0;
}
```
