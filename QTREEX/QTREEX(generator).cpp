#include <bits/stdc++.h>
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define all(x) x.begin(), x.end()
#define int long long
using namespace std;

mt19937_64 RNG(chrono::high_resolution_clock::now().time_since_epoch().count());
long long UID(long long l, long long r){
    uniform_int_distribution<mt19937_64::result_type> random_number(l, r);
    return random_number(RNG);
}

void sinh(){
    int n = 100;
    int q = 100;
    int lim = 1e9;

    cout << n << "\n";
    up(i,1,n-1) {
        cout << UID(1, i) << " " << i+1 << " " << UID(-lim, lim) << "\n";
    }
    up(i,1,q){
        int x;
        string type;
        if (i & 1) x = 3;
        else x = UID(1, 2);

        if (x == 1) type = "CHANGE";
        else if (x == 2) type = "NEGATE";
        else type = "QUERY";

        cout << type << " ";
        if (x == 1){
            cout << UID(1, n-1) << " " << UID(-lim, lim);
        }
        if (x == 2 || x == 3){
            cout << UID(1, n) << " " << UID(1, n);
        }
        cout << "\n";
    }
    cout << "DONE";
    cout << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    #define Task "A"
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    int tt;
    tt = 20;
    cout << tt << "\n\n";
    while (tt--) sinh();
}
