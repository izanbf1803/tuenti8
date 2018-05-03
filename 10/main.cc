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

const ll MOD = 1000000007;

inline ll mod(ll k, ll m) { return (m + k % m) % m; }

int P, G;
V<V<bool>> allowed;
V<V<ll>> dp;

ll h(int left, int right)
{
    // cerr << "CALL: "; D(left); D(right); D(right-left) << endl; /////
    if (right - left <= 0) return 1;
    if (dp[left][right] != -1) return dp[left][right];
    // cerr << "EXEC: "; D(left); D(right) << endl; /////
    ll sum = 0;

    for (int i = left+1; i <= right; i += 2) {
        if (allowed[left][i]) {
            // cerr << "UNION: "; D(left); D(i) << endl; /////
            sum = mod(sum + h(left+1, i-1) * h(i+1, right), MOD);
        }
    }

    dp[left][right] = sum;
    // cerr << "END: "; D(left); D(right) << endl; /////
    return sum;
}

int main()
{
    ios::sync_with_stdio(0);

    int C;
    cin >> C;
    for (int tc = 1; tc <= C; ++tc) {
        cin >> P >> G;
        allowed = V<V<bool>>(P, V<bool>(P, true));
        dp = V<V<ll>>(P, V<ll>(P, -1));
        for (int i = 0; i < G; ++i) {
            int a, b;
            cin >> a >> b;
            allowed[a][b] = allowed[b][a] = false;
            // D(a); D(b) << endl;
        }
        ll r;
        if (P % 2 == 1) {
            r = 0;
        }
        else {
            r = h(0, P-1);
        }
        cout << "Case #" << tc << ": " << r << endl;
    }
}