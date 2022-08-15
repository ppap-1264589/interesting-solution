#include <bits/stdc++.h>
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define pii pair<int, int>
#define f first
#define s second
#define ep emplace_back
using namespace std;

const int maxn = 1e4 +10;
const int LOG = log(maxn)+3;
int c[maxn][maxn];
pii E[maxn];
vector<pii> a[maxn];
int n;
int par[maxn];

int tdfs;
int tin[maxn];
int node[maxn << 1];
int h[maxn];
void DFS(int u, int PAR){
    tin[u] = ++tdfs;
    node[tdfs] = u;
    for (pii& x : a[u]){
        int v = x.first;
        if (v == PAR) continue;
        par[v] = u;
        h[v] = h[u] + 1;
        DFS(v, u);
        node[++tdfs] = u;
    }
}

int sp[LOG][maxn << 1];
int logg[maxn << 1];
int MIN(const int& x, const int& y){
    if (h[x] < h[y]) return x;
    return y;
}
void build_sparse(int n){
    up(i,1,n) sp[0][i] = node[i];
    for (int i = 1; (1 << i) <= n; i++){
        for (int j = 1; j + (1 << i) - 1 <= n; j++){
            sp[i][j] = MIN(sp[i-1][j], sp[i-1][j + (1 << (i-1))]);
        }
    }
}

int LCA(int u, int v){
    int l = tin[u];
    int r = tin[v];
    if (l > r) swap(l, r);
    int k = logg[r - l + 1];
    return MIN(sp[k][l], sp[k][r - (1 << k) + 1]);
}

void query(){
    string type;
    int x,y;
    while (cin >> type){
        if (type == "DONE") return;
        cin >> x >> y;
        if (type == "CHANGE"){
            c[E[x].f][E[x].s] = c[E[x].s][E[x].f] = y;
        }
        if (type == "NEGATE"){
            int l = LCA(x, y);
            while (x != l){
                c[x][par[x]] = -c[x][par[x]];
                c[par[x]][x] = -c[par[x]][x];
                x = par[x];
            }
            while (y != l){
                c[y][par[y]] = -c[y][par[y]];
                c[par[y]][y] = -c[par[y]][y];
                y = par[y];
            }
        }
        if (type == "QUERY"){
            int l = LCA(x, y);
            int maxx = -1e9 - 7;
            while (x != l){
                maxx = max(maxx, c[x][par[x]]);
                x = par[x];
            }
            while (y != l){
                maxx = max(maxx, c[y][par[y]]);
                y = par[y];
            }

            if (maxx == -1e9 - 7) cout << 0;
            else cout << maxx;
            cout << "\n";
        }
    }
}

void resetdata(){
    up(i,1,n) a[i].clear();
    up(i,1,n) up(j,i,n) c[i][j] = c[j][i] = 0;
    tdfs = 0;
}

void debug(){
    cout << LCA(4, 3);
    exit(0);
}

void solve(){
    cin >> n;
    resetdata();
    up(i,1,n-1){
        int u,v,w;
        cin >> u >> v >> w;
        a[u].ep(v, w);
        a[v].ep(u, w);
        E[i] = make_pair(u, v);
        c[u][v] = c[v][u] = w;
    }
    DFS(1, 0);
    build_sparse(tdfs);
    up(i,1,n-1){
        if (par[E[i].f] != E[i].s) swap(E[i].f, E[i].s);
    }

//    debug();

    query();
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    #define Task "QTREEX"
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    up(i,2,1e4) logg[i] = logg[i/2] + 1;
    int tt;
    cin >> tt;
    while (tt--) solve();


}
