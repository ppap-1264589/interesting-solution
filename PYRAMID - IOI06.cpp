#include <bits/stdc++.h>
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define ep emplace_back
#define pii pair<int, int>
#define f first
#define s second
using namespace std;

const int maxn = 1e3 + 10;
int a[maxn][maxn], s[maxn][maxn];
int minr[maxn][maxn];
int mint[maxn][maxn];
int n,m;
int A,B,C,D;

int cs[maxn][maxn]; //chamber sum

deque<int> Q;

int Sum(int ux, int vx, int uy, int vy){
    return s[vx][vy] - s[ux-1][vy] - s[vx][uy-1] + s[ux-1][uy-1];
}

void push_row(int i, int j){
    while (!Q.empty() && cs[i][Q.front()] >= cs[i][j]) Q.pop_front();
    Q.push_front(j);
    while (Q.back() - (B - D - 1) + 1 > j) Q.pop_back();
    //Q.back() - (B - D - 1) + 1 is the limit that Q can hold for min chambers
}

void init_row(){
    up(i,1,n-C+1){
        Q.clear();
        //downward -> take information from j + (A - C - 1) to j
        down(j,m,1){
            push_row(i, j);
            if (j + (B - D - 1) - 1 <= m) minr[i][j] = cs[i][Q.back()];
        }
    }
}

void push_table(int i, int j){
    while (!Q.empty() && minr[Q.front()][j] >= minr[i][j]) Q.pop_front();
    Q.push_front(i);
    while (Q.back() - (A - C - 1) + 1 > i) Q.pop_back();
    //Q.back() - (A - C - 1) + 1 is the limit that Q can hold for min chambers
}

void init_table(){
    up(j,1,m-D+1){
        Q.clear();
        //downward -> take information from i + (B - D - 1) to i
        down(i,n,1){
            push_table(i, j);
            if (i + (A - C - 1) - 1 <= n) mint[i][j] = minr[Q.back()][j];
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    #define Task "A"
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

//    n,A,C
//    m,B,D

    cin >> m >> n >> B >> A >> D >> C;
    up(i,1,n) up(j,1,m){
        cin >> a[i][j];
        s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
    }

    for (int i = 1; i <= n-C+1; i++){
        for (int j = 1; j <= m-D+1; j++){
            cs[i][j] = Sum(i, i+C-1, j, j+D-1);
        }
    }

    up(i,0,n+1){
        memset(minr[i], 60, sizeof(minr[i][0])*(m+3));
        memset(mint[i], 60, sizeof(mint[i][0])*(m+3));
    }

    init_row();
    init_table();


    pii C1 = {0, 0};
    pii C2 = {0, 0};
    int maxx = -1;
    int foundmin = -1;
    up(i,1,n-A+1){
        up(j,1,m-B+1){
            int val = Sum(i, i+A-1, j, j+B-1) - mint[i+1][j+1];
            if (maxx < val){
                maxx = val;
                foundmin = mint[i+1][j+1];
                C1 = make_pair(i, j);
            }
        }
    }

    for (int i = C1.f+1; i <= C1.f+A-C-1; i++){
        if (C2.f != 0) break;
        for (int j = C1.s+1; j <= C1.s+B-D-1; j++){
            if (cs[i][j] == foundmin){
                C2 = make_pair(i, j);
                break;
            }
        }
    }

//    cout << maxx << "\n";
    cout << C1.s << " " << C1.f << "\n";
    cout << C2.s << " " << C2.f;
}
