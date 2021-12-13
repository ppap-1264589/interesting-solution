//PPAP_1264589
#include "bits/stdc++.h"
#define Task "A"
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define pdd pair<double, double>
#define x first
#define y second
#define PI 3.141592654
using namespace std;

pdd A, B, C;
double R;
double req;
double S;
const double eps = 1e-3;
struct xcoor{
    bool is_sol;
    double x1, x2;
};
struct intersection{
    bool is_sol;
    pdd I1, I2;
};
bool comp(double x, double y){
    return (x + eps <= y);
}

pdd VECT(pdd p, pdd q){
    return make_pair(q.x - p.x, q.y - p.y);
}

double DOT(pdd u, pdd v){
    return u.x*v.x + u.y*v.y;
}

double DIST(pdd p, pdd q){
    double hx = p.x - q.x;
    double hy = p.y - q.y;
    return sqrt(hx*hx + hy*hy);
}

xcoor solve_Q2(double a, double b, double c){
    double delta = b*b - 4*a*c;
    if (comp(delta, 0)) return {0, 0, 0};
    double x1 = (-b + sqrt(delta)) / 2 / a;
    double x2 = (-b - sqrt(delta)) / 2 / a;
    return {1, x1, x2};
}

intersection Find(pdd line, pdd C, double R){
    double la = line.x;
    double lb = line.y;
    double a = la*la+1;
    double b = 2*(la*lb - C.x - C.y*la);
    double c = C.x*C.x + (C.y-lb)*(C.y-lb) - R*R;
    xcoor X = solve_Q2(a,b,c);
    if (!X.is_sol) return {0, {}, {}};

    double x1 = X.x1;
    double x2 = X.x2;
    double y1 = la*x1 + lb;
    double y2 = la*x2 + lb;
    return {1, {x1, y1}, {x2, y2}};
}

double calc_angle(pair<pdd, pdd> I, pdd C){
    pdd A = I.x;
    pdd B = I.y;
    pdd u = VECT(C, A);
    pdd v = VECT(C, B);
    double angle = acos(DOT(u, v)/(DIST(C, A)*DIST(C, B)));
    return angle;
}

double segment_area(double angle, double R){
    return 0.5*R*R*(angle - sin(angle));
}

pdd make_line(pdd A, pdd B){
    double a = (A.y - B.y)/(A.x - B.x);
    double b = A.y - A.x*a;
    return make_pair(a, b);
}
string solve(){
    intersection K = Find(make_line(A, B), C, R);
    if (!K.is_sol) return "NO";
    double angle = calc_angle(make_pair(K.I1, K.I2), C);
    double cut = segment_area(angle, R);

    cut /= (R*R*PI);
    cut *= 100;
    if (cut >= req - 5 && cut <= req + 5) return "YES";
    return "NO";
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
        cin >> R >> req;
        cout << solve() << "\n";
    }
}
