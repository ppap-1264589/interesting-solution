#include <bits/stdc++.h>
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define ep emplace_back
#define pii pair<int, int>
#define f first
#define s second
using namespace std;

int n;
int res = 1e9 + 7;
string fin;
string check(int a, int b){
    string g = "";
    while (true){
        if (a == 0 && b == 0) break;
        if (a == b) break;

        string cur;

        bool isswap = 0;
        int maxx, minn;
        if (a < b){
            maxx = b;
            minn = a;
            isswap = 1;
            cur = "0";
        }
        else{
            maxx = a;
            minn = b;
            cur = "1";
        }

        int step = maxx/(minn+1);
        maxx -= step*(minn+1);

        if (isswap){
            a = minn;
            b = maxx;
        }
        else{
            a = maxx;
            b = minn;
        }
        while (step--) g += cur;

        if (g.size() > 60) break;
    }

    if (a != 0 && b != 0 && a == b) return "zzz";
    else if (abs(a - b) == 1){
        if (a - b == 1) g += "1";
        else g += "0";
    }
    return g;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    #define Task "A"
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    cin >> n;
    fin.resize(n+1);
    up(i,0,n/2+1){
        string k = check(i, n-i);
        if (k == "zzz") continue;
        if (fin.size() > k.size()) fin = k;
    }
    cout << fin;
}
