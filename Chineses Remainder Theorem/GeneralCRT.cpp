#include <bits/stdc++.h>
#define Task "A"
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define bit(x,i) ((x >> i) & 1)
#define int long long
using namespace std;

long long addmod(long long a, long long b){
    a %= b;
    if (a < 0) a += b;
    return a;
}

struct extype{
    int x,y,d;
};
extype exeuclid(int a, int b){
    if (b == 0) return {1, 0, a};
    extype p = exeuclid(b, a%b);
    return {p.y, p.x - a/b*p.y, p.d};
}

struct CRTtype{
    bool isSol;
    long long x;
    long long lcm;
};
CRTtype CRT(int a, int b, int n, int m){
    extype p = exeuclid(n,m);
    int x = p.x;
    int D = p.d;
    int C = (b - a);
    if (C%D != 0) return {0, -1, -1};
    long long res = addmod(a + 1ll*C/D*x % (m/D) * n, 1ll*m/D*n);
    return {1, res, 1ll*m/D*n};
}

namespace generalCRT{
    const int maxn = 101;
    int a[maxn];
    int n[maxn];
    int E;
    void MAIN(){
        cin >> E;
        up(i,1,E) cin >> n[i] >> a[i];
        int res = a[1];
        int LCM = n[1];
        up(i,2,E){
            auto p = CRT(res, a[i], LCM, n[i]);
            if (p.isSol == 0){
                cout << "no solution \n";
                return;
            }
            res = p.x;
            LCM = p.lcm;
        }
        cout << res << " " << LCM << "\n";
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    generalCRT::MAIN();
}
