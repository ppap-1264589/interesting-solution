#include <bits/stdc++.h>
#include <windows.h>
#include <direct.h>
#define bit(x, i) (((x) >> (i)) & 1)
#define Task "DRAFT"
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define pii pair<int, int>
#define f first
#define s second
#define ep emplace_back
#define int long long
using namespace std;

int maxtest;
ofstream fo;
ofstream rfo("DRAFT.out");
char NAME_file[] = "BASICCRT";  // <- Enter your Task file here
char exe_file[100] = "";
char inp_file[100] = "";
char out_file[100] = "";
string folder = "Test000";

mt19937 RNG(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<mt19937::result_type> random_number(1, 2000000011);
int randome(){  return random_number(RNG);  }

template<class Iter>
Iter FisherYates(Iter Begin, Iter End, size_t choose) {
    size_t left = distance(Begin, End);
    while (choose--) {
        Iter r = Begin;
        advance(r, randome()%left);
        swap(*Begin, *r);
        ++Begin, --left;
    }
    return Begin;
}
vector<int> pick_shuffle(vector<int>& temp, int choose){
    vector<int> res;
    FisherYates(temp.begin(), temp.end(), choose);
    up(i,0,choose-1) res.ep(temp[i]);
    return res;
}


///------------------ Main processes ------------------///

vector<int> prime;
vector<int> little_prime, medium_prime, bigger_prime;
vector<int> P;
vector<int> small_number, medium_number, bigger_number;
vector<int> pick;
bool return_test;

bool isprime(int x){
    if (x == 1) return false;
    for (int i = 2; i*i <= x; i++){
        if (x % i == 0) return false;
    }
    return true;
}
void prepare_test(){
    up(i,1,1000){
        P.ep(i);
        if (isprime(i)){
            prime.ep(i);
            if (1 <= i && i <= 61) little_prime.ep(i);
            if (233 <= i && i <= 659) medium_prime.ep(i);
            if (700 <= i && i <= 1000) bigger_prime.ep(i);
        }
        if (1 <= i && i <= 333) small_number.ep(i);
        if (334 <= i && i <= 667) medium_number.ep(i);
        if (668 <= i && i <= 1000) bigger_number.ep(i);
    }
}

// signal = 0 -> no assumption that modulos are pairwise-coprime (remainder < 1000)
// signal = 1 -> no assumption that modulos are pairwise-coprime (remainder < 100)
// signal = 2 -> all modulos are primes
// signal = 3 -> (n/2) choosen are pairwise-coprime and left are randoms

bool validate(vector<int>& x){
    long long LCM = 1;
    for (auto k : x){
        if (log10(LCM) + log10(k) >= 17) return false;
        LCM = LCM/__gcd(LCM, 1ll*k)*1ll*k;
    }
    return true;
}

void special_choose(vector<int>& x, vector<int>& mC, vector<int>& sC, int a, int b){
    x = pick_shuffle(mC, a);
    up(j,1,b) x.ep(sC[randome() % (int)sC.size()]);
}

void detail_test(int& test){
    int choose;
    int signal;
    signal = ceil(double((test-1)/(maxtest/4)));
    choose = test - signal*maxtest/4;
    choose = ceil(double((choose-1)/8))+1;
    vector<pii> T;

    if (signal == 0) pick = pick_shuffle(P, choose);
    if (signal == 1) pick = pick_shuffle(small_number, choose);
    if (signal == 2) pick = pick_shuffle(prime, choose);
    if (signal == 3) {
        int choose_prime = randome() % choose + 1;
        int left_choose = choose - choose_prime;
        if (choose <= 2) special_choose(pick, bigger_prime, small_number, choose_prime, left_choose);
        else if (choose <= 4) special_choose(pick, medium_prime, small_number, choose_prime, left_choose);
        else if (choose <= 6) special_choose(pick, little_prime, medium_number, choose_prime, left_choose);
        else special_choose(pick, medium_prime, bigger_number, choose_prime, left_choose);
    }

    if (!validate(pick) || pick.empty()){
        --test;
        return_test = 1;
        return;
    }

    shuffle(pick.begin(), pick.end(), RNG);
    for (auto x : pick) T.ep(x, randome() % x);
    fo << choose << "\n";
    for (auto x : T) fo << x.f << " " << x.s << "\n";
}


///------------------ Define file behaviour ------------------///

void run_answer(){
    system(exe_file);
}

void Rename_file(int test){
    folder[4] = test/100 + '0';
    folder[5] = test/10%10 + '0';
    folder[6] = test%10 + '0';
}

void Redirect_folder(){
    mkdir(&folder[0]);
    string output_path = folder + "\\" + inp_file;
    CopyFile(inp_file, &output_path[0], false);
    output_path = folder + "\\" + out_file;
    CopyFile(out_file, &output_path[0], false);
}

void Make_file_name(){
    strcpy(exe_file, NAME_file);
    strcpy(inp_file, NAME_file);
    strcpy(out_file, NAME_file);

    strcat(exe_file, ".exe");
    strcat(inp_file, ".inp");
    strcat(out_file, ".out");
}

void generate_test(){
    prepare_test();
    Make_file_name();
    up(test, 1, maxtest){
        return_test = 0;
        fo.open(inp_file);
        detail_test(test);
        if (return_test == 1) {
            fo.close();
            continue;
        }
        fo.close();
        run_answer();
        Rename_file(test);
        Redirect_folder();
    }
    DeleteFile(inp_file);
    DeleteFile(out_file);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    maxtest = 256;
    generate_test();

    up(test, 1, maxtest){
        int choose;
        int signal;
        signal = ceil(double((test-1)/(maxtest/4)));
        choose = test - signal*maxtest/4;
        choose = ceil(double((choose-1)/8))+1;
        rfo << signal << " " << choose << "\n";
    }
}
