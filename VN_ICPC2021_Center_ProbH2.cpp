//PPAP_1264589
#pragma GCC optimize("O3,unroll-loops")
#include "bits/stdc++.h"
#define Task "A"
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define pdd pair<double, double>
#define x first
#define y second
using namespace std;

pdd A, B, C;
double R;
double perc;

double distance_line_center(pdd A, pdd B, pdd C){
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = -(A.x*a + A.y*b);
    return abs((a*C.x + b*C.y + c)/sqrt(a*a + b*b));
}

const double PI = asin(1.0)*2;
const double eps = 1e-18;
bool comp(double a, double b){
    return (a + eps <= b);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    if (fopen(Task".inp", "r")){
        freopen (Task".inp", "r", stdin);
        freopen (Task".out", "w", stdout);
    }

    cout << fixed << setprecision(3);
    while (cin >> A.x){
        cin >> A.y >> B.x >> B.y >> C.x >> C.y;
        cin >> R >> perc;

        double d = distance_line_center(A, B, C);
        if (comp(R, d)) {
            cout << "NO\n";
            continue;
        }
        double S = R*R*PI;
        double liml = S * (perc - 5)/100;
        double limr = S * (perc + 5)/100;
        double theta = acos(d/R);
        double S2 = theta*R*R - d*sqrt(R*R - d*d);
        if (comp(liml, S2) && comp(S2, limr)) cout << "YES";
        else cout << "NO";
        cout << "\n";
    }
}

// Algorithmic logic
// Very nice Implementation, instead of too many complicated computations
