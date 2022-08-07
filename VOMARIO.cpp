#include <bits/stdc++.h>
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define pii pair<long long, long long>
#define a first
#define b second
#define int long long
#define all(x) x.begin(), x.end()
#define purge(x) x.resize(unique(x.begin(), x.end()) - x.begin())
using namespace std;

const int maxn = 1e5 + 10;
pii Line[maxn];

int n;
int x[maxn], w[maxn], e[maxn];
pii T[maxn << 2]; // IT Doan Thang

int realval[maxn];
int get(const pii& L, int x){
    return L.a*realval[x] + L.b;
}

int query(int nod, int l, int r, int pos){
    int res = get(T[nod], pos);
    if (l == r) return res;

    int val;
    int mid = (l+r) >> 1;

    if (pos <= mid) val = query(nod*2, l, mid, pos);
    else val = query(nod*2+1, mid+1, r, pos);
    res = max(res, val);
    return res;
}

void update(int nod, int l, int r, int u, int v, const pii& Line){
    if (l > v || r < u) return;

    int mid = (l+r) >> 1;
    if (l >= u && r <= v){
        int TL = get(T[nod], l);
        int Tmid1 = get(T[nod], mid);
        int Tmid2 = get(T[nod], mid+1);
        int TR = get(T[nod], r);
        int LineL = get(Line, l);
        int Linemid1 = get(Line, mid);
        int Linemid2 = get(Line, mid+1);
        int LineR = get(Line, r);

        if (TL >= LineL && TR >= LineR){
            return;
        }
        if (TL <= LineL && TR <= LineR){
            T[nod] = Line;
            return;
        }

        if (TL <= LineL && Tmid1 <= Linemid1){
            update(nod*2+1, mid+1, r, u, v, T[nod]);
            T[nod] = Line;
            return;
        }

        if (TL >= LineL && Tmid1 >= Linemid1){
            update(nod*2+1, mid+1, r, u, v, Line);
            return;
        }

        if (Tmid2 <= Linemid2 && TR <= LineR){
            update(nod*2, l, mid, u, v, T[nod]);
            T[nod] = Line;
            return;
        }

        if (Tmid2 >= Linemid2 && TR >= LineR){
            update(nod*2, l, mid, u, v, Line);
            return;
        }
        return;
    }

    update(nod*2, l, mid, u, v, Line);
    update(nod*2+1, mid+1, r, u, v, Line);
}

vector<int> X; // Vector Roi rac hoa
int SIZE;
void update(int l, int r, const pii& Line){
    update(1, 1, SIZE, l, r, Line);
}
int query(int pos){
    return query(1, 1, SIZE, pos);
}
int LB(const int& val){
    return lower_bound(all(X), val) - X.begin();
}
int UB(const int& val){
    return upper_bound(all(X), val) - X.begin() - 1;
}

int f[maxn];
void DP(){
    int maxx = 0;
    up(i,1,n){
        int cur = LB(x[i]);
        f[i] = query(cur) + e[i];
        if (w[i] == 0) update(1, SIZE, {0ll, f[i]});
        // never mess with binary search !!
        // this update mean "insert a line from -oo to oo with a = 0 and b = f[i]"
        // 0 = lower_bound(-oo);
        // SIZE = upper_bound(oo) - 1;
        else{
            int l = x[i] - f[i]/w[i];
            int r = x[i] + f[i]/w[i];
            update(LB(l), cur, {w[i], f[i] - w[i]*x[i]});
            update(cur, UB(r), {-w[i], f[i] + w[i]*x[i]});
        }
        maxx = max(maxx, f[i]);
    }
    cout << maxx;
}

signed main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    #define Task "VOMARIO"
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    cin >> n;

    up(i,1,n){
        cin >> x[i] >> w[i] >> e[i];
        X.push_back(x[i]);
    }
    sort(all(X));
    purge(X);
    SIZE = X.size();

    X.insert(X.begin(), -1e9 - 7);
    X.push_back(1e9 + 7);
    up(i,1,SIZE) realval[i] = X[i];

    DP();
}

//solution for https://oj.vnoi.info/problem/vomario

/*
holy shit this is how you break the DP formular
//https://vnoi.info/forum/11/5384/?page=2
*/
