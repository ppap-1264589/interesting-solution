#include <bits/stdc++.h>
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define pii pair<int, int>
#define f first
#define s second
#define ep emplace_back
#define void inline void
using namespace std;

const int maxn = 1e4 + 10;
const int LIM = 1e9 + 7;
struct Node{
    int maxx, minn;
    bool change;

    void Merge(const Node& L, const Node& R){
        int Lmax, Lmin;
        int Rmax, Rmin;
        if (L.change){
            Lmax = -L.minn;
            Lmin = -L.maxx;
        }
        else{
            Lmax = L.maxx;
            Lmin = L.minn;
        }
        if (R.change){
            Rmax = -R.minn;
            Rmin = -R.maxx;
        }
        else{
            Rmax = R.maxx;
            Rmin = R.minn;
        }
        maxx = max(Lmax, Rmax);
        minn = min(Lmin, Rmin);
    }
} T[maxn << 2];

int n;
vector<pii> a[maxn];
int c[maxn];
pii E[maxn];


int par[maxn];
int heavy[maxn];
int Tsize[maxn];
void DFS(int u, int PAR){
    Tsize[u] = 1;
    int max_size = 0;
    int id = -1;
    up(i,0,a[u].size()-1){
        int& v = a[u][i].f;
        int& w = a[u][i].s;
        if (v == PAR) continue;
        par[v] = u;
        c[v] = w;
        /*
        weight of edge from root->(u -> v)
        = weight of node[v]
        */
        DFS(v, u);
        Tsize[u] += Tsize[v];
        if (max_size < Tsize[v]){
            max_size = Tsize[v];
            heavy[u] = v;
            id = i;
        }
    }
    if (id != -1) swap(a[u][0], a[u][id]);
}

int Hchain[maxn], Dchain[maxn];
int node[maxn];
int Tin[maxn];
int thld;
void HLD(int u, int PAR){
    Tin[u] = ++thld;
    node[thld] = u;
    for (pii& x : a[u]){
        int v = x.f;
        if (v == PAR) continue;
        if (heavy[u] == v){
            Hchain[v] = Hchain[u];
            Dchain[v] = Dchain[u];
        }
        else{
            Hchain[v] = v;
            Dchain[v] = Dchain[u] + 1;
        }
        HLD(v, u);
    }
}

void build(int nod, int l, int r){
    T[nod].change = 0;
    if (l == r){
        T[nod].maxx = T[nod].minn = c[node[l]];
        return;
    }
    int mid = (l+r) >> 1;
    build(nod*2, l, mid);
    build(nod*2+1, mid+1, r);
    T[nod].maxx = max(T[nod*2].maxx, T[nod*2+1].maxx);
    T[nod].minn = min(T[nod*2].minn, T[nod*2+1].minn);
}

void push_down(int nod){
    up(i, nod*2, nod*2+1){
        T[i].change ^= T[nod].change;
    }
    T[nod].change = 0;
}

void Negate(int nod, int l, int r, int u, int v){
    if (l > v || r < u || l > r) return;
    if (l >= u && r <= v){
        T[nod].change ^= 1;
        return;
    }
    push_down(nod);
    int mid = (l+r) >> 1;
    Negate(nod*2, l, mid, u, v);
    Negate(nod*2+1, mid+1, r, u, v);
    T[nod].Merge(T[nod*2], T[nod*2+1]);
}

void update(int nod, int l, int r, int pos, int val){
    if (l == r){
        T[nod].maxx = T[nod].minn = val;
        T[nod].change = 0;
        return;
    }
    push_down(nod);
    int mid = (l+r) >> 1;
    if (pos <= mid) update(nod*2, l, mid, pos, val);
    else update(nod*2+1, mid+1, r, pos, val);
    T[nod].Merge(T[nod*2], T[nod*2+1]);
}

inline int get(int nod, int l, int r, int u, int v){
    if (l > v || r < u) return -1e9 - 7;
    if (l >= u && r <= v) {
        if (T[nod].change) return -T[nod].minn;
        return T[nod].maxx;
    }
    push_down(nod);
    int mid = (l+r) >> 1;
    int L = get(nod*2, l, mid, u, v);
    int R = get(nod*2+1, mid+1, r, u, v);
    T[nod].Merge(T[nod*2], T[nod*2+1]);
    return max(L, R);
}

void update(int x, int val){
    update(1, 1, n, Tin[x], val);
}

void Negate(int u, int v){
    while (Hchain[u] != Hchain[v]){
        if (Dchain[u] > Dchain[v]) swap(u, v);
        Negate(1, 1, n, Tin[Hchain[v]], Tin[v]);
        v = par[Hchain[v]];
    }

    if (Tin[u] > Tin[v]) swap(u, v);
    Negate(1, 1, n, Tin[u]+1, Tin[v]);
    //why +1 for Tin[u] ? because we don't update the weight of the LCA of u and v
}

inline int get(int u, int v){
    int maxx = -LIM;
    while (Hchain[u] != Hchain[v]){
        if (Dchain[u] > Dchain[v]) swap(u, v);
        maxx = max(maxx, get(1, 1, n, Tin[Hchain[v]], Tin[v]));
        v = par[Hchain[v]];
    }

    if (Tin[u] > Tin[v]) swap(u, v);
    maxx = max(maxx, get(1, 1, n, Tin[u]+1, Tin[v]));
    return maxx;
}

void solve(){
    cin >> n;
    up(i,1,n) a[i].clear();
    thld = 0;

    up(i,1,n-1){
        int u,v,w;
        cin >> u >> v >> w;
        a[u].ep(v, w);
        a[v].ep(u, w);
        E[i] = make_pair(u, v);
    }
    DFS(1, 0);
    Hchain[1] = Dchain[1] = 1;
    HLD(1, 0);
    build(1, 1, n);

    up(i,1,n-1){
        if (par[E[i].f] != E[i].s) swap(E[i].f, E[i].s);
        //E[i].s = parrent
        //E[i].f = children
    }

    string type;
    int x,y;
    while (cin >> type){
        if (type == "DONE") return;
        cin >> x >> y;
        if (type == "CHANGE") update(E[x].f, y);
        else if (type == "NEGATE") Negate(x, y);
        else {
            int res = get(x, y);
            cout << ((res == -LIM) ? 0 : res) << "\n";
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    #define Task "QTREEX"
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    int tt;
    cin >> tt;
    while (tt--) solve();
}
