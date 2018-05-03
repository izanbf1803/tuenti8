#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
using namespace std;

#define D(x) cerr << #x << " = " << (x) << ", "

typedef unsigned int uint;
typedef unsigned long ul;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;

template<typename T> using V = vector<T>;
template<typename T, typename U> using P = pair<T,U>;
template<typename T, typename U> using umap = unordered_map<T,U>;
template<typename T, typename U> using uset = unordered_set<T,U>;
template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using max_heap = priority_queue<T>;

template <typename T>
ostream& operator<<(ostream& os, V<T> v)
{
    os << '{';
    if (v.size() > 0) {
        os << v[0];
        for (int i = 1; i < v.size(); ++i) {
            os << ',' << ' ' << v[i];
        }
    }
    os << '}';
    return os;
}

const int W = 2;
const int H = 1;

const int mayor = 1;
const int menor = 0;

const V<V<int>> saltos = {
    { 0, W, H, W, W, H, W, W }, // menor
    { 0, W, W, H, W, W, W, H }, // mayor
};

const V<string> notas = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

V<V<int>> offsets(2, V<int>(8));
V<V<string>> escalas;
V<char> escala_m;

const int MOD = 12;
 
int mod(int n) { return (n % MOD + MOD) % MOD; }

bool pertenece(V<string>& escala, string& s)
{
    int v = 0;
    for (int i = 0; i < 12; ++i) {
        if (s[0] == notas[i][0]) {
            v = mod(i);
            break;
        }
    }
    if (s.size() > 1) {
        if (s[1] == '#') v = mod(v+1);
        if (s[1] == 'b') v = mod(v-1);
    }
    return (find(escala.begin(), escala.end(), notas[v]) != escala.end());
}

int main()
{
    ios::sync_with_stdio(0);

    for (int m = 0; m < 2; ++m) {
        for (int i = 1; i < 7; ++i) {
            offsets[m][i] = saltos[m][i] + offsets[m][i-1];
        }
        for (int i = 0; i < 12; ++i) {
            V<string> escala;
            for (int j = 0; j < 7; ++j) {
                escala.push_back(notas[mod(i+offsets[m][j])]);
            }
            escalas.push_back(escala);
            escala_m.push_back(m == mayor ? 'M' : 'm');
            // D(escalas.size()-1); D(m); D(escala) << endl;
        }
    }

    int C;
    cin >> C;
    for (int tc = 1; tc <= C; ++tc) {
        int n;
        cin >> n;
        V<string> s(n);
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
        }
        
        cout << "Case #" << tc << ":";
        V<string> escalas_validas;

        for (int i = 0; i < escalas.size(); ++i) {
            auto& escala = escalas[i];
            bool ok = true;
            for (int i = 0; i < n; ++i) {
               ok &= pertenece(escala, s[i]);
            }
            if (ok) {
                escalas_validas.push_back(escala_m[i] + escala[0]);
            }
        }

        sort(escalas_validas.begin(), escalas_validas.end(), [&](const string& a, const string& b){
            if (a[0] != b[0]) {
                return a[0] == 'M';
            }   
            else if (a[1] != b[1]) {
                return a[1] < b[1];
            }
            else if (a.size() != b.size()) {
                return a.size() < b.size();
            }
            return false;
        });

        if (escalas_validas.size() > 0) {
            for (string& escala : escalas_validas) {
                cout << ' ' << escala;
            }
        }
        else {
            cout << " None";
        }
        cout << endl;
    }
}