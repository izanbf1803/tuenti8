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
using pii = P<int,int>;

V<V<int>> diamonds;
V<V<int>> common; // lasers in common (by diamonds)
V<int> states; // -1 : undef, 0 : off, 1 : on
V<V<int>> graphs;

int n, m, I;

ostream& operator<<(ostream& os, const pii& x)
{
    os << '{' << x.first << ',' << x.second << '}';
    return os;
}

template <typename T>
void show_table(const V<V<T>>& t)
{
    cerr << endl;
    const int w = 3;
    for (int i = 0; i < t.size(); ++i) {
        cerr << setw(3) << i << ": ";
        for (int j = 0; j < t[i].size(); ++j) {
            if (t[i][j] == -1)
                cerr << setw(w) << '.';
            else 
                cerr << setw(w) << t[i][j];
        }
        cerr << endl;
    }
    cerr << endl;
}

void propagate_state(int l, int graph)
{
    graphs[graph].push_back(l);
    states[l] = 1;
    for (int i : common[l]) {
        if (states[i] == -1) propagate_state(i, graph);
    }
}

void explore(int l)
{
    if (l < m+n) {
        if (states[l] == -1) {
            graphs.push_back({});
            propagate_state(l, graphs.size()-1);
        }
        explore(l+1);
    }
}

void isolate_vertices(const V<int>& graph)
{
    int node, mind;
    do {
        node = -1;
        mind = INT_MAX;
        for (int u : graph) {
            if (states[u] == 1) {
                int d = 0;
                for (int v : common[u]) {
                    d += states[v];
                }
                if (d != 0 and d < mind) {
                    mind = d;
                    node = u;
                }
            }
        }   
        if (node != -1) {
            for (int i : common[node]) {
                states[i] = 0;
            }
        }
    } while (node != -1);
}

int main()
{
    ios::sync_with_stdio(0);

    int C;
    cin >> C;
    for (int tc = 1; tc <= C; ++tc) {
        cin >> n >> m >> I;
        diamonds = V<V<int>>(n, V<int>(m, -1));
        common = V<V<int>>(n+m);
        states = V<int>(n+m, -1);
        graphs.clear();
        for (int i = 0; i < I; ++i) {
            int x, y;
            cin >> y >> x;
            diamonds[y][x] = 0;
            common[y].push_back(n+x);
            common[n+x].push_back(y);
        }

#define DEBUG 0
#if DEBUG
        D(m); D(n); D(m+n) << endl;
        show_table(diamonds);
#endif

        explore(0);

        int max_on = 0;
        for (int i = 0; i < graphs.size(); ++i) {
            isolate_vertices(graphs[i]);
            int zeros = 0;
            int ones = 0;
            for (int u : graphs[i]) {
                if (states[u] == 0) ++zeros;
                if (states[u] == 1) ++ones;
            }
            max_on += max(zeros, ones);
        }

        cout << "Case #" << tc << ": " << max_on << endl;
    }
}