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
// template<typename T, typename U> using P = pair<T,U>;
template<typename T, typename U> using umap = unordered_map<T,U>;
template<typename T, typename U> using uset = unordered_set<T,U>;
template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using max_heap = priority_queue<T>;

struct P {
    int x, y;
};

ostream& operator<<(ostream& os, P p)
{
    os << '{' << p.x << ',' << ' ' << p.y << '}';
    return os;
}

P operator+(P a, P b)
{
    return {a.x+b.x, a.y+b.y};
}

const V<P> dirs = {
    {+2, +1}, 
    {+2, -1}, 
    {-2, +1}, 
    {-2, -1}, 
    {+1, +2}, 
    {+1, -2}, 
    {-1, +2}, 
    {-1, -2}, 
};

int n, m;
V<V<char>> grid;

P pr, k, d; // princess, knight, destination

bool valid(P p)
{
    return (p.x >= 0) and (p.y >= 0) and (p.x < m) and (p.y < n) and (grid[p.y][p.x] != '#');
}

int BFS(P start, P end)
{
    V<V<int>> dist(n, V<int>(m, -1));
    queue<P> que;
    dist[start.y][start.x] = 0;
    que.push(start);
    while (not que.empty()) {
        P p = que.front();
        que.pop();
        if (p.x == end.x and p.y == end.y) {
            return dist[end.y][end.x];
        }
        for (P dir : dirs) {
            if (grid[p.y][p.x] == '*') dir = dir+dir; // boost
            P q = p + dir;
            if (valid(q)) {
                if (dist[q.y][q.x] == -1) {
                    dist[q.y][q.x] = dist[p.y][p.x] + 1;
                    que.push(q);
                }
            }
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(0);
    int c;
    cin >> c;
    for (int tc = 1; tc <= c; ++tc) {
        cin >> n >> m;
        grid = V<V<char>>(n, V<char>(m));
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < m; ++x) {
                cin >> grid[y][x];
                if (grid[y][x] == 'P') pr = {x, y};
                if (grid[y][x] == 'S') k = {x, y};
                if (grid[y][x] == 'D') d = {x, y};
            }
        }
        cout << "Case #" << tc << ": ";
        int a = BFS(k, pr);
        int b = BFS(pr, d);
        if (a < 0 or b < 0) {
            cout << "IMPOSSIBLE";
        }
        else {
            cout << a+b;
        }
        cout << endl;
    }
}